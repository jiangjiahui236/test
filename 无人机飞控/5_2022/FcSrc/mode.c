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

int32_t dis_x_location,dis_y_location;//要定位的坐标
int32_t task_1=2,task_2=10
;//定位目标的数字

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

void task_select(int mode)
{
	switch(mode)
	{
		//x：125,200,275,350,425  y：50,125,200,275,350
		case 0:{dis_x_location=75; dis_y_location=75;}break;
		case 1:{dis_x_location=125;dis_y_location=350;}break;
		case 2:{dis_x_location=275;dis_y_location=200;}break;
		case 3:{dis_x_location=350;dis_y_location=450;}break;
		case 4:{dis_x_location=425;dis_y_location=50;}break;
		case 5:{dis_x_location=425;dis_y_location=350;}break;
		case 6:{dis_x_location=350;dis_y_location=125;}break;
		case 7:{dis_x_location=200;dis_y_location=125;}break;
		case 8:{dis_x_location=200;dis_y_location=275;}break;
		case 9:{dis_x_location=125;dis_y_location=200;}break;
		case 10:{dis_x_location=275;dis_y_location=50;}break;
		case 11:{dis_x_location=275;dis_y_location=350;}break;
		case 12:{dis_x_location=425;dis_y_location=200;}break;
	}
}
