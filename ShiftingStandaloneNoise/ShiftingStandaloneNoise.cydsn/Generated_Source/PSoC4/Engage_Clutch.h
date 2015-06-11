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
#include "Engage_Clutch_aliases.h"


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
#define Engage_Clutch_DRIVE_MODE_BITS        (3)
#define Engage_Clutch_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Engage_Clutch_DRIVE_MODE_BITS))

#define Engage_Clutch_DM_ALG_HIZ         (0x00u)
#define Engage_Clutch_DM_DIG_HIZ         (0x01u)
#define Engage_Clutch_DM_RES_UP          (0x02u)
#define Engage_Clutch_DM_RES_DWN         (0x03u)
#define Engage_Clutch_DM_OD_LO           (0x04u)
#define Engage_Clutch_DM_OD_HI           (0x05u)
#define Engage_Clutch_DM_STRONG          (0x06u)
#define Engage_Clutch_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Engage_Clutch_MASK               Engage_Clutch__MASK
#define Engage_Clutch_SHIFT              Engage_Clutch__SHIFT
#define Engage_Clutch_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Engage_Clutch_PS                     (* (reg32 *) Engage_Clutch__PS)
/* Port Configuration */
#define Engage_Clutch_PC                     (* (reg32 *) Engage_Clutch__PC)
/* Data Register */
#define Engage_Clutch_DR                     (* (reg32 *) Engage_Clutch__DR)
/* Input Buffer Disable Override */
#define Engage_Clutch_INP_DIS                (* (reg32 *) Engage_Clutch__PC2)


#if defined(Engage_Clutch__INTSTAT)  /* Interrupt Registers */

    #define Engage_Clutch_INTSTAT                (* (reg32 *) Engage_Clutch__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Engage_Clutch_DRIVE_MODE_SHIFT       (0x00u)
#define Engage_Clutch_DRIVE_MODE_MASK        (0x07u << Engage_Clutch_DRIVE_MODE_SHIFT)


#endif /* End Pins Engage_Clutch_H */


/* [] END OF FILE */
