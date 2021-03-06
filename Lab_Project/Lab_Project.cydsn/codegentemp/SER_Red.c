/*******************************************************************************
* File Name: SER_Red.c  
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
#include "SER_Red.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SER_Red__PORT == 15 && ((SER_Red__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SER_Red_Write
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
void SER_Red_Write(uint8 value) 
{
    uint8 staticBits = (SER_Red_DR & (uint8)(~SER_Red_MASK));
    SER_Red_DR = staticBits | ((uint8)(value << SER_Red_SHIFT) & SER_Red_MASK);
}


/*******************************************************************************
* Function Name: SER_Red_SetDriveMode
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
void SER_Red_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SER_Red_0, mode);
}


/*******************************************************************************
* Function Name: SER_Red_Read
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
*  Macro SER_Red_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SER_Red_Read(void) 
{
    return (SER_Red_PS & SER_Red_MASK) >> SER_Red_SHIFT;
}


/*******************************************************************************
* Function Name: SER_Red_ReadDataReg
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
uint8 SER_Red_ReadDataReg(void) 
{
    return (SER_Red_DR & SER_Red_MASK) >> SER_Red_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SER_Red_INTSTAT) 

    /*******************************************************************************
    * Function Name: SER_Red_ClearInterrupt
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
    uint8 SER_Red_ClearInterrupt(void) 
    {
        return (SER_Red_INTSTAT & SER_Red_MASK) >> SER_Red_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
