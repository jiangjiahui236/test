/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "NiMing_UpperConputer.h"
#include "stdio.h"
#include "mpu9250.h"
#include "hc_sr04.h"
#include "encoder.h"
#include "motor.h"
#include "pid.h"
#include "control.h"
#include "string.h"

uint8_t Rx_String_1[100];    //接收字符串数组
uint8_t Rx_Flag_1=0;         //接收字符串计数uint8_t Rx_Flag_4=0;         //接收字符串计数
uint8_t Rx_buff_1;           //接收缓存
int OpenMV_data_0,OpenMV_data_1,OpenMV_data_2;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int set_basic_speek;
volatile int step=0;//步骤
int cnt=0;
int i=0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM9_Init();
  MX_TIM12_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */

HcSr04_TIM_start();
MPU_Init();
HAL_Delay(3000);
Encoder_Init();
motor_Init();
PID_Init();
HAL_GPIO_WritePin(IR_1_GPIO_Port, IR_1_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(IR_2_GPIO_Port, IR_2_Pin,GPIO_PIN_RESET);

HAL_UART_Receive_IT(&huart3, (uint8_t *)&Rx_buff_1, 1);   //开启接收中断


HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);	
HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);	


HAL_Delay(1000);
start_flag=1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


dis_target=1800;
keep_dis_1_flag=1;
yaw_set=yaw;
keep_yaw_flag=1;
//move_flag=1;




  while (1)
  {
		cnt++;
		HAL_Delay (3000);
		set_servo_1(60);
		HAL_Delay (3000);
		set_servo_1(120);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


  }
  /* USER CODE END 3 */
	
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */







void set_servo_1(int vel)
{
	int pwm;
	pwm = vel/0.9+50;
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, pwm);
}

void set_servo_2(int vel)
{
	int pwm;
	pwm = vel/0.9+50;
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, pwm);
}












void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)                                          //中断回调函数
{	
		/*
		摄像头回传数据：x，y，0X0A
	*/		
		
		if(huart == &huart3)
		{
			Rx_String_1[Rx_Flag_1++] = Rx_buff_1;  //接收字符
			if(Rx_String_1[Rx_Flag_1-1] == 0x0A) //判断是否接收结束
			{
				OpenMV_data_0 = Rx_String_1[0];
				OpenMV_data_1 = Rx_String_1[1]-80;
				OpenMV_data_2 = Rx_String_1[2]-60;				
				memset(Rx_String_1,0x00,sizeof(Rx_buff_1)); //清空接收字符串
				Rx_Flag_1 = 0; //清空计数器
			}
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&Rx_buff_1, 1);   //再开启接收中断
		}
		
		}
	

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
