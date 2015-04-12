/*******************************************************************************
* File Name: pwrisr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_pwrisr_H)
#define CY_ISR_pwrisr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pwrisr_Start(void);
void pwrisr_StartEx(cyisraddress address);
void pwrisr_Stop(void);

CY_ISR_PROTO(pwrisr_Interrupt);

void pwrisr_SetVector(cyisraddress address);
cyisraddress pwrisr_GetVector(void);

void pwrisr_SetPriority(uint8 priority);
uint8 pwrisr_GetPriority(void);

void pwrisr_Enable(void);
uint8 pwrisr_GetState(void);
void pwrisr_Disable(void);

void pwrisr_SetPending(void);
void pwrisr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pwrisr ISR. */
#define pwrisr_INTC_VECTOR            ((reg32 *) pwrisr__INTC_VECT)

/* Address of the pwrisr ISR priority. */
#define pwrisr_INTC_PRIOR             ((reg32 *) pwrisr__INTC_PRIOR_REG)

/* Priority of the pwrisr interrupt. */
#define pwrisr_INTC_PRIOR_NUMBER      pwrisr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pwrisr interrupt. */
#define pwrisr_INTC_SET_EN            ((reg32 *) pwrisr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pwrisr interrupt. */
#define pwrisr_INTC_CLR_EN            ((reg32 *) pwrisr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pwrisr interrupt state to pending. */
#define pwrisr_INTC_SET_PD            ((reg32 *) pwrisr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pwrisr interrupt. */
#define pwrisr_INTC_CLR_PD            ((reg32 *) pwrisr__INTC_CLR_PD_REG)



#endif /* CY_ISR_pwrisr_H */


/* [] END OF FILE */
