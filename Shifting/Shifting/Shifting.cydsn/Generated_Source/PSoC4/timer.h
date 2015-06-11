/*******************************************************************************
* File Name: timer.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_timer_H)
#define CY_ISR_timer_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void timer_Start(void);
void timer_StartEx(cyisraddress address);
void timer_Stop(void);

CY_ISR_PROTO(timer_Interrupt);

void timer_SetVector(cyisraddress address);
cyisraddress timer_GetVector(void);

void timer_SetPriority(uint8 priority);
uint8 timer_GetPriority(void);

void timer_Enable(void);
uint8 timer_GetState(void);
void timer_Disable(void);

void timer_SetPending(void);
void timer_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the timer ISR. */
#define timer_INTC_VECTOR            ((reg32 *) timer__INTC_VECT)

/* Address of the timer ISR priority. */
#define timer_INTC_PRIOR             ((reg32 *) timer__INTC_PRIOR_REG)

/* Priority of the timer interrupt. */
#define timer_INTC_PRIOR_NUMBER      timer__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable timer interrupt. */
#define timer_INTC_SET_EN            ((reg32 *) timer__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the timer interrupt. */
#define timer_INTC_CLR_EN            ((reg32 *) timer__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the timer interrupt state to pending. */
#define timer_INTC_SET_PD            ((reg32 *) timer__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the timer interrupt. */
#define timer_INTC_CLR_PD            ((reg32 *) timer__INTC_CLR_PD_REG)



#endif /* CY_ISR_timer_H */


/* [] END OF FILE */
