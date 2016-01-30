/*******************************************************************************
* File Name: Engage_Clutch.h  
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

#if !defined(CY_PINS_Engage_Clutch_H) /* Pins Engage_Clutch_H */
#define CY_PINS_Engage_Clutch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Engage_Clutch_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Engage_Clutch__PORT == 15 && ((Engage_Clutch__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Engage_Clutch_Write(uint8 value) ;
void    Engage_Clutch_SetDriveMode(uint8 mode) ;
uint8   Engage_Clutch_ReadDataReg(void) ;
uint8   Engage_Clutch_Read(void) ;
uint8   Engage_Clutch_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Engage_Clutch_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Engage_Clutch_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Engage_Clutch_DM_RES_UP          PIN_DM_RES_UP
#define Engage_Clutch_DM_RES_DWN         PIN_DM_RES_DWN
#define Engage_Clutch_DM_OD_LO           PIN_DM_OD_LO
#define Engage_Clutch_DM_OD_HI           PIN_DM_OD_HI
#define Engage_Clutch_DM_STRONG          PIN_DM_STRONG
#define Engage_Clutch_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Engage_Clutch_MASK               Engage_Clutch__MASK
#define Engage_Clutch_SHIFT              Engage_Clutch__SHIFT
#define Engage_Clutch_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Engage_Clutch_PS                     (* (reg8 *) Engage_Clutch__PS)
/* Data Register */
#define Engage_Clutch_DR                     (* (reg8 *) Engage_Clutch__DR)
/* Port Number */
#define Engage_Clutch_PRT_NUM                (* (reg8 *) Engage_Clutch__PRT) 
/* Connect to Analog Globals */                                                  
#define Engage_Clutch_AG                     (* (reg8 *) Engage_Clutch__AG)                       
/* Analog MUX bux enable */
#define Engage_Clutch_AMUX                   (* (reg8 *) Engage_Clutch__AMUX) 
/* Bidirectional Enable */                                                        
#define Engage_Clutch_BIE                    (* (reg8 *) Engage_Clutch__BIE)
/* Bit-mask for Aliased Register Access */
#define Engage_Clutch_BIT_MASK               (* (reg8 *) Engage_Clutch__BIT_MASK)
/* Bypass Enable */
#define Engage_Clutch_BYP                    (* (reg8 *) Engage_Clutch__BYP)
/* Port wide control signals */                                                   
#define Engage_Clutch_CTL                    (* (reg8 *) Engage_Clutch__CTL)
/* Drive Modes */
#define Engage_Clutch_DM0                    (* (reg8 *) Engage_Clutch__DM0) 
#define Engage_Clutch_DM1                    (* (reg8 *) Engage_Clutch__DM1)
#define Engage_Clutch_DM2                    (* (reg8 *) Engage_Clutch__DM2) 
/* Input Buffer Disable Override */
#define Engage_Clutch_INP_DIS                (* (reg8 *) Engage_Clutch__INP_DIS)
/* LCD Common or Segment Drive */
#define Engage_Clutch_LCD_COM_SEG            (* (reg8 *) Engage_Clutch__LCD_COM_SEG)
/* Enable Segment LCD */
#define Engage_Clutch_LCD_EN                 (* (reg8 *) Engage_Clutch__LCD_EN)
/* Slew Rate Control */
#define Engage_Clutch_SLW                    (* (reg8 *) Engage_Clutch__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Engage_Clutch_PRTDSI__CAPS_SEL       (* (reg8 *) Engage_Clutch__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Engage_Clutch_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Engage_Clutch__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Engage_Clutch_PRTDSI__OE_SEL0        (* (reg8 *) Engage_Clutch__PRTDSI__OE_SEL0) 
#define Engage_Clutch_PRTDSI__OE_SEL1        (* (reg8 *) Engage_Clutch__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Engage_Clutch_PRTDSI__OUT_SEL0       (* (reg8 *) Engage_Clutch__PRTDSI__OUT_SEL0) 
#define Engage_Clutch_PRTDSI__OUT_SEL1       (* (reg8 *) Engage_Clutch__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Engage_Clutch_PRTDSI__SYNC_OUT       (* (reg8 *) Engage_Clutch__PRTDSI__SYNC_OUT) 


#if defined(Engage_Clutch__INTSTAT)  /* Interrupt Registers */

    #define Engage_Clutch_INTSTAT                (* (reg8 *) Engage_Clutch__INTSTAT)
    #define Engage_Clutch_SNAP                   (* (reg8 *) Engage_Clutch__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Engage_Clutch_H */


/* [] END OF FILE */
