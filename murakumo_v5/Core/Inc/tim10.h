#ifndef __TIM10_H__
#define __TIM10_H__

#include "defines.h"
#include "print.h"
#include "length.h"
#include "course.h"
#include "velotrace.h"
#include "slow.h"

/* motor_free にして手押しで移動距離を測りたい場合はここを 1 にする */
#define D_TIM10 (0 + D_COURSE)

#define D_TIM10_WHILE 0

#define TIM10_Hz 0.001f

double tim10_read_length_left();
double tim10_read_length_right();
double tim10_read_length();

double tim10_read_velocity_left();
double tim10_read_velocity_right();
double tim10_read_velocity();

void tim10_init();
void tim10_start();
void tim10_stop();

void tim10_main();

void tim10_d_print();

void tim10_length_set_zero();
void tim10_velocity_set_zero();

double tim10_read_left();
double tim10_read_right();

void tim10_update_length();

#endif
