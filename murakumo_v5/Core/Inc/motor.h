#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "print.h"
#include "defines.h"
#include "stm32f4xx_hal_tim.h"

#define D_MOTOR 0

#define PWMMAX 1000

void motor_start();
void motor_stop();
void motor_init();
void motor_enable(uint8_t enable_);
char motor_read_enable();
void motor_set(double motor_left_, double motor_right_);

#endif

