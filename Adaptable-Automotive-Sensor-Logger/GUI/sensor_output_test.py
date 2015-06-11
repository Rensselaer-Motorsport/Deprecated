#sensor_output_test.py

import sensor_buffer
import random as rand
from random import randint
import time

sensorDict = sensor_buffer.SensorBuffer();

sensorDict.addSensor("temperature")
sensorDict.addSensor("oil_pressure")
sensorDict.addSensor("accelerometer")
sensorDict.getSensors('test_buffer.txt')

def getRandValue(mean, deviation):
    sign = randint(0, 1)
    if sign == 0:
        sign = -1
    return rand.uniform(0, deviation)*sign + mean

for i in range(0, 80):
    sensorDict.addSensorValue("temperature", getRandValue(120, 22))
    sensorDict.addSensorValue("oil_pressure", getRandValue(24, 2))
    sensorDict.addSensorValue("accelerometer", getRandValue(0.95, 0.1))
    sensorDict.getValues('test_buffer.txt')
    time.sleep(0.25)
