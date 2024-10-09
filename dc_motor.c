/******************************************************************************
 *
 * Module: DC Motor Driver
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC Motor driver to control the fan speed and direction.
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function to initialize the DC motor by setting up the motor control pins.
 * Motor starts in the stop state.
 */
void DcMotor_Init(void)
{
   /* Set the direction of the motor control pins (IN1, IN2, and Enable) */
    GPIO_setupPinDirection(IN1_PORT_ID,IN1_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(IN2_PORT_ID,IN2_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(ENABLE_PORT_ID,ENABLE_PIN_ID, PIN_OUTPUT);

    /* Stop the motor initially */
    DcMotor_Rotate(MOTOR_STOP, 0);
}

/*
 * Function to control the motor state (Clockwise, Anti-Clockwise, or Stop) and adjust its speed.
 * The speed is set using a PWM signal with a duty cycle based on the input percentage.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
    /* Ensure the speed is within the 0-100% range */
    if (speed > 100) {
        speed = 100;
    }
    PWM_Timer0_Start(speed);
    /* Set the motor state and control the direction pins */
    switch(state)
    {
        case MOTOR_CW:
            /* Clockwise rotation: IN1 = HIGH, IN2 = LOW */
            GPIO_writePin(IN1_PORT_ID,IN1_PIN_ID,LOGIC_HIGH);
            GPIO_writePin(IN2_PORT_ID,IN2_PIN_ID,LOGIC_LOW);
            break;

        case MOTOR_ACW:
            /* Anti-clockwise rotation: IN1 = LOW, IN2 = HIGH */
            GPIO_writePin(IN1_PORT_ID,IN1_PIN_ID,LOGIC_LOW);
            GPIO_writePin(IN2_PORT_ID,IN2_PIN_ID,LOGIC_HIGH);
            break;

        case MOTOR_STOP:
        default:
            /* Stop the motor: IN1 = LOW, IN2 = LOW */
            GPIO_writePin(IN1_PORT_ID,IN1_PIN_ID,LOGIC_LOW);
            GPIO_writePin(IN2_PORT_ID,IN2_PIN_ID,LOGIC_LOW);
            speed = 0; /* Ensure speed is 0 when the motor is stopped */
            break;
    }

    /* Set the motor speed using PWM on the enable pin */

}

