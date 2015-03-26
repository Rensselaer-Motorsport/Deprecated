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
#define MPU 0x68


int16 bytecombine(uint8,uint8); //Combines high and low bytes to form a 16 bit int
int16 readacc(int16); //Reads from the accelerometer and returns a 16 bit int
void I2CInit(); //Initializes the accelerometer with the range,etc.

int16 bytecombine(uint8 msb, uint8 lsb) //Used for combining the high and low bytes from the accelerometer
{
    //Takes a msbyte and lsbyte, msb 8 bits with sign bit, lsb 4 bits with last 4 zero.
    int16 temp = msb;
    temp <<= 8; //shift 8 most significant bits into high byte
    temp = temp | lsb; //add lower 8 bits 
    return temp;
}

int16 readacc(int16 address) //address is the address of the first register for the axis you want to read from
{
    //address = 3B for X axis
    //        = 3D for Y axis
    //        = 3F for Z axis
    I2C_1_I2CMasterSendStart(MPU,I2C_1_I2C_WRITE_XFER_MODE); //2nd parameter: 0 for write, 1 for reading
    I2C_1_I2CMasterWriteByte(address); //Select which register to read from
    I2C_1_I2CMasterSendRestart(MPU,I2C_1_I2C_READ_XFER_MODE);
    uint8 msb = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA);
    I2C_1_I2CMasterSendRestart(MPU,I2C_1_I2C_READ_XFER_MODE);
    uint8 lsb = I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA);
    I2C_1_I2CMasterSendStop();
    return bytecombine(msb,lsb);
}

void I2CInit()
{
    I2C_1_Start(); //Turn on the I2c component first
    //Sets the configuration of the accelerometer
    I2C_1_I2CMasterSendStart(MPU,I2C_1_I2C_WRITE_XFER_MODE);
    I2C_1_I2CMasterWriteByte(0x1C); //Address of ACCEL_CONFIG
    //I2C_1_I2CMasterSendRestart(MPU,I2C_1_I2C_WRITE_XFER_MODE);
    I2C_1_I2CMasterWriteByte(0x18); //Set range to +-16G
    I2C_1_I2CMasterSendStop();
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyGlobalIntEnable;

    CyDelay(1);
    I2CInit();
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        uint16 accx = readacc(0x1C); //3B for x axis
        char string[15];
        sprintf(string,"%d",accx);
        CyDelay(10);
    }
}

/* [] END OF FILE */
