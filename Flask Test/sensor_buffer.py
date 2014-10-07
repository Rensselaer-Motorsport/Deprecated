class sensorBuffer:
	
	#initializes the class.
	#can either take in an already made sensor dictionary
	#or it will make an empty dictionary
	def __init__(self):
		#sensor_dict is a dictionary holding other dictionarys of seperate sensors
		self.sensor_dict = {}

	def addSensor (self, sensor_name):
		self.sensor_dict[sensor_name] = []

	def addSensorValue (self, sensor_name, new_value):
		self.sensor_dict[sensor_name].append(new_value)

	def getSensor (self, sensor_name):
		return self.sensor_dict[sensor_name]

	def getSensorValue (self, sensor_name):
		return self.sensor_dict[sensor_name].pop()
