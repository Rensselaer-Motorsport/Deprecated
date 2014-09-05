/*******************************************************************************
* File Name: USBUART_1_Dm.c  
* Version 2.0
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
#include "USBUART_1_Dm.h"


/*******************************************************************************
* Function Name: USBUART_1_Dm_Write
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
void USBUART_1_Dm_Write(uint8 value) 
{
    uint8 staticBits = (USBUART_1_Dm_DR & (uint8)(~USBUART_1_Dm_MASK));
    USBUART_1_Dm_DR = staticBits | ((uint8)(value << USBUART_1_Dm_SHIFT) & USBUART_1_Dm_MASK);
}


/*******************************************************************************
* Function Name: USBUART_1_Dm_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  USBUART_1_Dm_DM_STRONG     Strong Drive 
*  USBUART_1_Dm_DM_OD_HI      Open Drain, Drives High 
*  USBUART_1_Dm_DM_OD_LO      Open Drain, Drives Low 
*  USBUART_1_Dm_DM_RES_UP     Resistive Pull Up 
*  USBUART_1_Dm_DM_RES_DWN    Resistive Pull Down 
*  USBUART_1_Dm_DM_RES_UPDWN  Resistive Pull Up/Down 
*  USBUART_1_Dm_DM_DIG_HIZ    High Impedance Digital 
*  USBUART_1_Dm_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void USBUART_1_Dm_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(USBUART_1_Dm_0, mode);
}


/*******************************************************************************
* Function Name: USBUART_1_Dm_Read
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
*  Macro USBUART_1_Dm_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 USBUART_1_Dm_Read(void) 
{
    return (USBUART_1_Dm_PS & USBUART_1_Dm_MASK) >> USBUART_1_Dm_SHIFT;
}


/*******************************************************************************
* Function Name: USBUART_1_Dm_ReadDataReg
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
uint8 USBUART_1_Dm_ReadDataReg(void) 
{
    return (USBUART_1_Dm_DR & USBUART_1_Dm_MASK) >> USBUART_1_Dm_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(USBUART_1_Dm_INTSTAT) 

    /*******************************************************************************
    * Function Name: USBUART_1_Dm_ClearInterrupt
    ********************************************************************************
    *
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
    uint8 USBUART_1_Dm_ClearInterrupt(void) 
    {
        return (USBUART_1_Dm_INTSTAT & USBUART_1_Dm_MASK) >> USBUART_1_Dm_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
