#ifndef __TIM10_H__
#define __TIM10_H__

#include "defines.h"
#include "print.h"
#include "length.h"
#include "course.h"
#include "velotrace.h"
#include "slow.h"
#include "sidesensor.h"

/* motor_free にして手押しで移動距離を測りたい場合はここを 1 にする */
#define D_TIM10 0

#define D_TIM10_WHILE (0 + D_COURSE_WHILE)

#define TIM10_TIME_MS 1 //! [ms]

float tim10_read_length_left();
float tim10_read_length_right();
float tim10_read_length();

float tim10_read_velocity_left();
float tim10_read_velocity_right();
float tim10_read_velocity();

void tim10_init();
void tim10_start();
void tim10_stop();

void tim10_main();

void tim10_d_print();

void tim10_length_set_zero();
void tim10_velocity_set_zero();

float tim10_read_left();
float tim10_read_right();

void tim10_update_length();

#endif
