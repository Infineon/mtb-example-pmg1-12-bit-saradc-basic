/******************************************************************************
* File Name: main.c
*
* Description: This is the source code for the PMG1 12-bit SAR ADC basic Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/


/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "cybsp.h"
#include "cy_pdl.h"
#include "stdio.h"


/*******************************************************************************
* Macros
*******************************************************************************/
#define CY_ASSERT_FAILED            (0u)
#define TERMINAL_DELAY              (500u)    /* milliseconds */
#define CHANNEL_0                   (0u) 


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  System entrance point. This function performs
*  - initial setup of device
*  - configure 12-bit SAR ADC
*  - configure the SCB block as UART interface
*  - checks the configured ADC mode
*  - convert ADC output codes into corresponding voltage
*  - prints the value of input voltage via UART interface
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Declaration of UART context */
    cy_stc_scb_uart_context_t UART_context; 

    /* Variables for processing SAR ADC output */
    int16_t Ch0;    /* Variable holding ADC output code */
    int8_t mode;    /* Variable holding ADC modes of operation */
    float ADC_voltage = 0;    /* ADC input voltage (mV) */
    int voltage_integer;    /* Integer part of ADC input voltage */
    int voltage_decimal;    /* Decimal part of ADC input voltage */
    char_t ADC_string[73];    /* String containing output to be displayed on the UART terminal */

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        /* insert error handling here */
        CY_ASSERT(CY_ASSERT_FAILED);
    }

    /* Global interrupt enable */
    __enable_irq(); 

    /* SAR ADC initialization */
    cy_en_sar_status_t sarStatus = Cy_SAR_Init(SAR0, &SARADC0_config);
    if (CY_SAR_SUCCESS != sarStatus)
    {
        /* insert error handling here */
        CY_ASSERT(CY_ASSERT_FAILED);
    }

    /* Enable SAR ADC */
    Cy_SAR_Enable(SAR0); 

    /* Configure and enable the UART peripheral */
    Cy_SCB_UART_Init(CYBSP_UART_HW, &CYBSP_UART_config, &UART_context);
    Cy_SCB_UART_Enable(CYBSP_UART_HW);

    /* To read the ADC operational modes set using Device Configurator */
    if(SARADC0_channel_0_config.differential)
    {
        if(SARADC0_config.differentialSigned)
        {
            /* Differential Signed */
            mode = 1;

            /* Send a string through UART peripheral to display the configured ADC modes */
            Cy_SCB_UART_PutString(CYBSP_UART_HW,"\n\nDisplaying 12-bit SAR ADC output: DIFFERENTIAL mode - Signed \r\n\n");
        }
        
        else
        {
            /* Differential Unsigned */
            mode = 2;

            /* Send a string through UART peripheral to display the configured ADC modes */
            Cy_SCB_UART_PutString(CYBSP_UART_HW,"\n\nDisplaying 12-bit SAR ADC output: DIFFERENTIAL mode - Unsigned \r\n\n");
        }
    }

    else
    {
        if(SARADC0_config.singleEndedSigned)
        {
            /* Single-ended Signed */
            mode = 3;

            /* Send a string through UART peripheral to display the configured ADC modes */
            Cy_SCB_UART_PutString(CYBSP_UART_HW,"\n\nDisplaying 12-bit SAR ADC output: SINGLE-ENDED mode - Signed \r\n\n");
        }
        
        else
        {
            /* Single-ended Unsigned */
            mode = 4;

            /* Send a string through UART peripheral to display the configured ADC modes */
            Cy_SCB_UART_PutString(CYBSP_UART_HW,"\n\nDisplaying 12-bit SAR ADC output: SINGLE-ENDED mode - Unsigned \r\n\n");
        }
    }

    /* Send a string through UART peripheral */
    Cy_SCB_UART_PutString(CYBSP_UART_HW, "--------------------------------------------------------------\r\n");

    for(;;)
    {
        /* Start SAR conversion of analog sample values */
        Cy_SAR_StartConvert(SAR0, CY_SAR_START_CONVERT_SINGLE_SHOT  );

        /* Delay of 2.304 milliseconds is required to finish conversion of an analog sample as detailed in README file.
         * However, here a delay of 500 milliseconds is added for better visibility of ADC codes on UART terminal.
         * This delay may be replaced by codes that can perform some useful task in 2.304 milliseconds time interval. */

        /* 'CY_SAR_RETURN_STATUS' immediately returns the conversion status.
         * This is a non-blocking read mode
         * Hence, here a while-loop is used to check the conversion status before reading the ADC code */
        while(CY_SAR_SUCCESS != Cy_SAR_IsEndConversion(SAR0, CY_SAR_RETURN_STATUS))
        {
            /* This loop executes until ADC sample coversion completes */
        }
        Ch0 = Cy_SAR_GetResult16(SAR0, CHANNEL_0);
        /* now 'Ch0' contains the ADC channel 0 result */

        switch(mode)
        {
            case 1:
                /* Differential Signed */
                ADC_voltage = 2.4 * Ch0/4095 * 1000; /* ADC code to voltage conversion formula */
                break;

            case 2:
                /* Differential Unsigned */
                ADC_voltage = 2.4 * (Ch0 - 2048)/4095 * 1000; /* ADC code to voltage conversion formula */
                break;

            case 3:
                /* Single-ended Signed */
                ADC_voltage = 2.4 * (Ch0 + 2048)/4095 * 1000; /* ADC code to voltage conversion formula */
                break;

            case 4:
                /* Single-ended Unsigned */
                ADC_voltage = 2.4 * Ch0/4095 * 1000; /* ADC code to voltage conversion formula */
                break;
        }

        voltage_integer = (int)ADC_voltage;
        voltage_decimal = (int)(10000 * (ADC_voltage - voltage_integer));
        if(voltage_decimal<0)
        {
            voltage_decimal = - voltage_decimal; /* Negative to positive conversion */
        }

        /* conversion from uint32_t to char_t for UART transmit */
        sprintf(ADC_string,"Raw ADC data = %d ; Voltage measured = %d.%04d mV\r\n\n",Ch0, voltage_integer, voltage_decimal);

        /* Send a string through UART peripheral */
        Cy_SCB_UART_PutString(CYBSP_UART_HW, ADC_string);

        /* Delay required to slow down terminal display rate */
        Cy_SysLib_Delay(TERMINAL_DELAY);
    }
}
/* [] END OF FILE */
