def getRandom():
	with open( "/dev/urandom", 'rb' ) as f:
		temp = f.read( 1 )
		temp2 = ord( temp )
		print( temp2 )

while True:
	getRandom()
