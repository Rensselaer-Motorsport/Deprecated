from flask import Flask, jsonify, render_template, request
from serialpoll import SensorData
import serial
import threading
app = Flask( __name__ )

@app.route( '/_random_number' )
def get_random():
	with open( "/dev/urandom", 'rb' ) as f:
		return jsonify(  result=ord( f.read( 1 ) ) )

@app.route( '/' )
def index():
	return render_template( 'index.html' )

def serial_init():
	ser = serial.Serial()
	ser.baudrate = 9600
	ser.port = '/dev/ttyACM0'
	ser.open()

	return ser

def serial_poll(s_dict):
	dev = serial_init()
	s = SensorData(dev, s_dict, 0, 5)
	while True:
		s_dict = s.poll()
		s.wait_for_end()
		print s_dict

if __name__ == "__main__":
	sensor_buffer = {'sensor1': [], 'sensor2': [], 'sensor3': []}
	app.debug = True
	
	#app_thread = threading.Thread( target=app.run, args=() )
	#serial_thread = threading.Thread( target=serial_poll, args=(sensor_buffer, ) )
	#app.run()
	serial_poll(sensor_buffer)
