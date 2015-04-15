/*******************************************************************************
* File Name: CapSense_CSD_INT.c
* Version 3.30
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_CSD.h"

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START CapSense_CSD_IsrCH_ISR_intc` */

/* `#END` */

/* Extern functions declarations, Start and Compete the scan */
extern void CapSense_CSD_PreScan(uint8 sensor) CYREENTRANT;
#if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
    extern void CapSense_CSD_PostScan(uint8 sensor) CYREENTRANT;
#else
    extern void CapSense_CSD_PostScanCh0(uint8 sensor) CYREENTRANT;
    extern void CapSense_CSD_PostScanCh1(uint8 sensor) CYREENTRANT;
#endif  /* CapSense_CSD_DESIGN_TYPE */

 #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
    extern uint8 CapSense_CSD_FindNextSensor(uint8 snsIndex) CYREENTRANT;
#endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN) */
 
#if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
    extern uint8 CapSense_CSD_FindNextPair(uint8 snsIndex) CYREENTRANT;
#endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) */

/* Global variables and arrays */
extern volatile uint8 CapSense_CSD_csv;
extern volatile uint8 CapSense_CSD_sensorIndex;


#if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
    /*******************************************************************************
    * Function Name: CapSense_CSD_IsrCH0_ISR
    ********************************************************************************
    *
    * Summary:
    *  This ISR is executed when measure window is closed. The measure window 
    *  depends on scan resolution parameter of sensor. 
    *  The ISR has two modes: 
    *   1. Scans single sensor and stores measure result.
    *   2. Stores result of current measure and starts next scan till all 
    *      enabled sensors will be scanned.
    *  This interrupt handler only used in one channel designs.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_csv - used to provide status and mode of scanning process.
    *   Mode - single scan or scan of all enabled sensors.
    *   Status - scan in progress or ready for new scan.
    *  CapSense_CSD_sensorIndex - used to store sensor scanning sensor number.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    CY_ISR(CapSense_CSD_IsrCH0_ISR)
    {
        /*  Place your Interrupt code here. */
        /* `#START CapSense_CSD_ONE_CHANNEL_IsrCH0_ISR` */

        /* `#END` */
    
        /* Save results and disable sensor */
        CapSense_CSD_PostScan(CapSense_CSD_sensorIndex);
                
        if ((CapSense_CSD_csv & CapSense_CSD_SW_CTRL_SINGLE_SCAN) != 0u)
        {
            CapSense_CSD_csv &= ~CapSense_CSD_SW_STS_BUSY;
        }
        else
        {
            /* Proceed the scanning */
            CapSense_CSD_sensorIndex = CapSense_CSD_FindNextSensor(CapSense_CSD_sensorIndex);
            
            /* Check end of scan */
            if(CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT)
            {
                CapSense_CSD_PreScan(CapSense_CSD_sensorIndex);
            }
            else
            {
                CapSense_CSD_csv &= ~CapSense_CSD_SW_STS_BUSY;
            } 
        }
    }
 #endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN) */


 #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)   
    /*******************************************************************************
    * Function Name: CapSense_CSD_IsrCH0_ISR
    ********************************************************************************
    *
    * Summary:
    *  This ISR is executed when measure window is closed. The measure window 
    *  depends on scan resolution parameter of sensor. 
    *  The ISR has two modes: 
    *   1. Scans single sensor or pair of sensors and stores measure result.
    *   2. Stores results of current measure when complete scan of sensors pair or 
    *      sensor scan and starts next enabled sensors pair or sensor scan. 
    *  This interrupt handler only used in two channel designs.
    *  The synchronization is added to scanning process. The ISR channel 0 or 
    *  channel 1 stores the result and starts next scan. It depends which channel
    *  scans longer. The biggest scan resolution parameter of sensor within pair 
    *  defines scanning time of pair.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_csv - used to provide status and mode of scanning process.
    *   Mode - single scan or scan of all enabled sensors.
    *   Status - scan in progress or ready for new scan.
    *  CapSense_CSD_sensorIndex - used to store sensor scanning sensor number.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    CY_ISR(CapSense_CSD_IsrCH0_ISR)
    {
        /*  Place your Interrupt code here. */
        /* `#START CapSense_CSD_TWO_CHANNELS_IsrCH0_ISR` */

        /* `#END` */
        
        CapSense_CSD_CONTROL_REG &= ~CapSense_CSD_CTRL_WINDOW_EN__CH0;
        CapSense_CSD_PostScanCh0(CapSense_CSD_sensorIndex);
        
        if((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH1) == 0u)
        {
            if ((CapSense_CSD_csv & CapSense_CSD_SW_CTRL_SINGLE_SCAN) != 0u)
            {
                CapSense_CSD_csv &= ~CapSense_CSD_SW_STS_BUSY;
            }
            else
            {
                /* Procced the scanning */
                CapSense_CSD_sensorIndex = CapSense_CSD_FindNextPair(CapSense_CSD_sensorIndex);
                
                /* Check end of scan conditions */
                if((CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT__CH0) || 
                   (CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT__CH1))
                {
                    CapSense_CSD_PreScan(CapSense_CSD_sensorIndex);
                }
                else
                {
                    CapSense_CSD_csv &= ~CapSense_CSD_SW_STS_BUSY;
                }
            }
        }
        else
        {
            /* Do nothing */
        }
    }

    
    /*******************************************************************************
    * Function Name: CapSense_CSD_IsrCH1_ISR
    ********************************************************************************
    *
    * Summary:
    *  This ISR is executed when measure window is closed. The measure window 
    *  depends on scan resolution parameter of sensor. 
    *  The ISR has two modes: 
    *   1. Scans single sensor or pair of sensors and stores measure result.
    *   2. Stores results of current measure when complete scan of sensors pair or 
    *      sensor scan and starts next enabled sensors pair or sensor scan. 
    *  This interrupt handler only used in two channel designs.
    *  The synchronization is added to scanning process. The ISR channel 0 or 
    *  channel 1 stores the result and starts next scan. It depends which channel
    *  scans longer. The biggest scan resolution parameter of sensor within pair 
    *  defines scanning time of pair.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_csv - used to provide status and mode of scanning process.
    *   Mode - single scan or scan of all enabled sensors.
    *   Status - scan in progress or ready for new scan.
    *  CapSense_CSD_sensorIndex - used to store sensor scanning sensor number.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    CY_ISR(CapSense_CSD_IsrCH1_ISR)
    {
        /*  Place your Interrupt code here */
        /* `#START CapSense_CSD_TWO_CHANNELS_IsrCH1_ISR` */

        /* `#END` */
        
        CapSense_CSD_CONTROL_REG &= ~CapSense_CSD_CTRL_WINDOW_EN__CH1;
        CapSense_CSD_PostScanCh1(CapSense_CSD_sensorIndex + CapSense_CSD_TOTAL_SENSOR_COUNT__CH0);
        
        if((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH0) == 0u)
        {
            if ((CapSense_CSD_csv & CapSense_CSD_SW_CTRL_SINGLE_SCAN) != 0u)
            {
                CapSense_CSD_csv &= ~CapSense_CSD_SW_STS_BUSY;
            }
            else 
            {
                /* Procced the scanning */
                CapSense_CSD_sensorIndex = CapSense_CSD_FindNextPair(CapSense_CSD_sensorIndex);
                
                /* Check end of scan conditions */
                if((CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT__CH0) || 
                   (CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT__CH1))
                {
                    CapSense_CSD_PreScan(CapSense_CSD_sensorIndex);
                }
                else
                {
                    CapSense_CSD_csv &= ~CapSense_CSD_SW_STS_BUSY;
                }
            }
        }
        else
        {
            /* Do nothing */
        }
    }
#endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) */


/* [] END OF FILE */
