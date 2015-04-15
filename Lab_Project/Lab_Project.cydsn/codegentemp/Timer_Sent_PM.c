/*******************************************************************************
* File Name: Timer_Sent_PM.c
* Version 2.40
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Sent.h"
static Timer_Sent_backupStruct Timer_Sent_backup;


/*******************************************************************************
* Function Name: Timer_Sent_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sent_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Sent_SaveConfig(void) 
{
    #if (!Timer_Sent_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            Timer_Sent_backup.TimerUdb = Timer_Sent_ReadCounter();
            Timer_Sent_backup.TimerPeriod = Timer_Sent_ReadPeriod();
            Timer_Sent_backup.InterruptMaskValue = Timer_Sent_STATUS_MASK;
            #if (Timer_Sent_UsingHWCaptureCounter)
                Timer_Sent_backup.TimerCaptureCounter = Timer_Sent_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Sent_backup.TimerUdb = Timer_Sent_ReadCounter();
            Timer_Sent_backup.InterruptMaskValue = Timer_Sent_STATUS_MASK;
            #if (Timer_Sent_UsingHWCaptureCounter)
                Timer_Sent_backup.TimerCaptureCounter = Timer_Sent_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Sent_ControlRegRemoved)
            Timer_Sent_backup.TimerControlRegister = Timer_Sent_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Sent_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sent_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Sent_RestoreConfig(void) 
{   
    #if (!Timer_Sent_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_Sent_interruptState;

            Timer_Sent_WriteCounter(Timer_Sent_backup.TimerUdb);
            Timer_Sent_WritePeriod(Timer_Sent_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_Sent_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Timer_Sent_STATUS_AUX_CTRL |= Timer_Sent_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_Sent_interruptState);
            Timer_Sent_STATUS_MASK =Timer_Sent_backup.InterruptMaskValue;
            #if (Timer_Sent_UsingHWCaptureCounter)
                Timer_Sent_SetCaptureCount(Timer_Sent_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Sent_WriteCounter(Timer_Sent_backup.TimerUdb);
            Timer_Sent_STATUS_MASK =Timer_Sent_backup.InterruptMaskValue;
            #if (Timer_Sent_UsingHWCaptureCounter)
                Timer_Sent_SetCaptureCount(Timer_Sent_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Sent_ControlRegRemoved)
            Timer_Sent_WriteControlRegister(Timer_Sent_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Sent_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sent_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Sent_Sleep(void) 
{
    #if(!Timer_Sent_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_Sent_CTRL_ENABLE == (Timer_Sent_CONTROL & Timer_Sent_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Sent_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Sent_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Sent_Stop();
    Timer_Sent_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Sent_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sent_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Sent_Wakeup(void) 
{
    Timer_Sent_RestoreConfig();
    #if(!Timer_Sent_ControlRegRemoved)
        if(Timer_Sent_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Sent_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
