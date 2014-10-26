#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
struct sensorData
{
	char beginPad[5];
	int data1;
	char pad0;
	int data2;
	char pad1;
	int data3;
};

union data
{
	unsigned char buffer[sizeof(sensorData)];
	sensorData vars;
};

data sendData;

void setup()
{
	Serial.begin(9600);
	
	static char temp[5] = {0, 1, 2, 3, 4};
	memcpy(sendData.vars.beginPad, temp, 5);
	sendData.vars.pad0 = 0;
	sendData.vars.pad1 = 0;
}

void loop()
{
	//sendData.vars.data1 = random(73);
	//sendData.vars.data2 = random(73);
	//sendData.vars.data3 = (unsigned char)random(73);
	sendData.vars.data1 = (256);
	sendData.vars.data2 = (512);
	sendData.vars.data3 = (1024);
	Serial.write(sendData.buffer, sizeof(sensorData));
}
