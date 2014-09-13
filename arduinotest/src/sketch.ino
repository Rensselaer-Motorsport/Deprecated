struct sensorData
{
	int data1;
	int data2;
	char data3;
};

union data
{
	unsigned char buffer[sizeof(sensorData)];
	sensorData vars;
};

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	data sendData;
	
	sendData.vars.data1 = random(73);
	sendData.vars.data2 = random(73);
	sendData.vars.data3 = (unsigned char)random(73);
	Serial.write(sendData.buffer, sizeof(sensorData));
}
