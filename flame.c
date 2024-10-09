#include "gpio.h"
#include "flame.h"

/* Initialize the flame sensor pin as input */
void FlameSensor_init(void)
{
    /* Set the flame sensor pin as input */
	GPIO_setupPinDirection(FLAME_SENSOR_PORT_ID, FLAME_SENSOR_PIN_ID, PIN_INPUT);
}

/* Get the current value of the flame sensor */
uint8 FlameSensor_getValue(void)
{
    /* Read and return the pin value (0 or 1) */
    return GPIO_readPin(FLAME_SENSOR_PORT_ID, FLAME_SENSOR_PIN_ID);
}
