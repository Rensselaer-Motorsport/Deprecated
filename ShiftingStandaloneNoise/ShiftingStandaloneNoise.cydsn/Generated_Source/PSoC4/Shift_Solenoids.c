/*******************************************************************************
* File Name: Shift_Solenoids.c  
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
#include "Shift_Solenoids.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Shift_Solenoids_PC =   (Shift_Solenoids_PC & \
                                (uint32)(~(uint32)(Shift_Solenoids_DRIVE_MODE_IND_MASK << (Shift_Solenoids_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Shift_Solenoids_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Shift_Solenoids_Write
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
void Shift_Solenoids_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Shift_Solenoids_DR & (uint8)(~Shift_Solenoids_MASK));
    drVal = (drVal | ((uint8)(value << Shift_Solenoids_SHIFT) & Shift_Solenoids_MASK));
    Shift_Solenoids_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Shift_Solenoids_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Shift_Solenoids_DM_STRONG     Strong Drive 
*  Shift_Solenoids_DM_OD_HI      Open Drain, Drives High 
*  Shift_Solenoids_DM_OD_LO      Open Drain, Drives Low 
*  Shift_Solenoids_DM_RES_UP     Resistive Pull Up 
*  Shift_Solenoids_DM_RES_DWN    Resistive Pull Down 
*  Shift_Solenoids_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Shift_Solenoids_DM_DIG_HIZ    High Impedance Digital 
*  Shift_Solenoids_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Shift_Solenoids_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Shift_Solenoids__0__SHIFT, mode);
	SetP4PinDriveMode(Shift_Solenoids__1__SHIFT, mode);
	SetP4PinDriveMode(Shift_Solenoids__2__SHIFT, mode);
	SetP4PinDriveMode(Shift_Solenoids__3__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Shift_Solenoids_Read
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
*  Macro Shift_Solenoids_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Shift_Solenoids_Read(void) 
{
    return (uint8)((Shift_Solenoids_PS & Shift_Solenoids_MASK) >> Shift_Solenoids_SHIFT);
}


/*******************************************************************************
* Function Name: Shift_Solenoids_ReadDataReg
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
uint8 Shift_Solenoids_ReadDataReg(void) 
{
    return (uint8)((Shift_Solenoids_DR & Shift_Solenoids_MASK) >> Shift_Solenoids_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Shift_Solenoids_INTSTAT) 

    /*******************************************************************************
    * Function Name: Shift_Solenoids_ClearInterrupt
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
    uint8 Shift_Solenoids_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Shift_Solenoids_INTSTAT & Shift_Solenoids_MASK);
		Shift_Solenoids_INTSTAT = maskedStatus;
        return maskedStatus >> Shift_Solenoids_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
