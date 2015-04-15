/*******************************************************************************
* File Name: SRCLK_Blue.h  
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

#if !defined(CY_PINS_SRCLK_Blue_H) /* Pins SRCLK_Blue_H */
#define CY_PINS_SRCLK_Blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SRCLK_Blue_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SRCLK_Blue__PORT == 15 && ((SRCLK_Blue__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SRCLK_Blue_Write(uint8 value) ;
void    SRCLK_Blue_SetDriveMode(uint8 mode) ;
uint8   SRCLK_Blue_ReadDataReg(void) ;
uint8   SRCLK_Blue_Read(void) ;
uint8   SRCLK_Blue_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SRCLK_Blue_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SRCLK_Blue_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SRCLK_Blue_DM_RES_UP          PIN_DM_RES_UP
#define SRCLK_Blue_DM_RES_DWN         PIN_DM_RES_DWN
#define SRCLK_Blue_DM_OD_LO           PIN_DM_OD_LO
#define SRCLK_Blue_DM_OD_HI           PIN_DM_OD_HI
#define SRCLK_Blue_DM_STRONG          PIN_DM_STRONG
#define SRCLK_Blue_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SRCLK_Blue_MASK               SRCLK_Blue__MASK
#define SRCLK_Blue_SHIFT              SRCLK_Blue__SHIFT
#define SRCLK_Blue_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SRCLK_Blue_PS                     (* (reg8 *) SRCLK_Blue__PS)
/* Data Register */
#define SRCLK_Blue_DR                     (* (reg8 *) SRCLK_Blue__DR)
/* Port Number */
#define SRCLK_Blue_PRT_NUM                (* (reg8 *) SRCLK_Blue__PRT) 
/* Connect to Analog Globals */                                                  
#define SRCLK_Blue_AG                     (* (reg8 *) SRCLK_Blue__AG)                       
/* Analog MUX bux enable */
#define SRCLK_Blue_AMUX                   (* (reg8 *) SRCLK_Blue__AMUX) 
/* Bidirectional Enable */                                                        
#define SRCLK_Blue_BIE                    (* (reg8 *) SRCLK_Blue__BIE)
/* Bit-mask for Aliased Register Access */
#define SRCLK_Blue_BIT_MASK               (* (reg8 *) SRCLK_Blue__BIT_MASK)
/* Bypass Enable */
#define SRCLK_Blue_BYP                    (* (reg8 *) SRCLK_Blue__BYP)
/* Port wide control signals */                                                   
#define SRCLK_Blue_CTL                    (* (reg8 *) SRCLK_Blue__CTL)
/* Drive Modes */
#define SRCLK_Blue_DM0                    (* (reg8 *) SRCLK_Blue__DM0) 
#define SRCLK_Blue_DM1                    (* (reg8 *) SRCLK_Blue__DM1)
#define SRCLK_Blue_DM2                    (* (reg8 *) SRCLK_Blue__DM2) 
/* Input Buffer Disable Override */
#define SRCLK_Blue_INP_DIS                (* (reg8 *) SRCLK_Blue__INP_DIS)
/* LCD Common or Segment Drive */
#define SRCLK_Blue_LCD_COM_SEG            (* (reg8 *) SRCLK_Blue__LCD_COM_SEG)
/* Enable Segment LCD */
#define SRCLK_Blue_LCD_EN                 (* (reg8 *) SRCLK_Blue__LCD_EN)
/* Slew Rate Control */
#define SRCLK_Blue_SLW                    (* (reg8 *) SRCLK_Blue__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SRCLK_Blue_PRTDSI__CAPS_SEL       (* (reg8 *) SRCLK_Blue__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SRCLK_Blue_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SRCLK_Blue__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SRCLK_Blue_PRTDSI__OE_SEL0        (* (reg8 *) SRCLK_Blue__PRTDSI__OE_SEL0) 
#define SRCLK_Blue_PRTDSI__OE_SEL1        (* (reg8 *) SRCLK_Blue__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SRCLK_Blue_PRTDSI__OUT_SEL0       (* (reg8 *) SRCLK_Blue__PRTDSI__OUT_SEL0) 
#define SRCLK_Blue_PRTDSI__OUT_SEL1       (* (reg8 *) SRCLK_Blue__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SRCLK_Blue_PRTDSI__SYNC_OUT       (* (reg8 *) SRCLK_Blue__PRTDSI__SYNC_OUT) 


#if defined(SRCLK_Blue__INTSTAT)  /* Interrupt Registers */

    #define SRCLK_Blue_INTSTAT                (* (reg8 *) SRCLK_Blue__INTSTAT)
    #define SRCLK_Blue_SNAP                   (* (reg8 *) SRCLK_Blue__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SRCLK_Blue_H */


/* [] END OF FILE */
