#ifndef __SIM_MATH_H
#define __SIM_MATH_H

#include "stm32f4xx_hal.h"

float sim_FAbs(float x);

int sim_Abs(int x);

int sim_int(uint8_t s);

void user_delay_us(uint16_t us);
#endif
