/*******************************************************************************
* File Name: Shift_Solenoids.h  
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

#if !defined(CY_PINS_Shift_Solenoids_H) /* Pins Shift_Solenoids_H */
#define CY_PINS_Shift_Solenoids_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Shift_Solenoids_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Shift_Solenoids_Write(uint8 value) ;
void    Shift_Solenoids_SetDriveMode(uint8 mode) ;
uint8   Shift_Solenoids_ReadDataReg(void) ;
uint8   Shift_Solenoids_Read(void) ;
uint8   Shift_Solenoids_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Shift_Solenoids_DRIVE_MODE_BITS        (3)
#define Shift_Solenoids_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Shift_Solenoids_DRIVE_MODE_BITS))

#define Shift_Solenoids_DM_ALG_HIZ         (0x00u)
#define Shift_Solenoids_DM_DIG_HIZ         (0x01u)
#define Shift_Solenoids_DM_RES_UP          (0x02u)
#define Shift_Solenoids_DM_RES_DWN         (0x03u)
#define Shift_Solenoids_DM_OD_LO           (0x04u)
#define Shift_Solenoids_DM_OD_HI           (0x05u)
#define Shift_Solenoids_DM_STRONG          (0x06u)
#define Shift_Solenoids_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Shift_Solenoids_MASK               Shift_Solenoids__MASK
#define Shift_Solenoids_SHIFT              Shift_Solenoids__SHIFT
#define Shift_Solenoids_WIDTH              4u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Shift_Solenoids_PS                     (* (reg32 *) Shift_Solenoids__PS)
/* Port Configuration */
#define Shift_Solenoids_PC                     (* (reg32 *) Shift_Solenoids__PC)
/* Data Register */
#define Shift_Solenoids_DR                     (* (reg32 *) Shift_Solenoids__DR)
/* Input Buffer Disable Override */
#define Shift_Solenoids_INP_DIS                (* (reg32 *) Shift_Solenoids__PC2)


#if defined(Shift_Solenoids__INTSTAT)  /* Interrupt Registers */

    #define Shift_Solenoids_INTSTAT                (* (reg32 *) Shift_Solenoids__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Shift_Solenoids_DRIVE_MODE_SHIFT       (0x00u)
#define Shift_Solenoids_DRIVE_MODE_MASK        (0x07u << Shift_Solenoids_DRIVE_MODE_SHIFT)


#endif /* End Pins Shift_Solenoids_H */


/* [] END OF FILE */
