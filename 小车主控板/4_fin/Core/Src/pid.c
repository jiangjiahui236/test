/*
使用说明
PID_Init进行初始化
pid_value[]为参数
增添PID环需Pid_TypeDef pid_motor声明结构体
PID_calc进行计算
*/
#include "pid.h"

//为PID参数，为别为Kp,Ki,Kd,error_max,Integral_max,out_max
float motor_pid_value[6]={200,4,0,40,400,1000};

float Limit_max(float input,float max)//限幅函数
{
	if(input > max)
	{
		input = max;
	}
	else if(input < -max)
	{
		input = -max;
	}
	return input;
}
float make_zero(float input,float min)//消抖函数
{
	if((input<min)&&(input>-min))
	{
		input = 0;
	}
	return input;
}

void PID_value_Init(Pid_TypeDef *pid,const float value[6])//参数初始化
{
	pid->Kp = value[0];
	pid->Ki = value[1];
	pid->Kd = value[2];
	pid->error_max = value[3];
	pid->Integral_max  = value[4];
	pid->out_max = value[5];
	pid->error = pid->error = pid->error_last = pid->out = pid->Integral = 0.00f;
}

float PID_calc(float Target,float Data,Pid_TypeDef *pid)//pid算法函数
{
	pid->error = Target-Data;
	pid->error = Limit_max(pid->error,pid->error_max);
	pid->Integral += pid->error;
	pid->Integral = Limit_max(pid->Integral,pid->Integral_max);
	pid->out = pid->error*pid->Kp + pid->Integral*pid->Ki + (pid->error-pid->error_last)*pid->Kd;
	pid->error_last=pid->error;
	pid->out=Limit_max(pid->out,pid->out_max);
	return pid->out;
}

/*
使用案例
PID_value_Init(&pid_motor,motor_pid_value);
PID_calc(target,data,&pid_motor);
*/

void PID_Init(void)//PID初始化
{
	PID_value_Init(&pid_motor_1,motor_pid_value);
	PID_value_Init(&pid_motor_2,motor_pid_value);
	PID_value_Init(&pid_motor_3,motor_pid_value);
	PID_value_Init(&pid_motor_4,motor_pid_value);
}

//结构体声明
Pid_TypeDef  pid_motor_1={0};
Pid_TypeDef  pid_motor_2={0};
Pid_TypeDef  pid_motor_3={0};
Pid_TypeDef  pid_motor_4={0};
