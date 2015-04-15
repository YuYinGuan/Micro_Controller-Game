/*******************************************************************************
* File Name: SRCLR.h  
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

#if !defined(CY_PINS_SRCLR_H) /* Pins SRCLR_H */
#define CY_PINS_SRCLR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SRCLR_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SRCLR__PORT == 15 && ((SRCLR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SRCLR_Write(uint8 value) ;
void    SRCLR_SetDriveMode(uint8 mode) ;
uint8   SRCLR_ReadDataReg(void) ;
uint8   SRCLR_Read(void) ;
uint8   SRCLR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SRCLR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SRCLR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SRCLR_DM_RES_UP          PIN_DM_RES_UP
#define SRCLR_DM_RES_DWN         PIN_DM_RES_DWN
#define SRCLR_DM_OD_LO           PIN_DM_OD_LO
#define SRCLR_DM_OD_HI           PIN_DM_OD_HI
#define SRCLR_DM_STRONG          PIN_DM_STRONG
#define SRCLR_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SRCLR_MASK               SRCLR__MASK
#define SRCLR_SHIFT              SRCLR__SHIFT
#define SRCLR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SRCLR_PS                     (* (reg8 *) SRCLR__PS)
/* Data Register */
#define SRCLR_DR                     (* (reg8 *) SRCLR__DR)
/* Port Number */
#define SRCLR_PRT_NUM                (* (reg8 *) SRCLR__PRT) 
/* Connect to Analog Globals */                                                  
#define SRCLR_AG                     (* (reg8 *) SRCLR__AG)                       
/* Analog MUX bux enable */
#define SRCLR_AMUX                   (* (reg8 *) SRCLR__AMUX) 
/* Bidirectional Enable */                                                        
#define SRCLR_BIE                    (* (reg8 *) SRCLR__BIE)
/* Bit-mask for Aliased Register Access */
#define SRCLR_BIT_MASK               (* (reg8 *) SRCLR__BIT_MASK)
/* Bypass Enable */
#define SRCLR_BYP                    (* (reg8 *) SRCLR__BYP)
/* Port wide control signals */                                                   
#define SRCLR_CTL                    (* (reg8 *) SRCLR__CTL)
/* Drive Modes */
#define SRCLR_DM0                    (* (reg8 *) SRCLR__DM0) 
#define SRCLR_DM1                    (* (reg8 *) SRCLR__DM1)
#define SRCLR_DM2                    (* (reg8 *) SRCLR__DM2) 
/* Input Buffer Disable Override */
#define SRCLR_INP_DIS                (* (reg8 *) SRCLR__INP_DIS)
/* LCD Common or Segment Drive */
#define SRCLR_LCD_COM_SEG            (* (reg8 *) SRCLR__LCD_COM_SEG)
/* Enable Segment LCD */
#define SRCLR_LCD_EN                 (* (reg8 *) SRCLR__LCD_EN)
/* Slew Rate Control */
#define SRCLR_SLW                    (* (reg8 *) SRCLR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SRCLR_PRTDSI__CAPS_SEL       (* (reg8 *) SRCLR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SRCLR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SRCLR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SRCLR_PRTDSI__OE_SEL0        (* (reg8 *) SRCLR__PRTDSI__OE_SEL0) 
#define SRCLR_PRTDSI__OE_SEL1        (* (reg8 *) SRCLR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SRCLR_PRTDSI__OUT_SEL0       (* (reg8 *) SRCLR__PRTDSI__OUT_SEL0) 
#define SRCLR_PRTDSI__OUT_SEL1       (* (reg8 *) SRCLR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SRCLR_PRTDSI__SYNC_OUT       (* (reg8 *) SRCLR__PRTDSI__SYNC_OUT) 


#if defined(SRCLR__INTSTAT)  /* Interrupt Registers */

    #define SRCLR_INTSTAT                (* (reg8 *) SRCLR__INTSTAT)
    #define SRCLR_SNAP                   (* (reg8 *) SRCLR__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SRCLR_H */


/* [] END OF FILE */
