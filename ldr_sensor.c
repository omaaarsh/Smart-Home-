/******************************************************************************
 *
 * Module: LDR
 *
 * File Name: ldr.c
 *
 * Description: Source file for the LDR sensor driver
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/

#include "ldr_sensor.h"  /* LDR Sensor driver header file */

#include "adc.h"  /* To use the ADC functions */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint16 LDR_getLightIntensity(void)
{
    /* Read the ADC value from the LDR sensor on channel 0 */
    uint16 adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);

    /* Convert the ADC value to voltage */
    float voltage = (adc_value * LDR_SENSOR_MAX_VOLT_VALUE) / 1023;

    /* Calculate the light intensity as a percentage (0% to 100%) */
    uint16 light_intensity = (voltage * LDR_SENSOR_MAX_LIGHT_INTENSITY) / LDR_SENSOR_MAX_VOLT_VALUE;

    return light_intensity; /* Return the calculated light intensity */
}
