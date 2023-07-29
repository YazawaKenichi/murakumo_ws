#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "defines.h"
#include "print.h"
#include "stm32f4xx_hal.h"
#include "function.h"
#include "math.h"

#define D_MOTOR 0

#define PWMMAX 1000

typedef struct
{
    float left;
    float right;
} Motor;

void motor_start();
void motor_stop();
void motor_init();
void motor_enable(uint8_t enable_);
char motor_read_enable();
void motor_set(float motor_left_, float motor_right_);
void motor_d_print();

#endif

