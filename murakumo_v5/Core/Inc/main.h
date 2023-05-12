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

#define __VERSION__ 2.0

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "defines.h"
#include "LED.h"
#include "print.h"
#include "Switch.h"
#include "Rotary.h"
#include "analog.h"
#include "flash.h"
#include "tim6.h"
#include "tim7.h"
#include "tim10.h"
#include "tim11.h"
#include "revision.h"
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
#ifndef __DEFINES_H__
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern I2C_HandleTypeDef hi2c1;

extern SPI_HandleTypeDef hspi2;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim14;

extern UART_HandleTypeDef huart6;
#endif /* __DEFINES_H__ */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DRV2_PH_Pin GPIO_PIN_13
#define DRV2_PH_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_14
#define SW1_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_15
#define SW2_GPIO_Port GPIOC
#define SubSens1_Pin GPIO_PIN_2
#define SubSens1_GPIO_Port GPIOB
#define SubSens2_Pin GPIO_PIN_11
#define SubSens2_GPIO_Port GPIOB
#define SPI2_nCS_Pin GPIO_PIN_12
#define SPI2_nCS_GPIO_Port GPIOB
#define LED_Red_Pin GPIO_PIN_13
#define LED_Red_GPIO_Port GPIOB
#define LED_White_Pin GPIO_PIN_8
#define LED_White_GPIO_Port GPIOC
#define LED_B_Pin GPIO_PIN_9
#define LED_B_GPIO_Port GPIOC
#define Encoder1_A_Pin GPIO_PIN_8
#define Encoder1_A_GPIO_Port GPIOA
#define Encoder1_B_Pin GPIO_PIN_9
#define Encoder1_B_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_10
#define LED_G_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_11
#define LED_R_GPIO_Port GPIOA
#define Rotary4_Pin GPIO_PIN_12
#define Rotary4_GPIO_Port GPIOA
#define Rotary2_Pin GPIO_PIN_10
#define Rotary2_GPIO_Port GPIOC
#define Rotary8_Pin GPIO_PIN_11
#define Rotary8_GPIO_Port GPIOC
#define Rotary1_Pin GPIO_PIN_12
#define Rotary1_GPIO_Port GPIOC
#define DRV1_PH_Pin GPIO_PIN_2
#define DRV1_PH_GPIO_Port GPIOD
#define Encoder2_A_Pin GPIO_PIN_4
#define Encoder2_A_GPIO_Port GPIOB
#define Encoder2_B_Pin GPIO_PIN_5
#define Encoder2_B_GPIO_Port GPIOB
#define DRV1_EN_Pin GPIO_PIN_6
#define DRV1_EN_GPIO_Port GPIOB
#define DRV2_EN_Pin GPIO_PIN_7
#define DRV2_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

void main_init();
void running_start();
void running_stop();
void main_main();
void main_print_while();
void main_d_print();

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
