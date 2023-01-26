#ifndef __COURSE_H__
#define __COURSE_H__

#include "math.h"
#include "motor.h"
#include "encoder.h"
#include "flash.h"
#include "Rotary.h"
#include "time.h"
#include "function.h"   /// Low Pass Fileter が使いたい
#include "IMU.h"
#include "length.h"
#include "print.h"

#ifndef TREAD
#define TREAD 103
#endif

#define D_COURSE 1
#define D_COURSE_WHILE 0

void course_init(unsigned short int samplingtime_ms);
void course_start();
void course_stop();
void course_update_section_degree();
void course_set_update_section_freq_ms(unsigned short int samplingtime_ms);
double course_read_section_degree();
void course_reset_section_degree();
double course_read_curvature_radius();
uint16_t course_read_state_count();
void course_increment_state_count();
void course_calclate_radius();
void course_state_function();
void course_d_print();
uint16_t course_radius2speed(float);

#endif
