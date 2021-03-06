/*******************************************************************************
* File Name: SRCLK_Blue.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "SRCLK_Blue.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SRCLK_Blue__PORT == 15 && ((SRCLK_Blue__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SRCLK_Blue_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void SRCLK_Blue_Write(uint8 value) 
{
    uint8 staticBits = (SRCLK_Blue_DR & (uint8)(~SRCLK_Blue_MASK));
    SRCLK_Blue_DR = staticBits | ((uint8)(value << SRCLK_Blue_SHIFT) & SRCLK_Blue_MASK);
}


/*******************************************************************************
* Function Name: SRCLK_Blue_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void SRCLK_Blue_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SRCLK_Blue_0, mode);
}


/*******************************************************************************
* Function Name: SRCLK_Blue_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro SRCLK_Blue_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SRCLK_Blue_Read(void) 
{
    return (SRCLK_Blue_PS & SRCLK_Blue_MASK) >> SRCLK_Blue_SHIFT;
}


/*******************************************************************************
* Function Name: SRCLK_Blue_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 SRCLK_Blue_ReadDataReg(void) 
{
    return (SRCLK_Blue_DR & SRCLK_Blue_MASK) >> SRCLK_Blue_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SRCLK_Blue_INTSTAT) 

    /*******************************************************************************
    * Function Name: SRCLK_Blue_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 SRCLK_Blue_ClearInterrupt(void) 
    {
        return (SRCLK_Blue_INTSTAT & SRCLK_Blue_MASK) >> SRCLK_Blue_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
