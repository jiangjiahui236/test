#include "control.h"//代码详见滴答定时器，main函数
#include "encoder.h"

extern	float pitch,roll; 	        //欧拉角

int start_flag=0;//启动标志
int move_flag=0;
volatile int keep_dis_1_flag=0,keep_dis_2_flag=0,keep_dis_3_flag=0,keep_dis_23_flag=0;
int keep_yaw_flag=0;
int IR_1_flag=0,IR_2_flag=0,IR_3_flag=0,IR_4_flag=0;

int target_speek[4]={0};//最大约为35
int basic_speek=0;
float yaw_set=0;
float keep_yaw_pid_Kp=0.6,keep_yaw_pid_out=0;
int dis_target;
float keep_dis_pid_Kp=0.4,keep_dis_pid_out=0,keep_dis_1_pid_out_max=20,keep_dis_1_pid_Kp=0.2;



int servo_flag;

void advance(int value)//前进
{
  value=Limit_max(value,30);
	target_speek[0]+=value;
	target_speek[1]+=value;
	target_speek[2]+=value;
	target_speek[3]+=value;
}

void transverse(int value)//右移
{
	target_speek[0]+=value;
	target_speek[1]-=value;
	target_speek[2]-=value;
	target_speek[3]+=value;
}

void clockwise(int value)//顺时针旋转
{
	value=Limit_max(value,10);
	target_speek[0]+=value;
	target_speek[1]+=value;
	target_speek[2]-=value;
	target_speek[3]-=value;
}

void restart(void)//停止
{
	target_speek[0]=0;
	target_speek[1]=0;
	target_speek[2]=0;
	target_speek[3]=0;
}

void keep_yaw(void)//保持方向
{
	keep_yaw_pid_out=(yaw_set-yaw)*keep_yaw_pid_Kp;//外环单Kp的pid
	clockwise(keep_yaw_pid_out);
}

void keep_dis_1(void)//保持距离，前方超声波//////////////////////////////////////////改为了前进位置环pid
{
	keep_dis_pid_out=(dis_target-dis)*keep_dis_1_pid_Kp;
	if(keep_dis_pid_out>keep_dis_1_pid_out_max)keep_dis_pid_out=keep_dis_1_pid_out_max;
	if(keep_dis_pid_out<-keep_dis_1_pid_out_max)keep_dis_pid_out=-keep_dis_1_pid_out_max;
	advance(keep_dis_pid_out);
}

void keep_dis_2(void)//左侧超声波
{
//	keep_dis_pid_out=((float)dis_target[1]-(float)dis_2)*keep_dis_pid_Kp;
	transverse(keep_dis_pid_out);
}

void keep_dis_3(void)//右侧超声波
{
//	keep_dis_pid_out=((float)dis_target[2]-(float)dis_3)*keep_dis_pid_Kp;
	transverse(-keep_dis_pid_out);
}

void keep_dis_23(void)//过垄道保持俩侧等距
{
	keep_dis_pid_out=((float)dis_3-(float)dis_2)*keep_dis_pid_Kp;
	transverse(keep_dis_pid_out);
}


/*
示例代码
		来回移动
		basic_speek=10;
		HAL_Delay(3000);
		basic_speek=0;
		HAL_Delay(2000);
		basic_speek=-10;
		HAL_Delay(3000);
		basic_speek=0;
		HAL_Delay(2000);

*/
