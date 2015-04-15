/*******************************************************************************
* File Name: SER_Red.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SER_Red_H) /* Pins SER_Red_H */
#define CY_PINS_SER_Red_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SER_Red_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SER_Red__PORT == 15 && ((SER_Red__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SER_Red_Write(uint8 value) ;
void    SER_Red_SetDriveMode(uint8 mode) ;
uint8   SER_Red_ReadDataReg(void) ;
uint8   SER_Red_Read(void) ;
uint8   SER_Red_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SER_Red_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SER_Red_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SER_Red_DM_RES_UP          PIN_DM_RES_UP
#define SER_Red_DM_RES_DWN         PIN_DM_RES_DWN
#define SER_Red_DM_OD_LO           PIN_DM_OD_LO
#define SER_Red_DM_OD_HI           PIN_DM_OD_HI
#define SER_Red_DM_STRONG          PIN_DM_STRONG
#define SER_Red_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SER_Red_MASK               SER_Red__MASK
#define SER_Red_SHIFT              SER_Red__SHIFT
#define SER_Red_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SER_Red_PS                     (* (reg8 *) SER_Red__PS)
/* Data Register */
#define SER_Red_DR                     (* (reg8 *) SER_Red__DR)
/* Port Number */
#define SER_Red_PRT_NUM                (* (reg8 *) SER_Red__PRT) 
/* Connect to Analog Globals */                                                  
#define SER_Red_AG                     (* (reg8 *) SER_Red__AG)                       
/* Analog MUX bux enable */
#define SER_Red_AMUX                   (* (reg8 *) SER_Red__AMUX) 
/* Bidirectional Enable */                                                        
#define SER_Red_BIE                    (* (reg8 *) SER_Red__BIE)
/* Bit-mask for Aliased Register Access */
#define SER_Red_BIT_MASK               (* (reg8 *) SER_Red__BIT_MASK)
/* Bypass Enable */
#define SER_Red_BYP                    (* (reg8 *) SER_Red__BYP)
/* Port wide control signals */                                                   
#define SER_Red_CTL                    (* (reg8 *) SER_Red__CTL)
/* Drive Modes */
#define SER_Red_DM0                    (* (reg8 *) SER_Red__DM0) 
#define SER_Red_DM1                    (* (reg8 *) SER_Red__DM1)
#define SER_Red_DM2                    (* (reg8 *) SER_Red__DM2) 
/* Input Buffer Disable Override */
#define SER_Red_INP_DIS                (* (reg8 *) SER_Red__INP_DIS)
/* LCD Common or Segment Drive */
#define SER_Red_LCD_COM_SEG            (* (reg8 *) SER_Red__LCD_COM_SEG)
/* Enable Segment LCD */
#define SER_Red_LCD_EN                 (* (reg8 *) SER_Red__LCD_EN)
/* Slew Rate Control */
#define SER_Red_SLW                    (* (reg8 *) SER_Red__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SER_Red_PRTDSI__CAPS_SEL       (* (reg8 *) SER_Red__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SER_Red_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SER_Red__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SER_Red_PRTDSI__OE_SEL0        (* (reg8 *) SER_Red__PRTDSI__OE_SEL0) 
#define SER_Red_PRTDSI__OE_SEL1        (* (reg8 *) SER_Red__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SER_Red_PRTDSI__OUT_SEL0       (* (reg8 *) SER_Red__PRTDSI__OUT_SEL0) 
#define SER_Red_PRTDSI__OUT_SEL1       (* (reg8 *) SER_Red__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SER_Red_PRTDSI__SYNC_OUT       (* (reg8 *) SER_Red__PRTDSI__SYNC_OUT) 


#if defined(SER_Red__INTSTAT)  /* Interrupt Registers */

    #define SER_Red_INTSTAT                (* (reg8 *) SER_Red__INTSTAT)
    #define SER_Red_SNAP                   (* (reg8 *) SER_Red__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SER_Red_H */


/* [] END OF FILE */
