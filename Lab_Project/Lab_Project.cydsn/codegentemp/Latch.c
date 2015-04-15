/*******************************************************************************
* File Name: Latch.c  
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
#include "Latch.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Latch__PORT == 15 && ((Latch__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Latch_Write
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
void Latch_Write(uint8 value) 
{
    uint8 staticBits = (Latch_DR & (uint8)(~Latch_MASK));
    Latch_DR = staticBits | ((uint8)(value << Latch_SHIFT) & Latch_MASK);
}


/*******************************************************************************
* Function Name: Latch_SetDriveMode
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
void Latch_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Latch_0, mode);
}


/*******************************************************************************
* Function Name: Latch_Read
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
*  Macro Latch_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Latch_Read(void) 
{
    return (Latch_PS & Latch_MASK) >> Latch_SHIFT;
}


/*******************************************************************************
* Function Name: Latch_ReadDataReg
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
uint8 Latch_ReadDataReg(void) 
{
    return (Latch_DR & Latch_MASK) >> Latch_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Latch_INTSTAT) 

    /*******************************************************************************
    * Function Name: Latch_ClearInterrupt
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
    uint8 Latch_ClearInterrupt(void) 
    {
        return (Latch_INTSTAT & Latch_MASK) >> Latch_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
