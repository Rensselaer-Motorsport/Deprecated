class Buffer(object):
	
	#initializes the class.
	#can either take in an already made sensor dictionary
	#or it will make an empty dictionary
	def _init_(self, pre_sensor_dict):
		if pre_sensor_dict is None:
			#sensor_dict is a dictionary holding other dictionarys of seperate sensors
			self.sensor_dict = pre_sensor_dict
		else:
			self.sensor_dict = {}

	def addSensor (sensor_name):
		sensor_dict[sensor_name] = {}

	def addNewSensorValue (sensor_name, new_value_key, new_value):
		sensor_dict[sensor_name][new_value_key] = new_value

	def getSensor (sensor_name):
		return sensor_dict.get(sensor_name)

	def getSensorValue (sensor_name, value_key):
		return sensor_dict.get(sensor_name).get(value_key)


#bufferTest.py

sensorDict = Buffer()

sensorDict.addSensor("engine_sensor")
sensorDict.addSensorValue("engine", "temperature", 150)
sensorDict.addSensorValue("engine", "oil pressure", 89)
sensorDict.addSensor("suspension")
sensorDict.addSensorValue("suspension", "force", 12)

print("test")
print(sensorDict.getSensorValue("engine", "temperature"))
print(sensorDict.getSensorValue("engine", "oil pressure"))
print(sensorDict.getSensorValue("suspension", "force"))