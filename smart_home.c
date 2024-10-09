/******************************************************************************
 *
 * Module: Smart Home Main
 *
 * File Name: main.c
 *
 * Description: Main program to control the smart home system.
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/
#include "lcd.h"
#include "led.h"
#include "lm35_sensor.h"
#include "buzzer.h"
#include "dc_motor.h"
#include "flame.h"
#include "ldr_sensor.h"
#include <util/delay.h>

#define FAN_OFF_TEMP_THRESHOLD       25
#define FAN_LOW_SPEED_TEMP_THRESHOLD 30
#define FAN_MED_SPEED_TEMP_THRESHOLD 35
#define FAN_HIGH_SPEED_TEMP_THRESHOLD 40

int main(void)
{
    uint16 light_intensity = 0;
    uint16 temperature = 0;
    uint16 fire_detected=0;
    /* Initialize modules */
    ADC_init();
    LCD_init();
    LEDS_init();  /* Assuming led_config is defined with pin and logic settings */
    DcMotor_Init();
    FlameSensor_init();
    Buzzer_init();

    LCD_displayStringRowColumn(0, 3, "Smart Home");
    _delay_ms(1000);
    LCD_clearScreen();
    while (1)
    {
        /* Read light intensity from LDR */
        light_intensity = LDR_getLightIntensity();

        /* Control LEDs based on light intensity */
        if (light_intensity < 15) {
            LED_on(LED_RED);
            LED_on(LED_GREEN);
            LED_on(LED_BLUE);
        } else if (light_intensity <= 50) {
            LED_on(LED_RED);
            LED_on(LED_GREEN);
            LED_off(LED_BLUE);
        } else if (light_intensity <= 70) {
            LED_on(LED_RED);
            LED_off(LED_GREEN);
            LED_off(LED_BLUE);
        } else {
            LED_off(LED_RED);
            LED_off(LED_GREEN);
            LED_off(LED_BLUE);
        }
        /* Detect fire using the flame sensor*/
        fire_detected = FlameSensor_getValue();
        if (fire_detected) {
        	LCD_clearScreen();
        	while(fire_detected){
				LCD_displayStringRowColumn(0, 0, "Critical Alert!");
				LCD_moveCursor(1, 0);
				 LCD_displayString("Fire Fire Fire!");
				Buzzer_on();
				fire_detected = FlameSensor_getValue();
        		}
        	LCD_clearScreen();
            }
         else {
            Buzzer_off();
        }
        Buzzer_off();
        /* Read temperature from LM35 */
        temperature = LM35_getTemperature();

        /* Control fan speed based on temperature */
        if (temperature < FAN_OFF_TEMP_THRESHOLD) {
            DcMotor_Rotate(MOTOR_STOP, 0);
            LCD_moveCursor(0, 3);
            LCD_displayString("Fan is Off   ");
        } else if (temperature < FAN_LOW_SPEED_TEMP_THRESHOLD) {
            DcMotor_Rotate(MOTOR_CW, 25);
            LCD_moveCursor(0, 3);
            LCD_displayString("Fan is On    ");
        } else if (temperature < FAN_MED_SPEED_TEMP_THRESHOLD) {
            DcMotor_Rotate(MOTOR_CW, 50);
            LCD_moveCursor(0, 3);
            LCD_displayString("Fan is On    ");
        } else if (temperature < FAN_HIGH_SPEED_TEMP_THRESHOLD) {
            DcMotor_Rotate(MOTOR_CW, 75);
            LCD_moveCursor(0, 3);
            LCD_displayString("Fan is On    ");
        } else {
            DcMotor_Rotate(MOTOR_CW, 100);
            LCD_moveCursor(0, 3);
            LCD_displayString("Fan is On    ");
        }

        /* Display temperature and light intensity on the LCD */

        LCD_moveCursor(1, 0);
        LCD_displayString("Temp=");
        LCD_intgerToString(temperature);
        LCD_displayString("C ");

        LCD_displayString("LDR=");
        LCD_intgerToString(light_intensity);
        LCD_displayString("%");

        /* Small delay for stability */
        _delay_ms(500);
    }
}
