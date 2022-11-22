#ifndef __COURSE_H__
#define __COURSE_H__

#include "motor.h"
#include "encoder.h"
#include "flash.h"
#include "tim10.h"
#include "Rotary.h"

#ifndef TREAD
#define TREAD 103
#endif

void course_init();
double course_read_length();
double course_ad_length(double length);
uint16_t course_read_state_time();
double course_calclate_radius();
void course_state_function();

#endif
