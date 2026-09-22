#ifndef __BUZZER_H
#define __BUZZER_H

#include "main.h"

void Buzzer_init(void);
void Buzzer_SetFrequency(uint32_t freq);
void Buzzer_on(void);
void Buzzer_off(void);
#endif
