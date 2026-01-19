//////////////////////////////////////////////////////////////////////
/*
各个环PID
*/
//////////////////////////////////////////////////////////////////////

#include "pid.h"
#include "control.h"
#include "get_data.h"
#include "mode.h"
#include "my_uart.h"
#include "mode.h"
#include "mbotLinuxUsart.h"
#include <math.h>

double KP_xy=1,KI_xy=0,KD_xy=15,intrgrate_max=30;//光流pid参数
double KP_MV=0.6,KI_MV=0,KD_MV=15;//OpenMV的pid参数
double KP_radar=0.8,KI_radar=0,KD_radar=15;//激光雷达pid参数


int Limit_max_int(int input,int max)//限幅函数
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

void keep_hight(int32_t hight_target,int32_t hight)//高度环
{
	my_give_vel_z = (hight_target-hight)*3;
	my_give_vel_z = Limit_max_int(my_give_vel_z,30);
}

void keep_dis_x(double KP,double KD,int32_t dis_x_target,int32_t dis_x,int32_t max)//x轴环
{
	int32_t error,KP_out,KI_out,KD_out,total_out;
	static int32_t dis_intrgrate,error_last;
	
	error = dis_x_target-dis_x;
	KP_out = KP*error;
	
	KD_out = (error-error_last)*KD;
	if(error_last!=error) error_last = error;
	
	dis_intrgrate += error;
	KI_out=Limit_max_int(KI_out,intrgrate_max);
	
	total_out = KP_out+KI_out+KD_out;
	total_out = Limit_max_int(total_out,max);
	
	my_give_vel_x = total_out;
}

void keep_dis_y(double KP,double KD,int32_t dis_y_target,int32_t dis_y,int32_t max)//y轴环
{
	int32_t error,KP_out,KI_out,KD_out,total_out;
	static int32_t dis_intrgrate,error_last;
	
	error = dis_y_target-dis_y;
	KP_out = KP*error;
	
	KD_out = (error-error_last)*KD;
	if(error_last!=error) error_last = error;
	
	dis_intrgrate += error;
	KI_out=Limit_max_int(KI_out,intrgrate_max);
	
	total_out = KP_out+KI_out+KD_out;
	total_out = Limit_max_int(total_out,max);
	
	my_give_vel_y = total_out;
}


void keep_yaw(int32_t yaw_target,int32_t yaw)//yaw环8
{
	my_give_vel_yaw = (yaw_target-yaw)*4;
	my_give_vel_yaw = Limit_max_int(my_give_vel_yaw,120);
}

void PID(void)//遥控输入值的PID运算
{
	my_give_vel_x=0;
	my_give_vel_y=0;
	my_give_vel_z=0;
	my_give_vel_yaw=0;
	
	if(keep_hight_flag)		keep_hight(hight_target,hight);
	
	if(keep_dis_x_flag)	  keep_dis_x(KP_xy,KD_xy,dis_x_target,dis_x_fix,20);
	if(keep_OpenMV_data_1)keep_dis_x(KP_MV,KD_MV,0,OpenMV_data_1,20);
	if(keep_radar_x_flag) keep_dis_x(KP_radar,KD_radar,dis_x_target,radar_data_1,20);
		
	if(keep_dis_y_flag)	  keep_dis_y(KP_xy,KD_xy,dis_y_target,dis_y_fix,20);
	if(keep_OpenMV_data_2)keep_dis_y(KP_MV,KD_MV,0,OpenMV_data_2,20);
	if(keep_radar_y_flag) keep_dis_y(KP_radar,KD_radar,dis_y_target,radar_data_2,20);
		
	if(keep_yaw_flag)			keep_yaw(yaw_target,yaw_fix);
}
