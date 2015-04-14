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

#define SERIAL_BUFFER_SIZE 1

union data
{
    struct serialDataInternals
    {
        char beginPad[5];
        char shift;
        char pad0;
        int16_t tach;
        char pad1;
        int16_t wheel_speed;
        char pad2;
    } serialData;
    char buffer[SERIAL_BUFFER_SIZE];
} sendData;

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    char rxData;
    UART_1_Start();

    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        // UART_1_PutChar('a');
        while (UART_1_GetRxBufferSize() != 0)
        {
            rxData = UART_1_GetChar();
            CyDelay(1);
        }
    }
}

/* [] END OF FILE */
