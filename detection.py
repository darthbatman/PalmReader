from picamera import PiCamera
import boto3
import time
import os
import serial
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

port = serial.Serial('/dev/ttyS0', baudrate=9600, timeout=0.5)

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

DETECTION_THRESHOLD = 25

try:
    while True:
        time.sleep(0.1)

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
        if cm_distance < DETECTION_THRESHOLD:
            print('Detected object within ' + str(DETECTION_THRESHOLD) + ' cm')
            GPIO.output(BUZZER, 1)
            time.sleep(0.5)
            GPIO.output(BUZZER, 0)

            camera.capture('/tmp/picture.jpg')

            output = ''
            with open('/tmp/picture.jpg', 'rb') as image:
                response = textract.detect_document_text(
                    Document={'Bytes': image.read()})
                for item in response['Blocks']:
                    if item['BlockType'] == 'LINE':
                        output += item['Text']
                print(output)
                port.write(str.encode(str(output)))
                port.flush()
                raise KeyboardInterrupt


except KeyboardInterrupt:
    GPIO.cleanup()
    exit
