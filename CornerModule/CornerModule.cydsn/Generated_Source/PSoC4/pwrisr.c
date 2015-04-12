/*******************************************************************************
* File Name: pwrisr.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <pwrisr.h>

#if !defined(pwrisr__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START pwrisr_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: pwrisr_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_Start(void)
{
    /* For all we know the interrupt is active. */
    pwrisr_Disable();

    /* Set the ISR to point to the pwrisr Interrupt. */
    pwrisr_SetVector(&pwrisr_Interrupt);

    /* Set the priority. */
    pwrisr_SetPriority((uint8)pwrisr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    pwrisr_Enable();
}


/*******************************************************************************
* Function Name: pwrisr_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    pwrisr_Disable();

    /* Set the ISR to point to the pwrisr Interrupt. */
    pwrisr_SetVector(address);

    /* Set the priority. */
    pwrisr_SetPriority((uint8)pwrisr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    pwrisr_Enable();
}


/*******************************************************************************
* Function Name: pwrisr_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_Stop(void)
{
    /* Disable this interrupt. */
    pwrisr_Disable();

    /* Set the ISR to point to the passive one. */
    pwrisr_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: pwrisr_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for pwrisr.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(pwrisr_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START pwrisr_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: pwrisr_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling pwrisr_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use pwrisr_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + pwrisr__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: pwrisr_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress pwrisr_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + pwrisr__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: pwrisr_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling pwrisr_Start
*   or pwrisr_StartEx will override any effect this method would 
*   have had. This method should only be called after pwrisr_Start or 
*   pwrisr_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((pwrisr__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *pwrisr_INTC_PRIOR = (*pwrisr_INTC_PRIOR & (uint32)(~pwrisr__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: pwrisr_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 pwrisr_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((pwrisr__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*pwrisr_INTC_PRIOR & pwrisr__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: pwrisr_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_Enable(void)
{
    /* Enable the general interrupt. */
    *pwrisr_INTC_SET_EN = pwrisr__INTC_MASK;
}


/*******************************************************************************
* Function Name: pwrisr_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 pwrisr_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*pwrisr_INTC_SET_EN & (uint32)pwrisr__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: pwrisr_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_Disable(void)
{
    /* Disable the general interrupt. */
    *pwrisr_INTC_CLR_EN = pwrisr__INTC_MASK;
}


/*******************************************************************************
* Function Name: pwrisr_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_SetPending(void)
{
    *pwrisr_INTC_SET_PD = pwrisr__INTC_MASK;
}


/*******************************************************************************
* Function Name: pwrisr_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void pwrisr_ClearPending(void)
{
    *pwrisr_INTC_CLR_PD = pwrisr__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
