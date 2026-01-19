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
	my_give_vel_z = Limit_max_int(my_give_vel_z,50);
}

void keep_dis_x(int32_t dis_x_target,int32_t dis_x,int32_t max)//x轴环
{
	my_give_vel_x = (dis_x_target-dis_x)*3;
	my_give_vel_x = Limit_max_int(my_give_vel_x,max);
}

void keep_dis_y(int32_t dis_y_target,int32_t dis_y,int32_t max)//y轴环
{
	my_give_vel_y = (dis_y_target-dis_y)*3;
	my_give_vel_y = Limit_max_int(my_give_vel_y,max);
}

void keep_yaw(int32_t yaw_target,int32_t yaw)//yaw环
{
	my_give_vel_yaw = (yaw_target-yaw)*2;
	my_give_vel_yaw = Limit_max_int(my_give_vel_yaw,120);
}

void PID(void)//遥控输入值的PID运算
{
	my_give_vel_x=0;
	my_give_vel_y=0;
	my_give_vel_z=0;
	my_give_vel_yaw=0;
	
	if(test_flag)				keep_hight(hight_target,hight);
	if(keep_hight_flag)	keep_hight(hight_target,hight);
	
	if(test_flag)				keep_dis_x(dis_x_target,dis_x,50);
	if(keep_dis_x_flag)	keep_dis_x(dis_x_target,dis_x,50);
	if(keep_OpenMV_data_1)keep_dis_x(0,OpenMV_data_1,10);
	
	if(test_flag)				keep_dis_y(dis_y_target,dis_y,50);
	if(keep_dis_y_flag)	keep_dis_y(dis_y_target,dis_y,50);
	if(keep_OpenMV_data_2)keep_dis_y(0,OpenMV_data_2,10);

	if(test_flag)				keep_yaw(yaw_target,yaw);
	if(keep_yaw_flag)		keep_yaw(yaw_target,yaw);
}
