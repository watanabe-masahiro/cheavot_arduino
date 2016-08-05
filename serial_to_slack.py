#!/usr/bin/env python
# coding=utf-8

import serial
import sys
import urllib
import pycurl

def init_serial():
    default_serial_path = '/dev/cu.usbserial-A600dON0' # for Aruduino mini pro
    # default_serial_path = '/dev/cu.usbmodem1421' # for Aruduino
    return serial.Serial(default_serial_path, 9600, bytesize=serial.EIGHTBITS)
    # return None

def readline_serial(serial):
    # return '10'
    return serial.readline()

def notify_to_slack(message):
    # channel = 'bot'
    # url = 'http://127.0.0.1:8080/notify_jackpot?channel_name=' + channel
    channel = 'jackpot'
    url = 'http://notify-jackpot.herokuapp.com/notify_jackpot?channel_name=' + channel
    curl = pycurl.Curl()
    curl.setopt(pycurl.URL, url)
    data = urllib.urlencode({'message': message})
    curl.setopt(pycurl.POSTFIELDS, data)
    curl.perform()

def serial_to_slack():
    serial = init_serial()
    # to = ['watanabe']
    to = ['watanabe', 'fukudamasafumi', 'asai', 't_mizuno', 'washino']
    mention = ', '.join(['@'+name for name in to])
    while True:
        number = readline_serial(serial).rstrip()
        message = mention+' こだわりが認められました!\n今までに、 ' + str(int(number)) + '人から認められています。'
        notify_to_slack(message)
    # number = readline_serial(serial).rstrip()
    # message = mention+' こだわりが認められました!\n今までに、 ' + number + '人から認められています。'
    # notify_to_slack(message)

if __name__ == '__main__':
    serial_to_slack()
