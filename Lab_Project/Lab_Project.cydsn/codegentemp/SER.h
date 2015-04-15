/*******************************************************************************
* File Name: SER.h  
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

#if !defined(CY_PINS_SER_H) /* Pins SER_H */
#define CY_PINS_SER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SER_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SER__PORT == 15 && ((SER__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SER_Write(uint8 value) ;
void    SER_SetDriveMode(uint8 mode) ;
uint8   SER_ReadDataReg(void) ;
uint8   SER_Read(void) ;
uint8   SER_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SER_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SER_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SER_DM_RES_UP          PIN_DM_RES_UP
#define SER_DM_RES_DWN         PIN_DM_RES_DWN
#define SER_DM_OD_LO           PIN_DM_OD_LO
#define SER_DM_OD_HI           PIN_DM_OD_HI
#define SER_DM_STRONG          PIN_DM_STRONG
#define SER_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SER_MASK               SER__MASK
#define SER_SHIFT              SER__SHIFT
#define SER_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SER_PS                     (* (reg8 *) SER__PS)
/* Data Register */
#define SER_DR                     (* (reg8 *) SER__DR)
/* Port Number */
#define SER_PRT_NUM                (* (reg8 *) SER__PRT) 
/* Connect to Analog Globals */                                                  
#define SER_AG                     (* (reg8 *) SER__AG)                       
/* Analog MUX bux enable */
#define SER_AMUX                   (* (reg8 *) SER__AMUX) 
/* Bidirectional Enable */                                                        
#define SER_BIE                    (* (reg8 *) SER__BIE)
/* Bit-mask for Aliased Register Access */
#define SER_BIT_MASK               (* (reg8 *) SER__BIT_MASK)
/* Bypass Enable */
#define SER_BYP                    (* (reg8 *) SER__BYP)
/* Port wide control signals */                                                   
#define SER_CTL                    (* (reg8 *) SER__CTL)
/* Drive Modes */
#define SER_DM0                    (* (reg8 *) SER__DM0) 
#define SER_DM1                    (* (reg8 *) SER__DM1)
#define SER_DM2                    (* (reg8 *) SER__DM2) 
/* Input Buffer Disable Override */
#define SER_INP_DIS                (* (reg8 *) SER__INP_DIS)
/* LCD Common or Segment Drive */
#define SER_LCD_COM_SEG            (* (reg8 *) SER__LCD_COM_SEG)
/* Enable Segment LCD */
#define SER_LCD_EN                 (* (reg8 *) SER__LCD_EN)
/* Slew Rate Control */
#define SER_SLW                    (* (reg8 *) SER__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SER_PRTDSI__CAPS_SEL       (* (reg8 *) SER__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SER_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SER__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SER_PRTDSI__OE_SEL0        (* (reg8 *) SER__PRTDSI__OE_SEL0) 
#define SER_PRTDSI__OE_SEL1        (* (reg8 *) SER__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SER_PRTDSI__OUT_SEL0       (* (reg8 *) SER__PRTDSI__OUT_SEL0) 
#define SER_PRTDSI__OUT_SEL1       (* (reg8 *) SER__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SER_PRTDSI__SYNC_OUT       (* (reg8 *) SER__PRTDSI__SYNC_OUT) 


#if defined(SER__INTSTAT)  /* Interrupt Registers */

    #define SER_INTSTAT                (* (reg8 *) SER__INTSTAT)
    #define SER_SNAP                   (* (reg8 *) SER__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SER_H */


/* [] END OF FILE */
