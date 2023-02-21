/**
 * @file defines.h
 * @author YAZAWA Kenichi (21C1036hn@gmail.com)
 * @brief 機能の使用決定をする
 * @version 0.1
 * @date 2023-01-08
 * 
 * @copyright Copyright (c) 2023 YAZAWA Kenichi
 * 
 * 多くの extern 変数や Error_Handler() を利用できるようにする
 * 複数の機能をスイッチングする
 * 
 */
#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "stm32f4xx_hal.h"

#define PLAY 1

#define USE_ANALOG 1
#define USE_MOTOR 1
#define USE_SIDESENSOR 1	// Use SideSensor
#define USE_ENCODER 1
#define USE_ROTARY 1
#define USE_SWITCH 1
#define USE_LED 1
#define USE_FLASH 1
#define USE_IMU 1
#define USE_BUZZER 0
#define USE_VELOCITY_CONTROL 1
#define USE_SIGMOID_TRACE 0
#define USE_DANGERSTOP 0
#define USE_LR_DIFFERENCE 1
#define USE_PID_ARRAY 1

#define USE_SLOWSTART 0
#define USE_WRITE_FLASH 1

/* 片方だけ選択 */
/* 長さでコース記憶 */
#define LENGTH_SAMPLING 0
/* 左マーカ */
#define LEFTMARKER_SAMPLING 1

/* main.h で再び宣言されるのを防ぐ */
#define EXTERN
#ifdef EXTERN

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

void Error_Handler(void);

#endif /* EXTERN */

#endif
