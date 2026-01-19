//////////////////////////////////////////////////////////////////////
/*
模式选择
*/
//////////////////////////////////////////////////////////////////////

#include "mode.h"
int my_mode;//飞行模式
int32_t hight_target,dis_x_target,dis_y_target,yaw_target;//数据目标
int32_t hight_now,dis_x_now,dis_y_now,yaw_now;//当前数据
int32_t test_flag,keep_hight_flag,keep_dis_x_flag,keep_dis_y_flag,keep_yaw_flag,keep_OpenMV_data_1,keep_OpenMV_data_2;//标志位

void mode_select(int mode)//选择飞行模式，改变标志位
{
	switch(mode)
	{
		case 0:{test_flag=0;keep_hight_flag=0;keep_dis_x_flag=0;keep_OpenMV_data_1=0;keep_dis_y_flag=0;keep_OpenMV_data_2=0;keep_yaw_flag=0;}break;//不使用PID模式
		case 1:{test_flag=1;keep_hight_flag=0;keep_dis_x_flag=0;keep_OpenMV_data_1=0;keep_dis_y_flag=0;keep_OpenMV_data_2=0;keep_yaw_flag=0;}break;//测试模式
		case 2:{test_flag=0;keep_hight_flag=1;keep_dis_x_flag=1;keep_OpenMV_data_1=0;keep_dis_y_flag=1;keep_OpenMV_data_2=0;keep_yaw_flag=1;}break;//xy定高定角度
		case 3:{test_flag=0;keep_hight_flag=1;keep_dis_x_flag=0;keep_OpenMV_data_1=1;keep_dis_y_flag=0;keep_OpenMV_data_2=1;keep_yaw_flag=1;}break;//OpenMV定高定角度
	}
}
