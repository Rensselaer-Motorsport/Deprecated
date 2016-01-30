/*******************************************************************************
* File Name: Down_Shift_Air.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Down_Shift_Air_H) /* Pins Down_Shift_Air_H */
#define CY_PINS_Down_Shift_Air_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Down_Shift_Air_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Down_Shift_Air__PORT == 15 && ((Down_Shift_Air__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Down_Shift_Air_Write(uint8 value) ;
void    Down_Shift_Air_SetDriveMode(uint8 mode) ;
uint8   Down_Shift_Air_ReadDataReg(void) ;
uint8   Down_Shift_Air_Read(void) ;
uint8   Down_Shift_Air_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Down_Shift_Air_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Down_Shift_Air_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Down_Shift_Air_DM_RES_UP          PIN_DM_RES_UP
#define Down_Shift_Air_DM_RES_DWN         PIN_DM_RES_DWN
#define Down_Shift_Air_DM_OD_LO           PIN_DM_OD_LO
#define Down_Shift_Air_DM_OD_HI           PIN_DM_OD_HI
#define Down_Shift_Air_DM_STRONG          PIN_DM_STRONG
#define Down_Shift_Air_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Down_Shift_Air_MASK               Down_Shift_Air__MASK
#define Down_Shift_Air_SHIFT              Down_Shift_Air__SHIFT
#define Down_Shift_Air_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Down_Shift_Air_PS                     (* (reg8 *) Down_Shift_Air__PS)
/* Data Register */
#define Down_Shift_Air_DR                     (* (reg8 *) Down_Shift_Air__DR)
/* Port Number */
#define Down_Shift_Air_PRT_NUM                (* (reg8 *) Down_Shift_Air__PRT) 
/* Connect to Analog Globals */                                                  
#define Down_Shift_Air_AG                     (* (reg8 *) Down_Shift_Air__AG)                       
/* Analog MUX bux enable */
#define Down_Shift_Air_AMUX                   (* (reg8 *) Down_Shift_Air__AMUX) 
/* Bidirectional Enable */                                                        
#define Down_Shift_Air_BIE                    (* (reg8 *) Down_Shift_Air__BIE)
/* Bit-mask for Aliased Register Access */
#define Down_Shift_Air_BIT_MASK               (* (reg8 *) Down_Shift_Air__BIT_MASK)
/* Bypass Enable */
#define Down_Shift_Air_BYP                    (* (reg8 *) Down_Shift_Air__BYP)
/* Port wide control signals */                                                   
#define Down_Shift_Air_CTL                    (* (reg8 *) Down_Shift_Air__CTL)
/* Drive Modes */
#define Down_Shift_Air_DM0                    (* (reg8 *) Down_Shift_Air__DM0) 
#define Down_Shift_Air_DM1                    (* (reg8 *) Down_Shift_Air__DM1)
#define Down_Shift_Air_DM2                    (* (reg8 *) Down_Shift_Air__DM2) 
/* Input Buffer Disable Override */
#define Down_Shift_Air_INP_DIS                (* (reg8 *) Down_Shift_Air__INP_DIS)
/* LCD Common or Segment Drive */
#define Down_Shift_Air_LCD_COM_SEG            (* (reg8 *) Down_Shift_Air__LCD_COM_SEG)
/* Enable Segment LCD */
#define Down_Shift_Air_LCD_EN                 (* (reg8 *) Down_Shift_Air__LCD_EN)
/* Slew Rate Control */
#define Down_Shift_Air_SLW                    (* (reg8 *) Down_Shift_Air__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Down_Shift_Air_PRTDSI__CAPS_SEL       (* (reg8 *) Down_Shift_Air__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Down_Shift_Air_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Down_Shift_Air__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Down_Shift_Air_PRTDSI__OE_SEL0        (* (reg8 *) Down_Shift_Air__PRTDSI__OE_SEL0) 
#define Down_Shift_Air_PRTDSI__OE_SEL1        (* (reg8 *) Down_Shift_Air__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Down_Shift_Air_PRTDSI__OUT_SEL0       (* (reg8 *) Down_Shift_Air__PRTDSI__OUT_SEL0) 
#define Down_Shift_Air_PRTDSI__OUT_SEL1       (* (reg8 *) Down_Shift_Air__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Down_Shift_Air_PRTDSI__SYNC_OUT       (* (reg8 *) Down_Shift_Air__PRTDSI__SYNC_OUT) 


#if defined(Down_Shift_Air__INTSTAT)  /* Interrupt Registers */

    #define Down_Shift_Air_INTSTAT                (* (reg8 *) Down_Shift_Air__INTSTAT)
    #define Down_Shift_Air_SNAP                   (* (reg8 *) Down_Shift_Air__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Down_Shift_Air_H */


/* [] END OF FILE */
