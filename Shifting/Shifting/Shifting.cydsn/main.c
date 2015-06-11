/* ========================================
 * Shifting Code v1.0
 * ========================================
*/
#include <project.h>
#include <cypins.h>

#define CLUTCH_ENGAGE_DELAY 70
#define CLUTCH_RELEASE_DELAY 20
#define SHIFT_DELAY 165
#define SHIFT_ENGAGE_DELAY 1
#define NEUTRAL_FIND 32
#define BEGIN_PAD_SIZE 5
#define BUFFER_SIZE 13

int msg_count = 1;
#define up 'u'
#define down 'd'
#define neutral 'n'

void ReadSerial();
void ReadSoftwareBuffer();
void shift(char paddle);

union data
{
    struct serialDataInternals
    {
        char beginPad[BEGIN_PAD_SIZE];
        char shift;
        char pad0;
        int16_t tach;
        char pad1;
        int16_t wheel_speed;
        char pad2;
    } serialData;
    char buffer[BUFFER_SIZE];
} sendData;

int main()
{
    Timer_1_Start();
    UART_1_Start();
    timer_StartEx(ReadSoftwareBuffer);
    CyGlobalIntEnable; 
    CyDelay(10);
    
    for(;;)
    {
        if(sendData.serialData.shift == up){
            //shift(up);
            UP_SHIFT_AIR_Write(1);
            CyDelay(100);
            UP_SHIFT_AIR_Write(0);
            //while(sendData.serialData.shift == up);
        }
        else if(sendData.serialData.shift == down){
            //shift(down);
            DOWN_SHIFT_AIR_Write(1);
            CyDelay(100);
            DOWN_SHIFT_AIR_Write(0);
            //while(sendData.serialData.shift == down);
        }
        else if(sendData.serialData.shift == neutral) {
            ENGAGE_CLUTCH_Write(1);
            CyDelay(100);
            ENGAGE_CLUTCH_Write(0);
            /*
            UP_SHIFT_AIR_Write(1);
            CyDelay(NEUTRAL_FIND);
            UP_SHIFT_AIR_Write(0);
            */
            //while(sendData.serialData.shift == neutral);
            //CyDelay(30);
        }
        CyDelay(5);
    }
}

void ReadSerial()
{
    char rxData;
    while (UART_1_GetRxBufferSize() != 0) {
        rxData = UART_1_GetChar();
        if (msg_count >= (BUFFER_SIZE)){
            msg_count = 1;
        }
        else if (msg_count <= BEGIN_PAD_SIZE && rxData == msg_count) msg_count++;
        else if (msg_count <= BEGIN_PAD_SIZE && rxData != msg_count) msg_count = 1;
        else {
            sendData.buffer[msg_count-1] = rxData;
            msg_count++;
        }
    }
}

void ReadSoftwareBuffer()
{
    if (UART_1_GetRxBufferSize()) ReadSerial();
}

void shift(char paddle)
{
    ENGAGE_CLUTCH_Write(1);
    CyDelay(CLUTCH_ENGAGE_DELAY);
    if (paddle == up) {
        UP_SHIFT_AIR_Write(1);
        CyDelay(SHIFT_ENGAGE_DELAY);
        UP_SHIFT_AIR_Write(0);
        CyDelay(CLUTCH_RELEASE_DELAY);
        ENGAGE_CLUTCH_Write(0);
    } else if (paddle == down) {
        DOWN_SHIFT_AIR_Write(1);
        CyDelay(SHIFT_ENGAGE_DELAY);
        DOWN_SHIFT_AIR_Write(0);
        CyDelay(CLUTCH_RELEASE_DELAY);
        ENGAGE_CLUTCH_Write(0);
    }
}

/* [] END OF FILE */