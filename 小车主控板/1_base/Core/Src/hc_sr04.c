#include "hc_sr04.h"//使用说明：HcSr04_TIM_start开启定时器中断，HcSr04_start发送超声波

uint32_t   dis_1,dis_2,dis_3;//超声波测距
uint8_t   hc_1_flag = 0,hc_2_flag = 0,hc_3_flag = 0;
uint16_t  hc_1_HighTime, hc_1_RisingTime, hc_1_FallingTime;
uint16_t  hc_2_HighTime, hc_2_RisingTime, hc_2_FallingTime;
uint16_t  hc_3_HighTime, hc_3_RisingTime, hc_3_FallingTime;

void HcSr04_TIM_start(void)//开启接收中断函数
{
		HAL_TIM_IC_Start_IT(&htim9, TIM_CHANNEL_1);
		HAL_TIM_IC_Start_IT(&htim9, TIM_CHANNEL_2);
		HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_1);
}

void HcSr04_start_1(void)//发送超声波
{  
  HAL_GPIO_WritePin(TRIG_1_GPIO_Port, TRIG_1_Pin, GPIO_PIN_SET);
  HcSr04_Delay(500);
  HAL_GPIO_WritePin(TRIG_1_GPIO_Port, TRIG_1_Pin, GPIO_PIN_RESET);
}
void HcSr04_start_2(void)//发送超声波
{
  HAL_GPIO_WritePin(TRIG_2_GPIO_Port, TRIG_2_Pin, GPIO_PIN_SET);
  HcSr04_Delay(500);
  HAL_GPIO_WritePin(TRIG_2_GPIO_Port, TRIG_2_Pin, GPIO_PIN_RESET);
}
void HcSr04_start_3(void)//发送超声波
{
  HAL_GPIO_WritePin(TRIG_3_GPIO_Port, TRIG_3_Pin, GPIO_PIN_SET);
  HcSr04_Delay(500);
  HAL_GPIO_WritePin(TRIG_3_GPIO_Port, TRIG_3_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  超声波延时函数
  * @param  i 延时时间
  * @retval 无
  */
void HcSr04_Delay(uint16_t i){
	
	while(i--);
}

/**
  * @brief  HAL的输入捕获回调函数
  * @param  htim TIM句柄结构体指针
  * @retval 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /*防止未使用参数(s)编译警告*/
	UNUSED(htim);
	
	if(htim->Instance == htim9.Instance)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(hc_1_flag == 0)          //捕获上升沿
			{
				hc_1_RisingTime = HAL_TIM_ReadCapturedValue(&htim9, TIM_CHANNEL_1);                         //获取上升沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim9, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);        //切换捕获极性
				HAL_TIM_IC_Start_IT(&htim9, TIM_CHANNEL_1);     //切换捕获极性后需重新启动
 
				hc_1_flag = 1;          	 //上升沿、下降沿捕获标志位
			}
			else if(hc_1_flag == 1)     //捕获下降沿
			{
				hc_1_FallingTime = HAL_TIM_ReadCapturedValue(&htim9, TIM_CHANNEL_1);                       //获取下降沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim9, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);        //切换捕获极性
				HAL_TIM_IC_Start_IT(&htim9, TIM_CHANNEL_1);   	 //切换捕获极性后需重新启动

				hc_1_HighTime = hc_1_FallingTime < hc_1_RisingTime ? hc_1_FallingTime + 0xffff - hc_1_RisingTime + 1 : hc_1_FallingTime - hc_1_RisingTime;
				//高电平持续时间 = 下降沿时间点 - 上升沿时间点
				dis_1 = hc_1_HighTime * 17 / 100; //计算超声波测量距离
				//i++;//累加计数
				hc_1_flag = 0;		  			 //一次采集完毕，清零
//				dis_1=KalmanFilter(dis_1);
				if(dis_1>=1000)dis_1=1000;
			}
		}
	}
	
	if(htim->Instance == htim9.Instance)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(hc_2_flag == 0)          //捕获上升沿
			{
				hc_2_RisingTime = HAL_TIM_ReadCapturedValue(&htim9, TIM_CHANNEL_2);                         //获取上升沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim9, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);        //切换捕获极性
				HAL_TIM_IC_Start_IT(&htim9, TIM_CHANNEL_2);     //切换捕获极性后需重新启动
 
				hc_2_flag = 1;          	 //上升沿、下降沿捕获标志位
			}
			else if(hc_2_flag == 1)     //捕获下降沿
			{
				hc_2_FallingTime = HAL_TIM_ReadCapturedValue(&htim9, TIM_CHANNEL_2);                       //获取下降沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim9, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);        //切换捕获极性
				HAL_TIM_IC_Start_IT(&htim9, TIM_CHANNEL_2);   	 //切换捕获极性后需重新启动

				hc_2_HighTime = hc_2_FallingTime < hc_2_RisingTime ? hc_2_FallingTime + 0xffff - hc_2_RisingTime + 1 : hc_2_FallingTime - hc_2_RisingTime;
				//高电平持续时间 = 下降沿时间点 - 上升沿时间点
				dis_2 = hc_2_HighTime * 17 / 100; //计算超声波测量距离

				//i++;//累加计数
				hc_2_flag = 0;		  			 //一次采集完毕，清零
				dis_2=KalmanFilter(dis_2);
				if(dis_2>=800)dis_2=800;
			}
		}
	}
	
	if(htim->Instance == htim12.Instance)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(hc_3_flag == 0)          //捕获上升沿
			{
				hc_3_RisingTime = HAL_TIM_ReadCapturedValue(&htim12, TIM_CHANNEL_1);                         //获取上升沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim12, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);        //切换捕获极性
				HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_1);     //切换捕获极性后需重新启动
 
				hc_3_flag = 1;          	 //上升沿、下降沿捕获标志位
			}
			else if(hc_3_flag == 1)     //捕获下降沿
			{
				hc_3_FallingTime = HAL_TIM_ReadCapturedValue(&htim12, TIM_CHANNEL_1);                       //获取下降沿时间点
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim12, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);        //切换捕获极性
				HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_1);   	 //切换捕获极性后需重新启动

				hc_3_HighTime = hc_3_FallingTime < hc_3_RisingTime ? hc_3_FallingTime + 0xffff - hc_3_RisingTime + 1 : hc_3_FallingTime - hc_3_RisingTime;
				//高电平持续时间 = 下降沿时间点 - 上升沿时间点
				dis_3 = hc_3_HighTime * 17 / 100; //计算超声波测量距离
				dis_3+=60;
				//i++;//累加计数
				hc_3_flag = 0;		  			 //一次采集完毕，清零
				dis_3=KalmanFilter(dis_3);
				if(dis_3>=800)dis_3=800;
			}
		}
	}
	
//			ANODT_SendF4(dis_1,dis_2,dis_3,0);
}
