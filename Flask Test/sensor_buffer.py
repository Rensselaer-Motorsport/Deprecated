import datetime

class SensorBuffer:

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
				print "  value " + str(value_index) + " = " + str(value)
				value_index = value_index + 1
			print

	#prints the entire dictionary
	def printDictionary (self):
		for sensor in self.sensor_dict:
			self.printSensorValues(sensor)

	#prints all the values of a specified sensor to a file
	#param sensor_name is the name of the sensor to print
	#param file_name is the name of the file to print to
	def printSensorToFile (self, sensor_name, file_name):
		f = open(file_name, 'w')
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				found = True
				break
		if not found:
			f.write("Sensor does not exist")
		else:
			f.write(sensor_name + ":")
			value_index = 0;
			for value in self.sensor_dict[sensor_name]:
				f.write("  value " + str(value_index) + " = " + str(value))
				value_index = value_index + 1;
				f.write('\n')

	#prints the entire dictionary to a file
	def printDictionaryToFile (self, file_name):
		f = open(file_name, 'w')
		for sensor_name in self.sensor_dict.keys():
			f.write(sensor_name + ":")
			value_index = 0;
			for value in self.sensor_dict[sensor_name]:
				f.write(" value " + str(value_index) + " = " + str(value))
				value_index = value_index + 1;
				f.write('\n')

	#prints and erases the last sensor value to a file
	def printLastSensorValueToFile (self, sensor_name, file_name):
		f = open(file_name, 'w')
		for key in self.sensor_dict.keys():
			if sensor_name == key:
				found = True
				break
		if not found:
			f.write("Sensor does not exist")
		else:
			f.write(sensor_name + ": " + str(self.getLastSensorValue(sensor_name)))
		f.write('\n')

	#prints and erases the last value from all sensors to a file
	def printAllLastSensorValuesToFile (self, file_name):
		f = open(file_name, 'w')
		for sensor_name in self.sensor_dict.keys():
			f.write(sensor_name + ": " + str(self.getLastSensorValue(sensor_name)) + '\n')

	#prints the last value from each sensor to a file with a time stamp, appending the file
	#does NOT erase the last value from the sensor
	#the format is...
	#yyyy-mm-dd hh:mm:ss.ssssss sensorAvalue sensorBvalue sensorCvalue etc.
	def getValues (self, file_name):
		f = open(file_name, 'a')
		f.write (str(datetime.datetime.now()) + " ")
		for sensor_name in self.sensor_dict.keys():
			lastIndex = len(self.sensor_dict[sensor_name]) - 1
			if lastIndex >= 0:
				f.write(str(self.sensor_dict[sensor_name][lastIndex]) + ' ')
		f.write('\n')
