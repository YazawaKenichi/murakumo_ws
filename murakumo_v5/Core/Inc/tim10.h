#ifndef __TIM10_H__
#define __TIM10_H__

#include "print.h"
#include "encoder.h"
#include "sidesensor.h"
#include "defines.h"

#define D_TIM10 1

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

#endif
