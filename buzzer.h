

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/* Buzzer Pin configuration */
#define BUZZER_PORT_ID  PORTD_ID
#define BUZZER_PIN_ID   PIN3_ID

/* Function Prototypes */
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
