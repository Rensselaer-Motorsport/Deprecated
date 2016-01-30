/*******************************************************************************
* File Name: Steering_Wheel.h  
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

#if !defined(CY_PINS_Steering_Wheel_H) /* Pins Steering_Wheel_H */
#define CY_PINS_Steering_Wheel_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Steering_Wheel_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Steering_Wheel__PORT == 15 && ((Steering_Wheel__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Steering_Wheel_Write(uint8 value) ;
void    Steering_Wheel_SetDriveMode(uint8 mode) ;
uint8   Steering_Wheel_ReadDataReg(void) ;
uint8   Steering_Wheel_Read(void) ;
uint8   Steering_Wheel_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Steering_Wheel_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Steering_Wheel_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Steering_Wheel_DM_RES_UP          PIN_DM_RES_UP
#define Steering_Wheel_DM_RES_DWN         PIN_DM_RES_DWN
#define Steering_Wheel_DM_OD_LO           PIN_DM_OD_LO
#define Steering_Wheel_DM_OD_HI           PIN_DM_OD_HI
#define Steering_Wheel_DM_STRONG          PIN_DM_STRONG
#define Steering_Wheel_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Steering_Wheel_MASK               Steering_Wheel__MASK
#define Steering_Wheel_SHIFT              Steering_Wheel__SHIFT
#define Steering_Wheel_WIDTH              3u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Steering_Wheel_PS                     (* (reg8 *) Steering_Wheel__PS)
/* Data Register */
#define Steering_Wheel_DR                     (* (reg8 *) Steering_Wheel__DR)
/* Port Number */
#define Steering_Wheel_PRT_NUM                (* (reg8 *) Steering_Wheel__PRT) 
/* Connect to Analog Globals */                                                  
#define Steering_Wheel_AG                     (* (reg8 *) Steering_Wheel__AG)                       
/* Analog MUX bux enable */
#define Steering_Wheel_AMUX                   (* (reg8 *) Steering_Wheel__AMUX) 
/* Bidirectional Enable */                                                        
#define Steering_Wheel_BIE                    (* (reg8 *) Steering_Wheel__BIE)
/* Bit-mask for Aliased Register Access */
#define Steering_Wheel_BIT_MASK               (* (reg8 *) Steering_Wheel__BIT_MASK)
/* Bypass Enable */
#define Steering_Wheel_BYP                    (* (reg8 *) Steering_Wheel__BYP)
/* Port wide control signals */                                                   
#define Steering_Wheel_CTL                    (* (reg8 *) Steering_Wheel__CTL)
/* Drive Modes */
#define Steering_Wheel_DM0                    (* (reg8 *) Steering_Wheel__DM0) 
#define Steering_Wheel_DM1                    (* (reg8 *) Steering_Wheel__DM1)
#define Steering_Wheel_DM2                    (* (reg8 *) Steering_Wheel__DM2) 
/* Input Buffer Disable Override */
#define Steering_Wheel_INP_DIS                (* (reg8 *) Steering_Wheel__INP_DIS)
/* LCD Common or Segment Drive */
#define Steering_Wheel_LCD_COM_SEG            (* (reg8 *) Steering_Wheel__LCD_COM_SEG)
/* Enable Segment LCD */
#define Steering_Wheel_LCD_EN                 (* (reg8 *) Steering_Wheel__LCD_EN)
/* Slew Rate Control */
#define Steering_Wheel_SLW                    (* (reg8 *) Steering_Wheel__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Steering_Wheel_PRTDSI__CAPS_SEL       (* (reg8 *) Steering_Wheel__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Steering_Wheel_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Steering_Wheel__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Steering_Wheel_PRTDSI__OE_SEL0        (* (reg8 *) Steering_Wheel__PRTDSI__OE_SEL0) 
#define Steering_Wheel_PRTDSI__OE_SEL1        (* (reg8 *) Steering_Wheel__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Steering_Wheel_PRTDSI__OUT_SEL0       (* (reg8 *) Steering_Wheel__PRTDSI__OUT_SEL0) 
#define Steering_Wheel_PRTDSI__OUT_SEL1       (* (reg8 *) Steering_Wheel__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Steering_Wheel_PRTDSI__SYNC_OUT       (* (reg8 *) Steering_Wheel__PRTDSI__SYNC_OUT) 


#if defined(Steering_Wheel__INTSTAT)  /* Interrupt Registers */

    #define Steering_Wheel_INTSTAT                (* (reg8 *) Steering_Wheel__INTSTAT)
    #define Steering_Wheel_SNAP                   (* (reg8 *) Steering_Wheel__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Steering_Wheel_H */


/* [] END OF FILE */
