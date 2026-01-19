#include "motor.h"//使用说明：motor_Init进行初始化，set_motor_pwm设定电机速度（滴答定时器中），pwm最大值为1000，当空载pwm为900时encoder为33，当空载pwm为300时encoder为10
/*轮1234对于PCB丝印2143
2  4
1  3
*/

int set_pwm[4]={0,0,0,0};
int zero_pwm[4]={0,0,0,0};
void motor_Init(void)
{
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
		HAL_GPIO_WritePin(IN_1_GPIO_Port, IN_1_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,0);
		HAL_GPIO_WritePin(IN_2_GPIO_Port, IN_2_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,0);
		HAL_GPIO_WritePin(IN_3_GPIO_Port, IN_3_Pin, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4,1000); 
		HAL_GPIO_WritePin(IN_4_GPIO_Port, IN_4_Pin, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3,1000); 
}

void set_motor_pwm(int set_pwm[4])//根据实际运动方向取负
{
	Limit_max(set_pwm[0],600);
	Limit_max(set_pwm[1],600);
	Limit_max(set_pwm[2],600);
	Limit_max(set_pwm[3],600);
	if(set_pwm[0]>=0){
		HAL_GPIO_WritePin(IN_2_GPIO_Port, IN_2_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,set_pwm[0]); 
	}
	else{
	HAL_GPIO_WritePin(IN_2_GPIO_Port, IN_2_Pin, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,1000+set_pwm[0]); 
	}

	if(set_pwm[1]>=0){
		HAL_GPIO_WritePin(IN_1_GPIO_Port, IN_1_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,set_pwm[1]); 
	}
	else{
	HAL_GPIO_WritePin(IN_1_GPIO_Port, IN_1_Pin, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,1000+set_pwm[1]); 
	}
	
	if(set_pwm[2]>=0){
		HAL_GPIO_WritePin(IN_4_GPIO_Port, IN_4_Pin, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4,1000-set_pwm[2]); 
	}
	else{
	  HAL_GPIO_WritePin(IN_4_GPIO_Port, IN_4_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4,-set_pwm[2]); 
	}
	
	if(set_pwm[3]>=0){
		HAL_GPIO_WritePin(IN_3_GPIO_Port, IN_3_Pin, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3,1000-set_pwm[3]); 
	}
	else{
	  HAL_GPIO_WritePin(IN_3_GPIO_Port, IN_3_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3,-set_pwm[3]); 
	}
	
}
