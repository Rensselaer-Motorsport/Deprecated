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

int main()
{
    int16_t ax, ay, az;
	int16_t gx, gy, gz;
	char buf[30];

	I2C_MPU6050_Start();
    UART_1_Start();
	
    CyGlobalIntEnable;

	MPU6050_init();
	MPU6050_initialize();
	
    for(;;)
    {
		MPU6050_getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		sprintf(buf, "%d \t", ax);
        UART_1_PutString(buf);
		sprintf(buf, "%d \t", ay);
		sprintf(buf, "%d \t", az);
		sprintf(buf, "%d \t", gx);
		sprintf(buf, "%d \t", gy);
		sprintf(buf, "%d \t", gz);
	}
}

/* [] END OF FILE */