/*******************************************************************************
* File Name: main.c
*
*Adaptable Automotive Data Logger
*
* Version: 1.0
*
*******************************************************************************/

#include <device.h>
#include "stdio.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

/* The size of the buffer is equal to maximum packet size of the 
*  IN and OUT bulk endpoints. 
*/
#define BUFFER_LEN  64u

char8 *parity[] = { "None", "Odd", "Even", "Mark", "Space" };
char8 *stop[] = { "1", "1.5", "2" };

void main()
{
    uint16 count;
    uint8 buffer[BUFFER_LEN];
    char8 lineStr[20];
    uint8 state;
    
    /* Enable Global Interrupts */
    CyGlobalIntEnable;                        

    /* Start USBFS Operation with 3V operation */
    USBUART_1_Start(0u, USBUART_1_3V_OPERATION);

    /* Start LCD */
    LCD_Start();
    LCD_PrintString("USB-UART example");
    
    /* Wait for Device to enumerate */
    while(!USBUART_1_GetConfiguration());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_1_CDC_Init();

    /* Main Loop: */
    for(;;)
    {
        if(USBUART_1_DataIsReady() != 0u)               /* Check for input data from PC */
        {   
            count = USBUART_1_GetAll(buffer);           /* Read received data and re-enable OUT endpoint */
            if(count != 0u)
            {
                while(USBUART_1_CDCIsReady() == 0u);    /* Wait till component is ready to send more data to the PC */ 
                USBUART_1_PutData(buffer, count);       /* Send data back to PC */
                /* If the last sent packet is exactly maximum packet size, 
                *  it shall be followed by a zero-length packet to assure the
                *  end of segment is properly identified by the terminal.
                */
                if(count == BUFFER_LEN)
                {
                    while(USBUART_1_CDCIsReady() == 0u); /* Wait till component is ready to send more data to the PC */ 
                    USBUART_1_PutData(NULL, 0u);         /* Send zero-length packet to PC */
                }
            }
        }  
        
        state = USBUART_1_IsLineChanged();              /* Check for Line settings changed */
        if(state != 0u)
        {  
            if(state & USBUART_1_LINE_CODING_CHANGED)   /* Show new settings */
            {
                sprintf(lineStr,"BR:%4ld,DB:%d",USBUART_1_GetDTERate(),(uint16)USBUART_1_GetDataBits());
                LCD_Position(0u, 0u);
                LCD_PrintString("                    ");
                LCD_Position(0u, 0u);
                LCD_PrintString(lineStr);
                sprintf(lineStr,"SB:%s,Parity:%s", stop[(uint16)USBUART_1_GetCharFormat()], \
                                                     parity[(uint16)USBUART_1_GetParityType()]);
                LCD_Position(1u, 0u);
                LCD_PrintString("                    ");
                LCD_Position(1u, 0u);
                LCD_PrintString(lineStr);
            }
            if(state & USBUART_1_LINE_CONTROL_CHANGED)  /* Show new settings */
            {   
                state = USBUART_1_GetLineControl();
                sprintf(lineStr,"DTR:%s,RTS:%s",  (state & USBUART_1_LINE_CONTROL_DTR) ? "ON" : "OFF", \
                                                    (state & USBUART_1_LINE_CONTROL_RTS) ? "ON" : "OFF");
                LCD_Position(1u, 0u);
                LCD_PrintString("                    ");
                LCD_Position(1u, 0u);
                LCD_PrintString(lineStr);
            
            }
        }
    }   
}

/* [] END OF FILE */
