from picamera import PiCamera
import boto3
import time
import os
import serial
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
# port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=0.5)
# port = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=0.5)
port = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=0.5)

TRIG = 7
ECHO = 12
BUZZER = 16

GPIO.setup(BUZZER, GPIO.OUT)

GPIO.setup(TRIG, GPIO.OUT)
GPIO.output(TRIG, 0)

GPIO.setup(ECHO, GPIO.IN)

camera = PiCamera()
client = boto3.client('rekognition')
textract = boto3.client('textract')

try:
    while True:
        time.sleep(0.1)

        # print("Starting Measurement...")

        GPIO.output(TRIG, 1)
        time.sleep(0.00001)
        GPIO.output(TRIG, 0)

        while GPIO.input(ECHO) == 0:
            pass
        start = time.time()

        while GPIO.input(ECHO) == 1:
            pass
        stop = time.time()

        cm_distance = (stop - start) * 17000

        buzzer_delay = 1.0
        if cm_distance < 25:
            print("WITHIN RANGE")
            GPIO.output(BUZZER, 1)

            # calling read() twice as a workaround to clear the buffer.
            camera.capture('/tmp/picture.jpg')

            output = ""
            # client.search_faces_by_image(CollectionId=collection, Image={'Bytes': frame}, MaxFaces=1, FaceMatchThreshold=85)
            with open('/tmp/picture.jpg', 'rb') as image:
                response = textract.detect_document_text(Document={'Bytes': image.read()})
                # response = client.detect_labels(Image={'Bytes': image.read()})
                # print('Detected labels:')
                # for label in response['Labels']:
                #     print (label['Name'] + ' : ' + str(label['Confidence']))
                for item in response["Blocks"]:
                    if item["BlockType"] == "LINE":
                        output += item["Text"]
                print(output)
                port.write(str.encode(str(output)))
                port.flush()
            GPIO.output(BUZZER, 0)


except KeyboardInterrupt:
    GPIO.cleanup()
    exit

