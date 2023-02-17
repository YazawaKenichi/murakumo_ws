#ifndef __TIM10_H__
#define __TIM10_H__

#include "defines.h"
#include "print.h"
#include "course.h"
#include "length.h"
#include "velotrace.h"
#include "slow.h"
#include "sidesensor.h"
#include "section_length.h"

#define D_TIM10 1

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

void tim10_update_values();

#endif
