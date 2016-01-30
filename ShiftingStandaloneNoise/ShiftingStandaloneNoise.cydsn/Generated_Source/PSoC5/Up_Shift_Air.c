/*******************************************************************************
* File Name: Up_Shift_Air.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Up_Shift_Air.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Up_Shift_Air__PORT == 15 && ((Up_Shift_Air__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Up_Shift_Air_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void Up_Shift_Air_Write(uint8 value) 
{
    uint8 staticBits = (Up_Shift_Air_DR & (uint8)(~Up_Shift_Air_MASK));
    Up_Shift_Air_DR = staticBits | ((uint8)(value << Up_Shift_Air_SHIFT) & Up_Shift_Air_MASK);
}


/*******************************************************************************
* Function Name: Up_Shift_Air_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Up_Shift_Air_DM_STRONG     Strong Drive 
*  Up_Shift_Air_DM_OD_HI      Open Drain, Drives High 
*  Up_Shift_Air_DM_OD_LO      Open Drain, Drives Low 
*  Up_Shift_Air_DM_RES_UP     Resistive Pull Up 
*  Up_Shift_Air_DM_RES_DWN    Resistive Pull Down 
*  Up_Shift_Air_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Up_Shift_Air_DM_DIG_HIZ    High Impedance Digital 
*  Up_Shift_Air_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Up_Shift_Air_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Up_Shift_Air_0, mode);
}


/*******************************************************************************
* Function Name: Up_Shift_Air_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Up_Shift_Air_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Up_Shift_Air_Read(void) 
{
    return (Up_Shift_Air_PS & Up_Shift_Air_MASK) >> Up_Shift_Air_SHIFT;
}


/*******************************************************************************
* Function Name: Up_Shift_Air_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Up_Shift_Air_ReadDataReg(void) 
{
    return (Up_Shift_Air_DR & Up_Shift_Air_MASK) >> Up_Shift_Air_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Up_Shift_Air_INTSTAT) 

    /*******************************************************************************
    * Function Name: Up_Shift_Air_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Up_Shift_Air_ClearInterrupt(void) 
    {
        return (Up_Shift_Air_INTSTAT & Up_Shift_Air_MASK) >> Up_Shift_Air_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
