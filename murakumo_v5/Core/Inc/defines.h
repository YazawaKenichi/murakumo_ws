/*
    main.h 内で stm32f4xx_hal.h の後に呼び出されるヘッダファイル

    この中で include したヘッダファイルは STM32 特有の型や変数が使用可能になる
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
#define USE_COURSE_STATE_TIME 1

#define USE_SLOWSTART 1
#define USE_WRITE_FLASH 1

// one side only
#define LENGTH_SAMPLING 1
#define LEFTMARKER_SAMPLING 0
#define SAMPLING_LENGTH 10000

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
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart6;

void Error_Handler(void);

#endif /* EXTERN */

#include "tim6.h"
#include "tim10.h"
#include "tim11.h"
#include "imu.h"

#endif
