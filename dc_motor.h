/******************************************************************************
 *
 * Module: DC Motor Driver
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC Motor driver.
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enum to define the motor state */
typedef enum {
    MOTOR_STOP,   /* Motor Stop */
    MOTOR_CW,     /* Motor Clockwise */
    MOTOR_ACW     /* Motor Anti-Clockwise */
} DcMotor_State;

/* Structure to hold the motor pin configuration */
#define IN1_PORT_ID     PORTB_ID	/* port for controlling motor direction (IN1)*/
#define IN1_PIN_ID      PIN0_ID /* pin for controlling motor direction (IN1) */
#define IN2_PORT_ID     PORTB_ID  /* port for controlling motor direction (IN2)*/
#define IN2_PIN_ID      PIN1_ID /* pin for controlling motor direction (IN1) */
#define ENABLE_PORT_ID  PORTB_ID /* port for enabling motor (connected to PWM)*/
#define ENABLE_PIN_ID   PIN3_ID /* pin for enabling motor (connected to PWM) */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function to initialize the DC motor.
 * Parameters:
 *    config: Pointer to the motor configuration structure.
 */
void DcMotor_Init(void);

/*
 * Function to rotate the motor in a specific direction and control the speed.
 * Parameters:
 *    state: The motor state (CW, A-CW, or Stop).
 *    speed: The motor speed as a percentage (0 to 100%).
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
