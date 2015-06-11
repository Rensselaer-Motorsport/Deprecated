/*******************************************************************************
* File Name: ENGAGE_CLUTCH.h  
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

#if !defined(CY_PINS_ENGAGE_CLUTCH_H) /* Pins ENGAGE_CLUTCH_H */
#define CY_PINS_ENGAGE_CLUTCH_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ENGAGE_CLUTCH_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ENGAGE_CLUTCH_Write(uint8 value) ;
void    ENGAGE_CLUTCH_SetDriveMode(uint8 mode) ;
uint8   ENGAGE_CLUTCH_ReadDataReg(void) ;
uint8   ENGAGE_CLUTCH_Read(void) ;
uint8   ENGAGE_CLUTCH_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ENGAGE_CLUTCH_DRIVE_MODE_BITS        (3)
#define ENGAGE_CLUTCH_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ENGAGE_CLUTCH_DRIVE_MODE_BITS))

#define ENGAGE_CLUTCH_DM_ALG_HIZ         (0x00u)
#define ENGAGE_CLUTCH_DM_DIG_HIZ         (0x01u)
#define ENGAGE_CLUTCH_DM_RES_UP          (0x02u)
#define ENGAGE_CLUTCH_DM_RES_DWN         (0x03u)
#define ENGAGE_CLUTCH_DM_OD_LO           (0x04u)
#define ENGAGE_CLUTCH_DM_OD_HI           (0x05u)
#define ENGAGE_CLUTCH_DM_STRONG          (0x06u)
#define ENGAGE_CLUTCH_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ENGAGE_CLUTCH_MASK               ENGAGE_CLUTCH__MASK
#define ENGAGE_CLUTCH_SHIFT              ENGAGE_CLUTCH__SHIFT
#define ENGAGE_CLUTCH_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ENGAGE_CLUTCH_PS                     (* (reg32 *) ENGAGE_CLUTCH__PS)
/* Port Configuration */
#define ENGAGE_CLUTCH_PC                     (* (reg32 *) ENGAGE_CLUTCH__PC)
/* Data Register */
#define ENGAGE_CLUTCH_DR                     (* (reg32 *) ENGAGE_CLUTCH__DR)
/* Input Buffer Disable Override */
#define ENGAGE_CLUTCH_INP_DIS                (* (reg32 *) ENGAGE_CLUTCH__PC2)


#if defined(ENGAGE_CLUTCH__INTSTAT)  /* Interrupt Registers */

    #define ENGAGE_CLUTCH_INTSTAT                (* (reg32 *) ENGAGE_CLUTCH__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ENGAGE_CLUTCH_DRIVE_MODE_SHIFT       (0x00u)
#define ENGAGE_CLUTCH_DRIVE_MODE_MASK        (0x07u << ENGAGE_CLUTCH_DRIVE_MODE_SHIFT)


#endif /* End Pins ENGAGE_CLUTCH_H */


/* [] END OF FILE */
