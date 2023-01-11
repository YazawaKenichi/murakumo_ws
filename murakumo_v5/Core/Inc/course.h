#ifndef __COURSE_H__
#define __COURSE_H__

#include "motor.h"
#include "encoder.h"
#include "flash.h"
#include "Rotary.h"
#include "time.h"
#include "IMU.h"
#include "length.h"

#ifndef TREAD
#define TREAD 103
#endif

#define D_COURSE 1

void course_update_section_degree();
void course_init();
double course_read_length();
uint16_t course_read_state_time();
double course_calclate_radius();
void course_state_function();
void course_d_print();

#endif
