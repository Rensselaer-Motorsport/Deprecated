class sensorBuffer:
	
	#initializes the class.
	#can either take in an already made sensor dictionary
	#or it will make an empty dictionary
	def __init__(self):
		#sensor_dict is a dictionary holding other dictionarys of seperate sensors
		self.sensor_dict = {}

	#adds a new sensor to the end of the dictionary
	#param sensor_name is the key for the sensor
	def addSensor (self, sensor_name):
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				print "Sensor already added"
				return
		self.sensor_dict[sensor_name] = []

	#adds a value to the end of a specified sensor
	#param sensor_name is the name of sensor/dictionary key
	#param new value is the value to be added
	def addSensorValue (self, sensor_name, new_value):
		found = False
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				found = True
				break
		if found:
			self.sensor_dict[sensor_name].append(new_value)
		else:
			print "Sensor does not exist"

	#returns the list of values for a specified sensor
	#param sensor_name is the name of sensor/dictionary key
	def getSensor (self, sensor_name):
		found = False
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				found = True
				break
		if found:
			return self.sensor_dict[sensor_name]
		else:
			print "Sensor does not exist"

	#returns and erases the last value of a specified sensor
	#param sensor_name is the name of sensor/dictionary key
	def getLastSensorValue (self, sensor_name):
		found = False
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				found = True
				break
		if not found:
			print "Sensor does not exist"
		else:		
			return self.sensor_dict[sensor_name].pop()

	#returns a specified value of a specified sensor
	#does not change the sensor list
	#param sensor_name is the name of sensor/dictionary key
	#param value_index is the index of the value to be returned
	def getSensorValue (self, sensor_name, value_index):
		found = False
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				found = True
				break
		if not found:
			print "Sensor does not exist"
		elif value_index >= len(self.sensor_dict[sensor_name]):
			print "Value index does not exist"
		else:
			return self.sensor_dict[sensor_name][value_index]

	#prints all of the values of a specified sensor
	#param sensor_name is the name of sensor/dictionary key
	def printSensorValues (self, sensor_name):
		found = False
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				found = True
				break
		if not found:
			print "Sensor does not exist"
		else:		
			print sensor_name + ":"
			value_index = 0;
			for value in self.sensor_dict[sensor_name]:
				print "  value " + str(value_index) + " = " + str(value);
				value_index = value_index + 1;
			print

	#prints the entire dictionary
	def printDictionary (self):
		for sensor in self.sensor_dict:
			self.printSensorValues(sensor)