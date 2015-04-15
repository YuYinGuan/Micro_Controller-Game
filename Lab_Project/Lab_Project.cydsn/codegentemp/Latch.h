/*******************************************************************************
* File Name: Latch.h  
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

#if !defined(CY_PINS_Latch_H) /* Pins Latch_H */
#define CY_PINS_Latch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Latch_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Latch__PORT == 15 && ((Latch__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Latch_Write(uint8 value) ;
void    Latch_SetDriveMode(uint8 mode) ;
uint8   Latch_ReadDataReg(void) ;
uint8   Latch_Read(void) ;
uint8   Latch_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Latch_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Latch_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Latch_DM_RES_UP          PIN_DM_RES_UP
#define Latch_DM_RES_DWN         PIN_DM_RES_DWN
#define Latch_DM_OD_LO           PIN_DM_OD_LO
#define Latch_DM_OD_HI           PIN_DM_OD_HI
#define Latch_DM_STRONG          PIN_DM_STRONG
#define Latch_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Latch_MASK               Latch__MASK
#define Latch_SHIFT              Latch__SHIFT
#define Latch_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Latch_PS                     (* (reg8 *) Latch__PS)
/* Data Register */
#define Latch_DR                     (* (reg8 *) Latch__DR)
/* Port Number */
#define Latch_PRT_NUM                (* (reg8 *) Latch__PRT) 
/* Connect to Analog Globals */                                                  
#define Latch_AG                     (* (reg8 *) Latch__AG)                       
/* Analog MUX bux enable */
#define Latch_AMUX                   (* (reg8 *) Latch__AMUX) 
/* Bidirectional Enable */                                                        
#define Latch_BIE                    (* (reg8 *) Latch__BIE)
/* Bit-mask for Aliased Register Access */
#define Latch_BIT_MASK               (* (reg8 *) Latch__BIT_MASK)
/* Bypass Enable */
#define Latch_BYP                    (* (reg8 *) Latch__BYP)
/* Port wide control signals */                                                   
#define Latch_CTL                    (* (reg8 *) Latch__CTL)
/* Drive Modes */
#define Latch_DM0                    (* (reg8 *) Latch__DM0) 
#define Latch_DM1                    (* (reg8 *) Latch__DM1)
#define Latch_DM2                    (* (reg8 *) Latch__DM2) 
/* Input Buffer Disable Override */
#define Latch_INP_DIS                (* (reg8 *) Latch__INP_DIS)
/* LCD Common or Segment Drive */
#define Latch_LCD_COM_SEG            (* (reg8 *) Latch__LCD_COM_SEG)
/* Enable Segment LCD */
#define Latch_LCD_EN                 (* (reg8 *) Latch__LCD_EN)
/* Slew Rate Control */
#define Latch_SLW                    (* (reg8 *) Latch__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Latch_PRTDSI__CAPS_SEL       (* (reg8 *) Latch__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Latch_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Latch__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Latch_PRTDSI__OE_SEL0        (* (reg8 *) Latch__PRTDSI__OE_SEL0) 
#define Latch_PRTDSI__OE_SEL1        (* (reg8 *) Latch__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Latch_PRTDSI__OUT_SEL0       (* (reg8 *) Latch__PRTDSI__OUT_SEL0) 
#define Latch_PRTDSI__OUT_SEL1       (* (reg8 *) Latch__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Latch_PRTDSI__SYNC_OUT       (* (reg8 *) Latch__PRTDSI__SYNC_OUT) 


#if defined(Latch__INTSTAT)  /* Interrupt Registers */

    #define Latch_INTSTAT                (* (reg8 *) Latch__INTSTAT)
    #define Latch_SNAP                   (* (reg8 *) Latch__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Latch_H */


/* [] END OF FILE */
