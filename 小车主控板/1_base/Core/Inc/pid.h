#ifndef __PID_H 
#define __PID_H 
#include "tim.h"
#include "main.h"

extern float motor_pid_value[6];


typedef struct
{
	float Kp;
  float Ki;
  float Kd;
	float error_max;
	float Integral_max;
	float out_max;
	
	float error;
	float error_last;
	float out;
	float Integral;
	
} Pid_TypeDef;

float Limit_max(float input,float max);

void PID_value_Init(Pid_TypeDef *pid,const float value[6]);

float PID_calc(float Target,float Data,Pid_TypeDef *pid);

void PID_Init(void);

extern Pid_TypeDef pid_motor_1;
extern Pid_TypeDef pid_motor_2;
extern Pid_TypeDef pid_motor_3;
extern Pid_TypeDef pid_motor_4;

#endif
