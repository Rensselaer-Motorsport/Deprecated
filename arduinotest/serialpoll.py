import serial

ser = serial.Serial()
ser.baudrate = 9600
ser.port = '/dev/ttyACM0'
ser.timeout = 10
ser.open()

while True:
	try:
		a = ser.read()
		break
	except:
		continue

print a
