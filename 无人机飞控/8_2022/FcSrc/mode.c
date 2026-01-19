//////////////////////////////////////////////////////////////////////
/*
模式选择
*/
//////////////////////////////////////////////////////////////////////

#include "mode.h"
int my_mode;//飞行模式
int32_t hight_target,dis_x_target,dis_y_target,yaw_target;//数据目标
int32_t dis_x_zore_fix,dis_y_zore_fix;//雷达修正后的光流坐标的原点
int32_t dis_x_fix,dis_y_fix;//当前光流坐标系下的坐标
double yaw_zore,yaw_fix;
int32_t test_flag,keep_hight_flag,keep_dis_x_flag,keep_dis_y_flag,keep_yaw_flag,keep_OpenMV_data_1,keep_OpenMV_data_2;//标志位
int dis_target_ref,dis_group[2][4]={{0,8,2,0},{8,6,3,8}};//一组坐标组，一组OpenMV模式，起飞点，蓝圆，红三角，起飞点

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

void dis_target_select(int dis_target_ref)
{
	int mode=dis_group[0][dis_target_ref];
	switch(mode)
	{
		//起飞点为坐标原点
		//x：125,200,275,350,425  y：50,125,200,275,350
		case 0:{dis_x_target=0; dis_y_target=0;}break;
		case 1:{dis_x_target=50;dis_y_target=275;}break;
		case 2:{dis_x_target=200;dis_y_target=125;}break;
		case 3:{dis_x_target=275;dis_y_target=375;}break;
		case 4:{dis_x_target=350;dis_y_target=-25;}break;
		case 5:{dis_x_target=350;dis_y_target=275;}break;
		case 6:{dis_x_target=275;dis_y_target=50;}break;
		case 7:{dis_x_target=125;dis_y_target=-25;}break;
		case 8:{dis_x_target=125;dis_y_target=200;}break;
		case 9:{dis_x_target=50;dis_y_target=125;}break;
		case 10:{dis_x_target=200;dis_y_target=50;}break;
		case 11:{dis_x_target=200;dis_y_target=275;}break;
		case 12:{dis_x_target=350;dis_y_target=125;}break;
	}
}
