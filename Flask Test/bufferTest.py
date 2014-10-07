import sensor_buffer
#bufferTest.py

sensorDict = sensor_buffer.sensorBuffer()

sensorDict.addSensor("engine_sensor")
sensorDict.addSensorValue("engine_sensor", 150)
sensorDict.addSensorValue("engine_sensor", 89)
sensorDict.addSensor("suspension")
sensorDict.addSensorValue("suspension", 12)

print("test")
print(sensorDict.getSensorValue("engine_sensor"))
print(sensorDict.getSensorValue("engine_sensor"))
print(sensorDict.getSensorValue("suspension"))
