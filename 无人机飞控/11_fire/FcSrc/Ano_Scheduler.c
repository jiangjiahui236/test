/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：任务调度
**********************************************************************************/
#include "Ano_Scheduler.h"
#include "User_Task.h"

//////////////////////////////////////////////////////////////////////
//用户程序调度器
//////////////////////////////////////////////////////////////////////
#include "get_data.h"
#include "NiMing_UpperConputer.h"
#include "control.h"
#include "pid.h"
#include "mode.h"
#include "KEY.h"
#include "oled.h"
#include "stdio.h"
#include "buzzer.h"
#include "mbotLinuxUsart.h"
#include "my_uart.h"
#include "mode.h"
#include "Drv_led.h"

int cnt;
int urst2_Send_data;
int Send_fire_flag;
int wait_time;
int car_time;
int rgb_flag,rgb_time;

static void Loop_1000Hz(void) //1ms执行一次
{
	//////////////////////////////////////////////////////////////////////
	get_data();//获取数据
//	ANODT_SendF4((int)(dis_x_target),(int)(dis_x_fix),(int)(dis_y_fix),(int)(yaw));//发送数据到匿名上位机
//	ANODT_SendF4((int)(dis_x_target),(int)(dis_y_target),(int)(radar_data_1),(int)(radar_data_2));//发送数据到匿名上位机
	time_cnt_ms++;//计时
	
	PID();//遥控输入值的PID运算
	//////////////////////////////////////////////////////////////////////
}

static void Loop_500Hz(void) //2ms执行一次
{
	//////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////
}

static void Loop_200Hz(void) //5ms执行一次
{
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
}

static void Loop_100Hz(void) //10ms执行一次
{
	//////////////////////////////////////////////////////////////////////
	radar_wait_time++;
	KEY_1+=KEY_Scan_1(1);
	KEY_2+=KEY_Scan_2(1);
	KEY_3_last=KEY_3;
	KEY_3+=KEY_Scan_3(1);
	if(KEY_3!=KEY_3_last)OLED_Clear();//如果KEY3变换了，则清屏，要切换显示内容
	
	if(KEY_1==1)	usartSendData(5000,to_radar_data_2,to_radar_data_3,to_radar_data_4);//雷达坐标重建
	else if(KEY_1==2) KEY_1=0;
	else usartSendData(0,to_radar_data_2,to_radar_data_3,to_radar_data_4);
	
//	if(KEY_2==1)	{set_dis_zero();}//光流坐标重建
//	else if(KEY_2==2) KEY_2=0;
	
	if(KEY_2==4) KEY_2=0;
	if(KEY_3==5) KEY_3=0;
	//////////////////////////////////////////////////////////////////////
}

static void Loop_50Hz(void) //20ms执行一次
{
	//////////////////////////////////////////////////////////////////////
	urst2_Send_data=dis_group[1][dis_target_ref];
	if(KEY_2!=0)urst2_Send_data=KEY_2;
	MY_urst2_Send(urst2_Send_data);
	if(Send_fire_flag)MY_urst1_Send_fire();
	MY_urst1_Send_xy();///////////////////////////////////////////////////////////////////////////////////////////////
	UserTask_OneKeyCmd();
	//////////////////////////////////////////////////////////////////////
}

static void Loop_20Hz(void) //50ms执行一次
{
	//////////////////////////////////////////////////////////////////////
	wait_time+=50;
	//////////////////////////////////////////////////////////////////////
}

static void Loop_2Hz(void) //500ms执行一次
{
	//////////////////////////////////////////////////////////////////////
	if(rgb_flag) rgb_time=!rgb_time;
	else rgb_time=0;
	if(rgb_time) {led.brightness[0]=20;led.brightness[1]=20;led.brightness[2]=20;}
	else {led.brightness[0]=0;led.brightness[1]=0;led.brightness[2]=0;}
	
	
	
	if(KEY_3==0)my_oled_show_0();
	if(KEY_3==1)my_oled_show_1();
	if(KEY_3==2)my_oled_show_2();
	if(KEY_3==3)my_oled_show_3();
	if(KEY_3==4)my_oled_show_4();
	cnt++;
	//////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////
//调度器初始化
//////////////////////////////////////////////////////////////////////
//系统任务配置，创建不同执行频率的“线程”
static sched_task_t sched_tasks[] =
	{
		{Loop_1000Hz, 1000, 0, 0},
		{Loop_500Hz, 500, 0, 0},
		{Loop_200Hz, 200, 0, 0},
		{Loop_100Hz, 100, 0, 0},
		{Loop_50Hz, 50, 0, 0},
		{Loop_20Hz, 20, 0, 0},
		{Loop_2Hz, 2, 0, 0},
};
//根据数组长度，判断线程数量
#define TASK_NUM (sizeof(sched_tasks) / sizeof(sched_task_t))

void Scheduler_Setup(void)
{
	uint8_t index = 0;
	//初始化任务表
	for (index = 0; index < TASK_NUM; index++)
	{
		//计算每个任务的延时周期数
		sched_tasks[index].interval_ticks = TICK_PER_SECOND / sched_tasks[index].rate_hz;
		//最短周期为1，也就是1ms
		if (sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}
//这个函数放到main函数的while(1)中，不停判断是否有线程应该执行
void Scheduler_Run(void)
{
	uint8_t index = 0;
	//循环判断所有线程，是否应该执行

	for (index = 0; index < TASK_NUM; index++)
	{
		//获取系统当前时间，单位MS
		uint32_t tnow = GetSysRunTimeMs();
		//进行判断，如果当前时间减去上一次执行的时间，大于等于该线程的执行周期，则执行线程
		if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{

			//更新线程的执行时间，用于下一次判断
			sched_tasks[index].last_run = tnow;
			//执行线程函数，使用的是函数指针
			sched_tasks[index].task_func();
		}
	}
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
