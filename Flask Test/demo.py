import serial

ser = serial.Serial()
ser.baudrate = 9600
ser.port = '/dev/ttyACM0'
ser.open()

myDict = {'s1': [], 's2': [], 's3': []}

def ser_read():
	while True:
		try:
			data = ord(ser.read())
			break
		except: continue
	return data

def wait_for_beginning(lst, start):
	data = ser_read()
	if data == start:
		lst.append(data)
		if len(lst) == 5:
			return
		wait_for_beginning(lst, start+1)
	else:
		wait_for_beginning([], 0)
