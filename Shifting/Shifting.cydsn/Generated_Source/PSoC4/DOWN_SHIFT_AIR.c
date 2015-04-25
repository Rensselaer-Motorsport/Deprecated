/*******************************************************************************
* File Name: DOWN_SHIFT_AIR.c  
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
#include "DOWN_SHIFT_AIR.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        DOWN_SHIFT_AIR_PC =   (DOWN_SHIFT_AIR_PC & \
                                (uint32)(~(uint32)(DOWN_SHIFT_AIR_DRIVE_MODE_IND_MASK << (DOWN_SHIFT_AIR_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (DOWN_SHIFT_AIR_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: DOWN_SHIFT_AIR_Write
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
void DOWN_SHIFT_AIR_Write(uint8 value) 
{
    uint8 drVal = (uint8)(DOWN_SHIFT_AIR_DR & (uint8)(~DOWN_SHIFT_AIR_MASK));
    drVal = (drVal | ((uint8)(value << DOWN_SHIFT_AIR_SHIFT) & DOWN_SHIFT_AIR_MASK));
    DOWN_SHIFT_AIR_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: DOWN_SHIFT_AIR_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DOWN_SHIFT_AIR_DM_STRONG     Strong Drive 
*  DOWN_SHIFT_AIR_DM_OD_HI      Open Drain, Drives High 
*  DOWN_SHIFT_AIR_DM_OD_LO      Open Drain, Drives Low 
*  DOWN_SHIFT_AIR_DM_RES_UP     Resistive Pull Up 
*  DOWN_SHIFT_AIR_DM_RES_DWN    Resistive Pull Down 
*  DOWN_SHIFT_AIR_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DOWN_SHIFT_AIR_DM_DIG_HIZ    High Impedance Digital 
*  DOWN_SHIFT_AIR_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DOWN_SHIFT_AIR_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(DOWN_SHIFT_AIR__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: DOWN_SHIFT_AIR_Read
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
*  Macro DOWN_SHIFT_AIR_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DOWN_SHIFT_AIR_Read(void) 
{
    return (uint8)((DOWN_SHIFT_AIR_PS & DOWN_SHIFT_AIR_MASK) >> DOWN_SHIFT_AIR_SHIFT);
}


/*******************************************************************************
* Function Name: DOWN_SHIFT_AIR_ReadDataReg
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
uint8 DOWN_SHIFT_AIR_ReadDataReg(void) 
{
    return (uint8)((DOWN_SHIFT_AIR_DR & DOWN_SHIFT_AIR_MASK) >> DOWN_SHIFT_AIR_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DOWN_SHIFT_AIR_INTSTAT) 

    /*******************************************************************************
    * Function Name: DOWN_SHIFT_AIR_ClearInterrupt
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
    uint8 DOWN_SHIFT_AIR_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(DOWN_SHIFT_AIR_INTSTAT & DOWN_SHIFT_AIR_MASK);
		DOWN_SHIFT_AIR_INTSTAT = maskedStatus;
        return maskedStatus >> DOWN_SHIFT_AIR_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
