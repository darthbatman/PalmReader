import RPi.GPIO as GPIO
import time
import picamera
import requests
import base64
import json

input_pin = 11
prev_input = 0

camera = picamera.PiCamera()
GPIO.setmode(GPIO.BOARD)
GPIO.setup(input_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)


def encode_image(file_name):
    with open(file_name, 'r') as image:
        data = image.read()
        return str(base64.b64encode(data))


def check_button():
    global prev_input
    while True:
        input = GPIO.input(input_pin)
        if (not prev_input) and input:
            return True
            break
        prev_input = input
        time.sleep(.05)


def get_text_from_image(file_name):
    request_data = {
        'requests': [
            {
                'image': {
                    'content': encode_image(file_name)
                },
                'features': [
                    {
                        'type': 'LABEL_DETECTION'
                    }
                ]
            }
        ]
    }

    api_base_url = 'https://vision.googleapis.com/v1'
    endpoint = '/images:annotate'
    key_param = '?key='
    key = 'API_KEY'

    url = api_base_url + endpoint + key_param + key

    response = requests.post(
        url, data=json.dumps(request_data))

    res_json = json.loads(response.text)

    print(res_json)


def start_capture():
    while True:
        global prev_input
        prev_input = 0
        if check_button():
            file_name = 'image.jpg'
            camera.capture(file_name)
            get_text_from_image(file_name)


if __name__ == '__main__':
    start_capture()
    GPIO.cleanup()
