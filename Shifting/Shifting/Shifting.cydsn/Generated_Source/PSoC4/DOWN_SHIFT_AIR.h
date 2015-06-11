/*******************************************************************************
* File Name: DOWN_SHIFT_AIR.h  
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

#if !defined(CY_PINS_DOWN_SHIFT_AIR_H) /* Pins DOWN_SHIFT_AIR_H */
#define CY_PINS_DOWN_SHIFT_AIR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DOWN_SHIFT_AIR_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DOWN_SHIFT_AIR_Write(uint8 value) ;
void    DOWN_SHIFT_AIR_SetDriveMode(uint8 mode) ;
uint8   DOWN_SHIFT_AIR_ReadDataReg(void) ;
uint8   DOWN_SHIFT_AIR_Read(void) ;
uint8   DOWN_SHIFT_AIR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DOWN_SHIFT_AIR_DRIVE_MODE_BITS        (3)
#define DOWN_SHIFT_AIR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DOWN_SHIFT_AIR_DRIVE_MODE_BITS))

#define DOWN_SHIFT_AIR_DM_ALG_HIZ         (0x00u)
#define DOWN_SHIFT_AIR_DM_DIG_HIZ         (0x01u)
#define DOWN_SHIFT_AIR_DM_RES_UP          (0x02u)
#define DOWN_SHIFT_AIR_DM_RES_DWN         (0x03u)
#define DOWN_SHIFT_AIR_DM_OD_LO           (0x04u)
#define DOWN_SHIFT_AIR_DM_OD_HI           (0x05u)
#define DOWN_SHIFT_AIR_DM_STRONG          (0x06u)
#define DOWN_SHIFT_AIR_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define DOWN_SHIFT_AIR_MASK               DOWN_SHIFT_AIR__MASK
#define DOWN_SHIFT_AIR_SHIFT              DOWN_SHIFT_AIR__SHIFT
#define DOWN_SHIFT_AIR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DOWN_SHIFT_AIR_PS                     (* (reg32 *) DOWN_SHIFT_AIR__PS)
/* Port Configuration */
#define DOWN_SHIFT_AIR_PC                     (* (reg32 *) DOWN_SHIFT_AIR__PC)
/* Data Register */
#define DOWN_SHIFT_AIR_DR                     (* (reg32 *) DOWN_SHIFT_AIR__DR)
/* Input Buffer Disable Override */
#define DOWN_SHIFT_AIR_INP_DIS                (* (reg32 *) DOWN_SHIFT_AIR__PC2)


#if defined(DOWN_SHIFT_AIR__INTSTAT)  /* Interrupt Registers */

    #define DOWN_SHIFT_AIR_INTSTAT                (* (reg32 *) DOWN_SHIFT_AIR__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define DOWN_SHIFT_AIR_DRIVE_MODE_SHIFT       (0x00u)
#define DOWN_SHIFT_AIR_DRIVE_MODE_MASK        (0x07u << DOWN_SHIFT_AIR_DRIVE_MODE_SHIFT)


#endif /* End Pins DOWN_SHIFT_AIR_H */


/* [] END OF FILE */
