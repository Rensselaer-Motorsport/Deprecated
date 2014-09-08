from flask import Flask, jsonify, render_template, request
app = Flask( __name__ )

@app.route( '/_random_number' )
def get_random():
	with open( "/dev/urandom", 'rb' ) as f:
		return jsonify(  result=ord( f.read( 1 ) ) )

@app.route( '/' )
def index():
	return render_template( 'index.html' )

if __name__ == "__main__":
	app.debug = True
	app.run()
