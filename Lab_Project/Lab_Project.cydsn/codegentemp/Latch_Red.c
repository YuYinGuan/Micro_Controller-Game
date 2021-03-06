/*******************************************************************************
* File Name: Latch_Red.c  
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
#include "Latch_Red.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Latch_Red__PORT == 15 && ((Latch_Red__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Latch_Red_Write
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
void Latch_Red_Write(uint8 value) 
{
    uint8 staticBits = (Latch_Red_DR & (uint8)(~Latch_Red_MASK));
    Latch_Red_DR = staticBits | ((uint8)(value << Latch_Red_SHIFT) & Latch_Red_MASK);
}


/*******************************************************************************
* Function Name: Latch_Red_SetDriveMode
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
void Latch_Red_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Latch_Red_0, mode);
}


/*******************************************************************************
* Function Name: Latch_Red_Read
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
*  Macro Latch_Red_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Latch_Red_Read(void) 
{
    return (Latch_Red_PS & Latch_Red_MASK) >> Latch_Red_SHIFT;
}


/*******************************************************************************
* Function Name: Latch_Red_ReadDataReg
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
uint8 Latch_Red_ReadDataReg(void) 
{
    return (Latch_Red_DR & Latch_Red_MASK) >> Latch_Red_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Latch_Red_INTSTAT) 

    /*******************************************************************************
    * Function Name: Latch_Red_ClearInterrupt
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
    uint8 Latch_Red_ClearInterrupt(void) 
    {
        return (Latch_Red_INTSTAT & Latch_Red_MASK) >> Latch_Red_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
