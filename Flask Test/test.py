from flask import Flask, jsonify, render_template, request
from serialpoll import SensorData
import serial
import threading
import time
app = Flask( __name__ )

@app.route( '/_random_number' )
def get_random():
	#with open( "/dev/urandom", 'rb' ) as f:
	#	return jsonify(  result=ord( f.read( 1 ) ) )
	while len( sensor_buffer.values()[0] ) == 0: continue
	return jsonify( result=sensor_buffer.values()[0].pop(0) )

@app.route( '/' )
def index():
	return render_template( 'index.html' )

def serial_init():
	ser = serial.Serial()
	ser.baudrate = 9600
	ser.port = '/dev/ttyACM0'
	ser.open()

	return ser

def serial_poll( s_dict ):
	dev = serial_init()
	s = SensorData( dev, s_dict, 0, 5 )
	while True:
		sensor_buffer = s.poll()
		s.wait_for_end()

if __name__ == "__main__":
	global sensor_buffer
	sensor_buffer = { 'sensor1': [1, 2, 3, 4 ,5], 'sensor2': [], 'sensor3': [] }
	app.debug = True
	
	serial_thread = threading.Thread( target=serial_poll, args=( sensor_buffer, ) )
	serial_thread.daemon = True

	app.run( threaded=True )
	serial_thread.start()

	while True:
		time.sleep(.1)
