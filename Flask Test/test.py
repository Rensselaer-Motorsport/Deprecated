from flask import Flask, jsonify, render_template, request
from serialpoll import SensorData
import serial
import threading
import time
app = Flask( __name__ )

@app.route( '/_random_number' )
def get_random():
	if len( sensor_buffer.values()[0] ) == 0: return
	else: return jsonify( result=sensor_buffer.values()[0].pop(0) )

@app.route( '/' )
def index():
	return render_template( 'index.html' )

def serial_poll( s_dict ):
	dev = serial_init()
	s = SensorData( dev, s_dict, 0, 5 )
	while True:
		sensor_buffer = s.poll()
		s.wait_for_end()

def serial_init():
	ser = serial.Serial()
	ser.baudrate = 9600
	ser.port = '/dev/ttyACM0'
	ser.open()

	return ser

if __name__ == "__main__":
	global sensor_buffer
	sensor_buffer = { 'sensor1': [], 'sensor2': [], 'sensor3': [] }
	app.debug = True

	serial_thread = threading.Thread( target=serial_poll, args=(sensor_buffer, ) )
	serial_thread.daemon = True
	serial_thread.start()
	
	app.run()

	while True:
		time.sleep( .1 )
