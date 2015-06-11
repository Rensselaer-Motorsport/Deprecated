/*******************************************************************************
* File Name: ENGAGE_CLUTCH.c  
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
#include "ENGAGE_CLUTCH.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ENGAGE_CLUTCH_PC =   (ENGAGE_CLUTCH_PC & \
                                (uint32)(~(uint32)(ENGAGE_CLUTCH_DRIVE_MODE_IND_MASK << (ENGAGE_CLUTCH_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ENGAGE_CLUTCH_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ENGAGE_CLUTCH_Write
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
void ENGAGE_CLUTCH_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ENGAGE_CLUTCH_DR & (uint8)(~ENGAGE_CLUTCH_MASK));
    drVal = (drVal | ((uint8)(value << ENGAGE_CLUTCH_SHIFT) & ENGAGE_CLUTCH_MASK));
    ENGAGE_CLUTCH_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ENGAGE_CLUTCH_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ENGAGE_CLUTCH_DM_STRONG     Strong Drive 
*  ENGAGE_CLUTCH_DM_OD_HI      Open Drain, Drives High 
*  ENGAGE_CLUTCH_DM_OD_LO      Open Drain, Drives Low 
*  ENGAGE_CLUTCH_DM_RES_UP     Resistive Pull Up 
*  ENGAGE_CLUTCH_DM_RES_DWN    Resistive Pull Down 
*  ENGAGE_CLUTCH_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ENGAGE_CLUTCH_DM_DIG_HIZ    High Impedance Digital 
*  ENGAGE_CLUTCH_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ENGAGE_CLUTCH_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ENGAGE_CLUTCH__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ENGAGE_CLUTCH_Read
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
*  Macro ENGAGE_CLUTCH_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ENGAGE_CLUTCH_Read(void) 
{
    return (uint8)((ENGAGE_CLUTCH_PS & ENGAGE_CLUTCH_MASK) >> ENGAGE_CLUTCH_SHIFT);
}


/*******************************************************************************
* Function Name: ENGAGE_CLUTCH_ReadDataReg
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
uint8 ENGAGE_CLUTCH_ReadDataReg(void) 
{
    return (uint8)((ENGAGE_CLUTCH_DR & ENGAGE_CLUTCH_MASK) >> ENGAGE_CLUTCH_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ENGAGE_CLUTCH_INTSTAT) 

    /*******************************************************************************
    * Function Name: ENGAGE_CLUTCH_ClearInterrupt
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
    uint8 ENGAGE_CLUTCH_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ENGAGE_CLUTCH_INTSTAT & ENGAGE_CLUTCH_MASK);
		ENGAGE_CLUTCH_INTSTAT = maskedStatus;
        return maskedStatus >> ENGAGE_CLUTCH_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
