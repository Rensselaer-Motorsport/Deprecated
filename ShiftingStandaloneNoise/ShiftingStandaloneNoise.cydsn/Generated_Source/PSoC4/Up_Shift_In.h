/*******************************************************************************
* File Name: Up_Shift_In.h  
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

#if !defined(CY_PINS_Up_Shift_In_H) /* Pins Up_Shift_In_H */
#define CY_PINS_Up_Shift_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Up_Shift_In_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Up_Shift_In_Write(uint8 value) ;
void    Up_Shift_In_SetDriveMode(uint8 mode) ;
uint8   Up_Shift_In_ReadDataReg(void) ;
uint8   Up_Shift_In_Read(void) ;
uint8   Up_Shift_In_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Up_Shift_In_DRIVE_MODE_BITS        (3)
#define Up_Shift_In_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Up_Shift_In_DRIVE_MODE_BITS))

#define Up_Shift_In_DM_ALG_HIZ         (0x00u)
#define Up_Shift_In_DM_DIG_HIZ         (0x01u)
#define Up_Shift_In_DM_RES_UP          (0x02u)
#define Up_Shift_In_DM_RES_DWN         (0x03u)
#define Up_Shift_In_DM_OD_LO           (0x04u)
#define Up_Shift_In_DM_OD_HI           (0x05u)
#define Up_Shift_In_DM_STRONG          (0x06u)
#define Up_Shift_In_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Up_Shift_In_MASK               Up_Shift_In__MASK
#define Up_Shift_In_SHIFT              Up_Shift_In__SHIFT
#define Up_Shift_In_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Up_Shift_In_PS                     (* (reg32 *) Up_Shift_In__PS)
/* Port Configuration */
#define Up_Shift_In_PC                     (* (reg32 *) Up_Shift_In__PC)
/* Data Register */
#define Up_Shift_In_DR                     (* (reg32 *) Up_Shift_In__DR)
/* Input Buffer Disable Override */
#define Up_Shift_In_INP_DIS                (* (reg32 *) Up_Shift_In__PC2)


#if defined(Up_Shift_In__INTSTAT)  /* Interrupt Registers */

    #define Up_Shift_In_INTSTAT                (* (reg32 *) Up_Shift_In__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Up_Shift_In_DRIVE_MODE_SHIFT       (0x00u)
#define Up_Shift_In_DRIVE_MODE_MASK        (0x07u << Up_Shift_In_DRIVE_MODE_SHIFT)


#endif /* End Pins Up_Shift_In_H */


/* [] END OF FILE */
