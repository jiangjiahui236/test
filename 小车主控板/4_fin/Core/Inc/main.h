/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
void set_servo_1(int vel);
void set_servo_2(int vel);
extern int OpenMV_data_0,OpenMV_data_1,OpenMV_data_2;

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TRIG_1_Pin GPIO_PIN_3
#define TRIG_1_GPIO_Port GPIOE
#define TRIG_2_Pin GPIO_PIN_4
#define TRIG_2_GPIO_Port GPIOE
#define ECHO_1_Pin GPIO_PIN_5
#define ECHO_1_GPIO_Port GPIOE
#define ECHO_2_Pin GPIO_PIN_6
#define ECHO_2_GPIO_Port GPIOE
#define IR_1_Pin GPIO_PIN_0
#define IR_1_GPIO_Port GPIOC
#define IR_2_Pin GPIO_PIN_1
#define IR_2_GPIO_Port GPIOC
#define IR_3_Pin GPIO_PIN_2
#define IR_3_GPIO_Port GPIOC
#define IR_4_Pin GPIO_PIN_3
#define IR_4_GPIO_Port GPIOC
#define Encoder_4A_Pin GPIO_PIN_0
#define Encoder_4A_GPIO_Port GPIOA
#define Encoder_4B_Pin GPIO_PIN_1
#define Encoder_4B_GPIO_Port GPIOA
#define USART2_TX_OpenMV_Pin GPIO_PIN_2
#define USART2_TX_OpenMV_GPIO_Port GPIOA
#define USART2_RX_OpenMV_Pin GPIO_PIN_3
#define USART2_RX_OpenMV_GPIO_Port GPIOA
#define Encoder_1A_Pin GPIO_PIN_5
#define Encoder_1A_GPIO_Port GPIOA
#define Encoder_2A_Pin GPIO_PIN_6
#define Encoder_2A_GPIO_Port GPIOA
#define Encoder_2B_Pin GPIO_PIN_7
#define Encoder_2B_GPIO_Port GPIOA
#define IN_1_Pin GPIO_PIN_8
#define IN_1_GPIO_Port GPIOE
#define PWM_1_Pin GPIO_PIN_9
#define PWM_1_GPIO_Port GPIOE
#define IN_2_Pin GPIO_PIN_10
#define IN_2_GPIO_Port GPIOE
#define PWM_2_Pin GPIO_PIN_11
#define PWM_2_GPIO_Port GPIOE
#define IN_3_Pin GPIO_PIN_12
#define IN_3_GPIO_Port GPIOE
#define PWM_3_Pin GPIO_PIN_13
#define PWM_3_GPIO_Port GPIOE
#define PWM_4_Pin GPIO_PIN_14
#define PWM_4_GPIO_Port GPIOE
#define IN_4_Pin GPIO_PIN_15
#define IN_4_GPIO_Port GPIOE
#define TRIG_3_Pin GPIO_PIN_12
#define TRIG_3_GPIO_Port GPIOB
#define ECHO_3_Pin GPIO_PIN_14
#define ECHO_3_GPIO_Port GPIOB
#define USART3_TX_OpenMV_Pin GPIO_PIN_8
#define USART3_TX_OpenMV_GPIO_Port GPIOD
#define USART3_RX_OpenMV_Pin GPIO_PIN_9
#define USART3_RX_OpenMV_GPIO_Port GPIOD
#define Encoder_3A_Pin GPIO_PIN_12
#define Encoder_3A_GPIO_Port GPIOD
#define Encoder_3B_Pin GPIO_PIN_13
#define Encoder_3B_GPIO_Port GPIOD
#define Encoder_1B_Pin GPIO_PIN_3
#define Encoder_1B_GPIO_Port GPIOB
#define MPU9250_SCL_Pin GPIO_PIN_6
#define MPU9250_SCL_GPIO_Port GPIOB
#define MPU9250_SDA_Pin GPIO_PIN_7
#define MPU9250_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
