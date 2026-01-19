//使用说明：Encoder_Init进行初始化，GetEncoder获取数据储存在Encoder[4]，滴答定时器中5ms执行一次GetEncoder
#include "encoder.h"
#include "math.h"
#include "mpu9250.h"


int Encoder[4]={0};
long dis,dis_;

void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);
}

void GetEncoder(void)//根据运动方向取正负
{
		Encoder[0]=-(short)(__HAL_TIM_GET_COUNTER(&htim2));//读取脉冲数
		__HAL_TIM_SET_COUNTER(&htim2,0);//再计数器清零 
		Encoder[1]=-(short)(__HAL_TIM_GET_COUNTER(&htim3));//读取脉冲数
		__HAL_TIM_SET_COUNTER(&htim3,0);//再计数器清零 
		Encoder[2]=(short)(__HAL_TIM_GET_COUNTER(&htim4));//读取脉冲数
		__HAL_TIM_SET_COUNTER(&htim4,0);//再计数器清零 
		Encoder[3]=(short)(__HAL_TIM_GET_COUNTER(&htim5));//读取脉冲数
		__HAL_TIM_SET_COUNTER(&htim5,0);//再计数器清零 
		dis_ += Encoder[0]+Encoder[1]+Encoder[2]+Encoder[3];
		dis=dis_/18.5;
}
