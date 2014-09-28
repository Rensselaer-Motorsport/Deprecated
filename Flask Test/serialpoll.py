import serial

class SensorData:
	def __init__(self, ser_obj, s_dict, p_start, p_len):
		self.ser = ser_obj
		self.sensor_buffer = s_dict
		self.num_sensors = len(s_dict)
		self.pad_start = p_start
		self.pad_len = p_len
		self.wait_for_beginning([], p_start)

	def poll(self):
		for i in range(self.num_sensors):
			tmp = self.ser_read()
			tmp+=(self.ser_read()<<8)
			self.sensor_buffer.values()[i].append(tmp)
			self.ser_read()
		return self.sensor_buffer

	def ser_read(self):
		while True:
			try:
				data = ord(self.ser.read())
				break
			except:
				continue
		return data

	def wait_for_beginning(self, lst, start):
		data = self.ser_read()
		if data == start:
			lst.append(data)
			if len(lst) == self.pad_len:
				return
			self.wait_for_beginning(lst, start+1)
		else:
			lst = []
			start = 0
			self.wait_for_beginning(lst, 0)

	def wait_for_end(self):
		last = self.ser_read()
		while last != self.pad_len-1:
			last = self.ser_read()
