import sensor_buffer
#bufferTest.py

print

sensorDict = sensor_buffer.sensorBuffer()

#add sensors and values
sensorDict.addSensor("engine_sensor")
sensorDict.addSensor("suspension")
for x in xrange(0, 25):
	sensorDict.addSensorValue("engine_sensor", x*(4.5))
	sensorDict.addSensorValue("suspension", x)

#print sensors
print "Print the sensors with data"
sensorDict.printSensorValues("engine_sensor")
sensorDict.printSensorValues("suspension")
sensorDict.printSensorToFile("engine_sensor", "engineTestOutput.txt")
sensorDict.printSensorToFile("suspension", "suspensionTestOutput.txt")
sensorDict.printDictionaryToFile("dictionaryOutput.txt")
sensorDict.printLastSensorValueToFile("suspension", "lastSuspensionValue.txt")
sensorDict.printAllLastSensorValuesToFile("allLastSensorValues.txt")

#test error cases
sensorDict.addSensor("engine_sensor")
sensorDict.addSensorValue("bad_sensor", 5)
sensorDict.getSensor("bad_sensor")
sensorDict.getSensorValue("bad_sensor", 3)
sensorDict.getSensorValue("engine_sensor", 28)
print sensorDict.getSensor("shitwentwrong")

#test other functions
print
print "Test other functions"
print
print "Returns the engine_sensor value list"
print sensorDict.getSensor("engine_sensor")
print
print sensorDict.getLastSensorValue("engine_sensor")
print "expected 108.0"
print
print sensorDict.getLastSensorValue("engine_sensor")
print "expected 103.5"
print
print sensorDict.getSensorValue("engine_sensor", 5)
print "expected 22.5"
print
print "Print entire dictionary"
print sensorDict.printDictionary()
