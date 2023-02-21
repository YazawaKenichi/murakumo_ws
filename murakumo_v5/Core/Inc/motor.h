#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "defines.h"
#include "print.h"
#include "stm32f4xx_hal.h"

#define D_MOTOR 0

#define PWMMAX 1000

void motor_start();
void motor_stop();
void motor_init();
void motor_enable(uint8_t enable_);
char motor_read_enable();
void motor_set(float motor_left_, float motor_right_);

#endif

