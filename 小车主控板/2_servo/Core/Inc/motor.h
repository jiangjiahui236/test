#ifndef __MOTOR_H 
#define __MOTOR_H 

#include "tim.h"
#include "gpio.h"
#include "pid.h"

extern int set_pwm[4];
extern int zero_pwm[4];

void motor_Init(void);
void set_motor_pwm(int set_pwm[4]);

#endif
