/* ========================================
 * Shifting Code v1.0
 * ========================================
*/
#include <project.h>
#include <UP_SHIFT_AIR.h>// i bellive i need this (from documentation, but since i don't have the output port connected to anything on the top design it dosen't like it
#include <ENGAGE_CLUTCH.h>


#define CLUTCH_ENGAGE_DELAY 70
#define CLUTCH_RELEASE_DELAY 20
#define SHIFT_DELAY 165
#define NEUTRAL_FIND 32
#define BEGIN_PAD_SIZE 5
#define UP_SHIFT_PADDLE 1// ??
#define DOWN_SHIFT_PADDLE 0// ??
#define UP_SHIFT_AIR UP_SHIFT_AIR_READ()// is this ok, it didn't throw errors so...
#define DOWN_SHIFT_AIR 1 // this is a thing and I'm not really sure where it comes from

int msg_count = 0;

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
    UART_1_Start();
    isr_1_StartEx(*ReadSerial);

    CyGlobalIntEnable; 
    for(;;)
    {
        if(sendData.serialData.shift == UP_SHIFT_PADDLE){
            shift(UP_SHIFT_AIR);
            while(sendData.serialData.shift == UP_SHIFT_PADDLE);
            //gear++;// do you keep track of this or do I
        }
        if(sendData.serialData.shift == DOWN_SHIFT_PADDLE){
            shift(DOWN_SHIFT_AIR);
            while(sendData.serialData.shift == DOWN_SHIFT_PADDLE){
                UP_SHIFT_AIR_WRITE(1);
                CyDelay(NEUTRAL_FIND);
                while(sendData.serialData.shift == UP_SHIFT_PADDLE);
            }
        }
        CyDelay930);
        //gear--;
    }
}

void Shift(char paddle)
{
    ENGAGE_CLUTCH_WRITE(1);
    CyDelay(CLUTCH_ENGAGE_DELAY);
    paddle_WRITE(1);
    CyDelay(SHIFT_ENGAGE_DELAY);
    paddle_WRITE(0);
    CyDelay(CLUTCH_RELEASE_DELAY);
    ENGAGE_CLUTCH_WRITE(0);


/* [] END OF FILE */
