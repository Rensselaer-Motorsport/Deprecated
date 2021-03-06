/*******************************************************************************
* File Name: Down_Shift_In.h  
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

#if !defined(CY_PINS_Down_Shift_In_H) /* Pins Down_Shift_In_H */
#define CY_PINS_Down_Shift_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Down_Shift_In_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Down_Shift_In_Write(uint8 value) ;
void    Down_Shift_In_SetDriveMode(uint8 mode) ;
uint8   Down_Shift_In_ReadDataReg(void) ;
uint8   Down_Shift_In_Read(void) ;
uint8   Down_Shift_In_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Down_Shift_In_DRIVE_MODE_BITS        (3)
#define Down_Shift_In_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Down_Shift_In_DRIVE_MODE_BITS))

#define Down_Shift_In_DM_ALG_HIZ         (0x00u)
#define Down_Shift_In_DM_DIG_HIZ         (0x01u)
#define Down_Shift_In_DM_RES_UP          (0x02u)
#define Down_Shift_In_DM_RES_DWN         (0x03u)
#define Down_Shift_In_DM_OD_LO           (0x04u)
#define Down_Shift_In_DM_OD_HI           (0x05u)
#define Down_Shift_In_DM_STRONG          (0x06u)
#define Down_Shift_In_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Down_Shift_In_MASK               Down_Shift_In__MASK
#define Down_Shift_In_SHIFT              Down_Shift_In__SHIFT
#define Down_Shift_In_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Down_Shift_In_PS                     (* (reg32 *) Down_Shift_In__PS)
/* Port Configuration */
#define Down_Shift_In_PC                     (* (reg32 *) Down_Shift_In__PC)
/* Data Register */
#define Down_Shift_In_DR                     (* (reg32 *) Down_Shift_In__DR)
/* Input Buffer Disable Override */
#define Down_Shift_In_INP_DIS                (* (reg32 *) Down_Shift_In__PC2)


#if defined(Down_Shift_In__INTSTAT)  /* Interrupt Registers */

    #define Down_Shift_In_INTSTAT                (* (reg32 *) Down_Shift_In__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Down_Shift_In_DRIVE_MODE_SHIFT       (0x00u)
#define Down_Shift_In_DRIVE_MODE_MASK        (0x07u << Down_Shift_In_DRIVE_MODE_SHIFT)


#endif /* End Pins Down_Shift_In_H */


/* [] END OF FILE */
