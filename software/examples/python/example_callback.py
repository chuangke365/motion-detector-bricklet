#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_motion_detector import MotionDetector

# Callback function for end of detection cycle
def cb_detection_cycle_ended():
    print('Detection Cycle Ended (next detection possible in ~3 seconds)')

# Callback function for detected motion
def cb_motion_detected():
    print('Motion Detected')

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    md = MotionDetector(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register detected callback to function cb_motion_detected
    md.register_callback(md.CALLBACK_MOTION_DETECTED, cb_motion_detected)

    # Register detection cycle ended callback to function cb_detection_cycle_ended
    md.register_callback(md.CALLBACK_DETECTION_CYCLE_ENDED, cb_detection_cycle_ended)

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
