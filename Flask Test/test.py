from flask import Flask, jsonify, render_template, request
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
	ser.port = 'ttyACM0'
	ser.open()

	return ser

def serial_poll():
	dev = serial_init()
	

if __name__ == "__main__":
	app.debug = True
	
	app_thread = threading.Thread( target=app.run, args=() )
	serial_thread = threading.Thread( target=serial_poll, args=() )
	app.run()
