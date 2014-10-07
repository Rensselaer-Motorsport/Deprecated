#bufferTest.py

sensorDict = Buffer()

sensorDict.addSensor("engine sensor")
sensorDict.addSensorValue("engine", "temperature", 150)
sensorDict.addSensorValue("engine", "oil pressure", 89)
sensorDict.addSensor("suspension")
sensorDict.addSensorValue("suspension", "force", 12)

print("test")
print(sensorDict.getSensorValue("engine", "temperature"))
print(sensorDict.getSensorValue("engine", "oil pressure"))
print(sensorDict.getSensorValue("suspension", "force"))