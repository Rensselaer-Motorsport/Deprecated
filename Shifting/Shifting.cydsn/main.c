/* ========================================
 * Shifting Code v1.0
 * ========================================
*/
#include <project.h>
#include <cypins.h>

#define CLUTCH_ENGAGE_DELAY 70
#define CLUTCH_RELEASE_DELAY 20
#define SHIFT_DELAY 165
#define SHIFT_ENGAGE_DELAY 1//??
#define NEUTRAL_FIND 32
#define BEGIN_PAD_SIZE 5

int msg_count = 0;
const char up = 'u';
const char down = 'd';
const char neutral = 'n';

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
    char buffer[sizeof(struct serialDataInternals)];
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
    char gear=0;
    UART_1_Start();
    isr_1_StartEx(*ReadSerial);
    CyGlobalIntEnable; 
    //CyDelay(1000);
    
    for(;;)
    {
        if(sendData.serialData.shift == up){
            shift(up);
            while(sendData.serialData.shift == up);
            gear++;// do you keep track of this or do I
        }
        if(sendData.serialData.shift == down){
            shift(down);
            while(sendData.serialData.shift == down);
            gear--;
        }
        if(sendData.serialData.shift == neutral){
            UP_SHIFT_AIR_Write(1);
            CyDelay(NEUTRAL_FIND);
            UP_SHIFT_AIR_Write(0);
            while(sendData.serialData.shift == up);
            CyDelay(30);
            //gear--;
        }
        
    }
}

void shift(char paddle)
{
    ENGAGE_CLUTCH_Write(1);
    CyDelay(CLUTCH_ENGAGE_DELAY);
    if (paddle == 'u') {
        UP_SHIFT_AIR_Write(1);
        CyDelay(SHIFT_ENGAGE_DELAY);
        UP_SHIFT_AIR_Write(0);
        CyDelay(CLUTCH_RELEASE_DELAY);
        ENGAGE_CLUTCH_Write(0);
    } else if (paddle == 'd') {
        DOWN_SHIFT_AIR_Write(1);
        CyDelay(SHIFT_ENGAGE_DELAY);
        DOWN_SHIFT_AIR_Write(0);
        CyDelay(CLUTCH_RELEASE_DELAY);
        ENGAGE_CLUTCH_Write(0);
    }
}

/* [] END OF FILE */
