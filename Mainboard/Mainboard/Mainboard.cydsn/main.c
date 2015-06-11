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

#define BEGIN_PAD_SIZE 5

int msg_count = 0;

union data {
    struct sensorDataInternals {
        char beginPad[BEGIN_PAD_SIZE];
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
    char buffer[sizeof(struct sensorDataInternals)];
} sendData;

void ReadSerial() {
    char rxData;
    while (UART_1_GetRxBufferSize() != 0) {
        rxData = UART_1_GetChar();
        if (msg_count == sizeof(sendData)) msg_count = 0;
        if (msg_count < BEGIN_PAD_SIZE && rxData == msg_count) msg_count++;
        else if (msg_count < BEGIN_PAD_SIZE && rxData != msg_count) msg_count = 0;
        else {
            sendData.buffer[msg_count] = rxData;
            msg_count++;
        }
    }
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_1_Start();
    isr_1_StartEx(*ReadSerial);
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
