/******************************************************************************
 *
 * Module: LDR
 *
 * File Name: ldr.h
 *
 * Description: Header file for the LDR sensor driver
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/

#ifndef LDR_SENSOR_H_
#define LDR_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* The ADC channel used by the LDR sensor (channel 0) */
#define LDR_SENSOR_CHANNEL_ID           0

/* Maximum voltage value of the LDR sensor (in Volts) */
#define LDR_SENSOR_MAX_VOLT_VALUE       2.56

/* Maximum light intensity percentage */
#define LDR_SENSOR_MAX_LIGHT_INTENSITY  100

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for reading the light intensity from the LDR sensor.
 *
 * Returns :
 * uint16 - Light intensity as a percentage (0-100%).
 */
uint16 LDR_getLightIntensity(void);

#endif /* LDR_SENSOR_H_ */
