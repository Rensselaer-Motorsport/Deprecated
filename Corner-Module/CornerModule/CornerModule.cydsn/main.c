/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include "mpu6050.h"

void I2CReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value) {
	uint8_t i=0;
	I2C_MPU6050_I2CMasterSendStart(devAddr, I2C_MPU6050_I2C_WRITE_XFER_MODE);
	I2C_MPU6050_I2CMasterWriteByte(regAddr);
	I2C_MPU6050_I2CMasterSendRestart(devAddr, I2C_MPU6050_I2C_READ_XFER_MODE);
	while (i++ < (length-1)) {
		*value++ = I2C_MPU6050_I2CMasterReadByte(I2C_MPU6050_I2C_ACK_DATA);
	}
	*value = I2C_MPU6050_I2CMasterReadByte(I2C_MPU6050_I2C_NAK_DATA);
	I2C_MPU6050_I2CMasterSendStop();	
}

void I2CReadByte(uint8_t devAddr, uint8_t regAddr, uint8_t *value) {
	I2CReadBytes(devAddr, regAddr, 1, value);
}

void I2CReadBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *value) {
   	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    I2CReadByte(devAddr, regAddr, value);
    *value &= mask;
    *value >>= (bitStart - length + 1);
}

void I2CReadBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *value) {
	I2CReadByte(devAddr, regAddr, value);
	*value = *value & (1 << bitNum);
}
	
void I2CWriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value) {
	uint8_t i=0;
	I2C_MPU6050_I2CMasterSendStart(devAddr, I2C_MPU6050_I2C_WRITE_XFER_MODE);
	I2C_MPU6050_I2CMasterWriteByte(regAddr);
	while (i++ < length) {
		I2C_MPU6050_I2CMasterWriteByte(*value++);
	}
	I2C_MPU6050_I2CMasterSendStop();	
}

void I2CWriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t value) {
	I2CWriteBytes(devAddr, regAddr, 1, &value);
}

void I2CWriteBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t value) {
	uint8_t b;
	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
	I2CReadByte(devAddr, regAddr, &b);
	value <<= (bitStart - length + 1);
	value &= mask;
	b &= ~(mask);
	b |= value;
	I2CWriteByte(devAddr, regAddr, b);	
}

void I2CWriteBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t value) {
	uint8_t b;
	I2CReadByte(devAddr, regAddr, &b);
	b = (value != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	I2CWriteByte(devAddr, regAddr, b);
}

void I2CWriteWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *value) {
	uint8_t i=0;
	I2C_MPU6050_I2CMasterSendStart(devAddr, I2C_MPU6050_I2C_WRITE_XFER_MODE);
	I2C_MPU6050_I2CMasterWriteByte(regAddr);
	while (i++ < length) {
		I2C_MPU6050_I2CMasterWriteByte(((uint8_t)*value) >> 8);
		I2C_MPU6050_I2CMasterWriteByte((uint8_t)*value++);
	}
	I2C_MPU6050_I2CMasterSendStop();		
}

void I2CWriteWord(uint8_t devAddr, uint8_t regAddr, uint16_t value) {
	I2CWriteWords(devAddr, regAddr, 1, &value);
}



union data
{
    struct sensorDataInternals
    {
        char beginPad[5];
        int16_t ax;
        char pad0;
        int16_t ay;
        char pad1;
        int16_t az;
        char pad2;
        int16_t gx;
        char pad3;
        int16_t gy;
        char pad4;
        int16_t gz;
    } sensorData;
    unsigned char buffer[sizeof(struct sensorDataInternals)];
} sendData;

int main()
{
    CyGlobalIntEnable;
    static char temp[5] = {0, 1, 2, 3, 4};
    memcpy(sendData.sensorData.beginPad, temp, 5);
    sendData.sensorData.pad0 = 0;
    sendData.sensorData.pad1 = 0;
    sendData.sensorData.pad2 = 0;
    sendData.sensorData.pad3 = 0;
    sendData.sensorData.pad4 = 0;
    CyDelay(10);
	I2C_MPU6050_Start();
    UART_1_Start();
	
    

	MPU6050_init();
	MPU6050_initialize();
	
    for(;;)
    {
	  MPU6050_getMotion6(&sendData.sensorData.ax, &sendData.sensorData.ay, &sendData.sensorData.az, &sendData.sensorData.gx, &sendData.sensorData.gy, &sendData.sensorData.gz);
      UART_1_PutArray(sendData.buffer, sizeof(sendData.buffer));
      //UART_1_PutString("/n/r");
	}
}

/* [] END OF FILE */