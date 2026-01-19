#include "pid_init.h"
float yaw_Kpid[3] = {2.3,0,0};//5 0.5 2 0.2    2.85 0.07    2.9 0.15   3 0.12 0.01

float spd_Kpid[3]={500,400,25};//400 250 60 /20 0.07/500,400,25

float ultrasonic1_Kpid[3] = {3.2,0.02,0.01};//3.1,0.012,0.01   3.2 0.02 0.01
float ultrasonic2_Kpid[3] = {3.0,0.012,0.01}; //4 0.024 0.01
float ultrasonic3_Kpid[3] = {3.2,0.02,0.01}; //4 0.012 0.01 3.0 0.015 0.01    3.1,0.02,0.01

float ciecle_Kpid[3] = {5,3,3};

float OpenMV_X_Kpid[3] = {0.6,0,0};
float OpenMV_Y_Kpid[3] = {1,0,0};

void pid_Init()
{
	PID_Init(&pid_spd1,PID_DELTA,spd_Kpid,16799,14000);
	PID_Init(&pid_spd2,PID_DELTA,spd_Kpid,16799,14000);
	PID_Init(&pid_spd3,PID_DELTA,spd_Kpid,16799,14000);
	PID_Init(&pid_spd4,PID_DELTA,spd_Kpid,16799,14000);
	
	PID_Init(&pid_yaw,PID_POSITION,yaw_Kpid,HighSpeed,HighSpeed);
	
	PID_Init(&pid_ultrasound1,PID_DELTA,ultrasonic1_Kpid,HighSpeed,HighSpeed);
	PID_Init(&pid_ultrasound2,PID_DELTA,ultrasonic2_Kpid,HighSpeed,HighSpeed);
	PID_Init(&pid_ultrasound3,PID_DELTA,ultrasonic3_Kpid,HighSpeed,HighSpeed);
	
//	PID_Init(&pid_ciecle,PID_POSITION,ciecle_Kpid,16799,14000);
	
	PID_Init(&pid_OpenMV_X,PID_POSITION,OpenMV_X_Kpid,MidSpeed,MidSpeed);
	PID_Init(&pid_OpenMV_Y,PID_POSITION,OpenMV_Y_Kpid,MidSpeed,MidSpeed);
}
