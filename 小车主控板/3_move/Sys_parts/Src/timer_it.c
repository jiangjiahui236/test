#include "timer_it.h" 
 
uint16_t psc = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim)
{
	if(htim == &htim6)
	{
		psc++;
		if(psc %5 == 0)
		{
//			IR_Scan();
		}
		if(psc%10 == 0)
		{
//			Car_Plant();//记得修改Flag为3
			GetSpeed();
//			IR_Scan();
//			Car_Plant();
//			Car_Go_Plant(0);
			Car_Turn(0);
//			Car_Stop();
//			Path_All_Deal();
//			Path_Plan_Finish();
//			Go_Line(0,2,0);
//			Motot_Set();
//			Speed_Set();
//			Planning_Path();
		}
		if(psc == 1000)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			psc = 0;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin & GPIO_PIN_0)
	{
		get_imu_data();
	}
}

