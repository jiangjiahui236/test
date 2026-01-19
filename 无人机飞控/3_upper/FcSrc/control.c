//////////////////////////////////////////////////////////////////////
/*
底层控制
*/
//////////////////////////////////////////////////////////////////////

#include "control.h"
int my_code_control_flag;//是否使用自定义变量代替遥控输入的标志位
int my_give_vel_x,my_give_vel_y,my_give_vel_z,my_give_vel_yaw;//自定义变量代替遥控输入
int Task_time_dly_cnt_ms;//普通计时
unsigned int  mission_step;//步骤

void all_data_init(void)//步骤二进行全部数据的初始化
{
	Task_time_dly_cnt_ms=0;
}

void User_Task_Delay(int ms)//步骤中进行延时函数
{
	if(Task_time_dly_cnt_ms<ms){Task_time_dly_cnt_ms+=20;}
	else{Task_time_dly_cnt_ms=0;mission_step++;}			
}
