 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void ADC_init(void)
{
    /* ADMUX Register Bits Description:
     * REFS1:0 = 11 to choose reference voltage as internal 2.56V
     * ADLAR = 0 right adjusted
     * MUX4:0 = 00000 to choose channel 0 as initialization
     */
    ADMUX = (1<<REFS1) | (1<<REFS0);  // Set internal 2.56V reference voltage

    /* ADCSRA Register Bits Description:
     * ADEN    = 1 Enable ADC
     * ADIE    = 0 Disable ADC Interrupt
     * ADATE   = 0 Disable Auto Trigger
     * ADPS2:0 = 111 to choose ADC_Clock = F_CPU/128 = 16Mhz/128 = 125Khz --> ADC must operate in range 50-200Khz
     */
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Enable ADC, set prescaler to F_CPU/128
}

uint16 ADC_readChannel(uint8 channel_num)
{
    channel_num &= 0x07; /* Ensure the channel number is between 0 and 7 */
    ADMUX &= 0xE0;       /* Clear first 5 bits in ADMUX (channel number MUX4:0) */
    ADMUX |= channel_num; /* Set the required channel number in MUX4:0 */

    SET_BIT(ADCSRA, ADSC); /* Start conversion by setting ADSC */

    while (BIT_IS_CLEAR(ADCSRA, ADIF)); /* Wait for conversion to complete */

    SET_BIT(ADCSRA, ADIF); /* Clear the ADIF flag by writing '1' to it */

    return ADC; /* Return the converted digital value from the ADC data register */
}
