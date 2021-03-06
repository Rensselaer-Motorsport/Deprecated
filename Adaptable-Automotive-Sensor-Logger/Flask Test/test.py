from flask import Flask, jsonify, render_template, request
from serialpoll import SensorData
import json
import random
import serial
import threading
import time
app = Flask( __name__ )

@app.route( '/_random_number' )
def get_data():
	if len( sensor_buffer.values()[0] ) == 0: return
	else: return jsonify( result=[ i.pop(0) for i in sensor_buffer.values() ] )

@app.route( '/' )
def index():
	return render_template( 'index.html' )

def serial_poll( s_dict ):
	dev = serial_init()
	s = SensorData( dev, s_dict, 0, 5 )
	s.wait_for_beginning(s.pad_start)
	while True:
		sensor_buffer = s.poll()
		s.wait_for_end()
		#print sensor_buffer
		#print s.ser_read()
		#print ord(dev.read())

def serial_init():
	ser = serial.Serial()
	ser.baudrate = 9600
	ser.port = '/dev/ttyACM0'
	ser.open()

	return ser

if __name__ == "__main__":
	global sensor_buffer
	sensor_buffer = { 'sensor1': [] }
	app.debug = True

	serial_thread = threading.Thread( target=serial_poll, args=(sensor_buffer, ) )
	serial_thread.daemon = True
	serial_thread.start()
	
	app.run(port=5001)

	while True:
		time.sleep( .1 )
