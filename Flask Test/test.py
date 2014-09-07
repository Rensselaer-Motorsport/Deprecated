from flask import Flask
app = Flask( __name__ )

@app.route( "/" )
def getRandom():
	with open( "/dev/urandom", 'rb' ) as f:
		return repr( ord( f.read( 1 ) ) )

@app.route( "/hello" )
def getJorel():
	return "Jorel"

if __name__ == "__main__":
	app.run()
