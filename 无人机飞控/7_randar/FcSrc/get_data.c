//////////////////////////////////////////////////////////////////////
/*
获取数据
*/
//////////////////////////////////////////////////////////////////////

#include "get_data.h"
#include "ANO_LX.h"
#include "stm32f4xx.h"
#include "LX_FC_EXT_Sensor.h"
#include "Drv_AnoOf.h"
#include "mode.h"

double rol,pit,yaw,yaw_part,yaw_last,yaw_round;//imu输出的欧拉角，单位度
int16_t vel_x,vel_y;//速度，单位cm/s
int32_t hight;//高度,单位cm
int32_t dis_x,dis_y,dis_x___,dis_y___;//累积的距离,单位cm
int32_t dx_fix_intergral,dy_fix_intergral;

void get_data(void)//获取各种数据
{
//数据来自ANO_LX.h凌霄接收IMU数据
	rol = (fc_att.st_data.rol_x100)/100.0;
	pit = (fc_att.st_data.pit_x100)/100.0;
	
	yaw_part = fc_att.st_data.yaw_x100;
	if((yaw_last>9000)&&(yaw_part<-9000)) yaw_round++;
	if((yaw_last<-9000)&&(yaw_part>9000)) yaw_round--;
	yaw = yaw_round*360 + yaw_part/100.0;
	yaw_last=yaw_part;
	yaw_fix=yaw-yaw_zore;
	
////数据来自光流数据融合后
//	vel_x = ano_of.of2_dx_fix;
//	vel_y = ano_of.of2_dy_fix;	
	////////////////////////////////////////////////////
	if(ano_of.of2_dx_fix<200&&ano_of.of2_dx_fix>-200)	dx_fix_intergral += ano_of.of2_dx_fix;
	if(ano_of.of2_dy_fix<200&&ano_of.of2_dy_fix>-200)	dy_fix_intergral += ano_of.of2_dy_fix;
	////////////////////////////////////////////////////

	dis_x = (int32_t) dx_fix_intergral*1.95/1000;
	dis_y = (int32_t) dy_fix_intergral*1.95/1000;
	dis_x_fix=dis_x-dis_x_zore_fix;////////////////////////////////////////////////////////////////////
	dis_y_fix=dis_y-dis_y_zore_fix;////////////////////////////////////////////////////////////////////
	
	
//数据来自ANO_LX.h凌霄接收IMU数据
	vel_x = fc_vel.st_data.vel_x;
	vel_y = fc_vel.st_data.vel_y;	
//	dis_x = -fc_dis.st_data.pix_x;
//	dis_y = -fc_dis.st_data.pix_y;
	hight = fc_hight.st_data.alt_add;	
}

void set_dis_zero(void)
{
	dx_fix_intergral=0;
	dy_fix_intergral=0;
	dis_x_zore_fix=0;
	dis_y_zore_fix=0;
}
