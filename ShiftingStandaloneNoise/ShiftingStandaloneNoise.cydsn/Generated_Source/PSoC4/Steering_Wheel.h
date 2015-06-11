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
#include "Steering_Wheel_aliases.h"


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
#define Steering_Wheel_DRIVE_MODE_BITS        (3)
#define Steering_Wheel_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Steering_Wheel_DRIVE_MODE_BITS))

#define Steering_Wheel_DM_ALG_HIZ         (0x00u)
#define Steering_Wheel_DM_DIG_HIZ         (0x01u)
#define Steering_Wheel_DM_RES_UP          (0x02u)
#define Steering_Wheel_DM_RES_DWN         (0x03u)
#define Steering_Wheel_DM_OD_LO           (0x04u)
#define Steering_Wheel_DM_OD_HI           (0x05u)
#define Steering_Wheel_DM_STRONG          (0x06u)
#define Steering_Wheel_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Steering_Wheel_MASK               Steering_Wheel__MASK
#define Steering_Wheel_SHIFT              Steering_Wheel__SHIFT
#define Steering_Wheel_WIDTH              3u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Steering_Wheel_PS                     (* (reg32 *) Steering_Wheel__PS)
/* Port Configuration */
#define Steering_Wheel_PC                     (* (reg32 *) Steering_Wheel__PC)
/* Data Register */
#define Steering_Wheel_DR                     (* (reg32 *) Steering_Wheel__DR)
/* Input Buffer Disable Override */
#define Steering_Wheel_INP_DIS                (* (reg32 *) Steering_Wheel__PC2)


#if defined(Steering_Wheel__INTSTAT)  /* Interrupt Registers */

    #define Steering_Wheel_INTSTAT                (* (reg32 *) Steering_Wheel__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Steering_Wheel_DRIVE_MODE_SHIFT       (0x00u)
#define Steering_Wheel_DRIVE_MODE_MASK        (0x07u << Steering_Wheel_DRIVE_MODE_SHIFT)


#endif /* End Pins Steering_Wheel_H */


/* [] END OF FILE */
