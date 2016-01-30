/*******************************************************************************
* File Name: Engage_Clutch.c  
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
#include "Engage_Clutch.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Engage_Clutch__PORT == 15 && ((Engage_Clutch__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Engage_Clutch_Write
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
void Engage_Clutch_Write(uint8 value) 
{
    uint8 staticBits = (Engage_Clutch_DR & (uint8)(~Engage_Clutch_MASK));
    Engage_Clutch_DR = staticBits | ((uint8)(value << Engage_Clutch_SHIFT) & Engage_Clutch_MASK);
}


/*******************************************************************************
* Function Name: Engage_Clutch_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Engage_Clutch_DM_STRONG     Strong Drive 
*  Engage_Clutch_DM_OD_HI      Open Drain, Drives High 
*  Engage_Clutch_DM_OD_LO      Open Drain, Drives Low 
*  Engage_Clutch_DM_RES_UP     Resistive Pull Up 
*  Engage_Clutch_DM_RES_DWN    Resistive Pull Down 
*  Engage_Clutch_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Engage_Clutch_DM_DIG_HIZ    High Impedance Digital 
*  Engage_Clutch_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Engage_Clutch_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Engage_Clutch_0, mode);
}


/*******************************************************************************
* Function Name: Engage_Clutch_Read
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
*  Macro Engage_Clutch_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Engage_Clutch_Read(void) 
{
    return (Engage_Clutch_PS & Engage_Clutch_MASK) >> Engage_Clutch_SHIFT;
}


/*******************************************************************************
* Function Name: Engage_Clutch_ReadDataReg
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
uint8 Engage_Clutch_ReadDataReg(void) 
{
    return (Engage_Clutch_DR & Engage_Clutch_MASK) >> Engage_Clutch_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Engage_Clutch_INTSTAT) 

    /*******************************************************************************
    * Function Name: Engage_Clutch_ClearInterrupt
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
    uint8 Engage_Clutch_ClearInterrupt(void) 
    {
        return (Engage_Clutch_INTSTAT & Engage_Clutch_MASK) >> Engage_Clutch_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
