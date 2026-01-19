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
int32_t keep_hight_flag,keep_dis_x_flag,keep_dis_y_flag,keep_yaw_flag,keep_OpenMV_data_1,keep_OpenMV_data_2,keep_radar_x_flag,keep_radar_y_flag;//标志位

void mode_select(int mode)//选择飞行模式，改变标志位
{
	keep_hight_flag=0;keep_dis_x_flag=0;keep_OpenMV_data_1=0;keep_dis_y_flag=0;keep_OpenMV_data_2=0;keep_yaw_flag=0;keep_radar_x_flag=0;keep_radar_y_flag=0;
	switch(mode)
	{
		case 1:{keep_yaw_flag=1;keep_hight_flag=1;keep_dis_x_flag=1;keep_dis_y_flag=1;}break;//测试模式
		case 2:{keep_yaw_flag=1;keep_hight_flag=1;keep_dis_x_flag=1;keep_dis_y_flag=1;}break;//光流xy定高定角度
		case 3:{keep_yaw_flag=1;keep_hight_flag=1;keep_OpenMV_data_1=1;keep_OpenMV_data_2=1;}break;//OpenMV定高定角度
		case 4:{keep_yaw_flag=1;keep_hight_flag=1;keep_radar_x_flag=1;keep_radar_y_flag=1;}break;//激光雷达xy定高定角度
	}
}
