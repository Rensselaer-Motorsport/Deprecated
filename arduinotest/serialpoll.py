import serial

num_sensors = 3

def poll(s_dict):
	for i in range(num_sensors):
		tmp = ser_read()
		tmp+=(ser_read()<<8)
		s_dict.values()[i].append(tmp)
		ser_read()

def ser_init():
	global ser
	ser = serial.Serial()
	ser.baudrate = 9600
	ser.port = '/dev/ttyACM0'
	ser.timeout = 10
	ser.open()

def ser_read():
	while True:
		try:
			data = ord(ser.read())
			break
		except:
			continue
	return data

def wait_for_beginning(lst, start):
	data = ser_read()
	if data == start:
		lst.append(data)
		if len(lst) == 5:
			return
		wait_for_beginning(lst, start+1)
	else:
		lst = []
		start = 0
		wait_for_beginning(lst, 0)

def main():
	pad_len = 5
	sensor_buffer = {'sensor1': [], 'sensor2': [], 'sensor3': []}

	ser_init()
	wait_for_beginning([], 0)
	count = 0
	while count < 10:
		poll(sensor_buffer)
		last = ser_read()
		while last != pad_len-1:
			last = ser_read()
		count += 1
	print sensor_buffer

if __name__ == '__main__':
	main()
