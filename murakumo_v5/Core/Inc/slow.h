/**
 * @file slow.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-08
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
*/
#ifndef __SLOW_H__
#define __SLOW_H__

#include "pid.h"
#include "function.h"
#include "length.h"
#include "sidesensor.h"
#include "velotrace.h"
#include "tracer.h"

#define D_SLOW 1

#define SLOW_LENGTH 300

#define SLOW_VELOTRACE_TARGET 0.3   //! [ m / s ]
#define SLOW_TRACE_KP 3
#define SLOW_TRACE_KI 0
#define SLOW_TRACE_KD 0.5f

#define THREE_SIGMA 0.9976f

#define SLOW_SIGMOID_X0 (SLOW_LENGTH / 2)
#define SLOW_SIGMOID_A  (13 / SLOW_LENGTH)

void slow_init();
void slow_start();
void slow_stop();
void slow_fin();

void slow_main();

uint8_t slow_read_enable();
float slow_read_velocity();
PID *slow_read_gain_values();

void slow_set_enable(uint8_t);
void slow_set_values(PID*);
void slow_set_velocity(float);

float slow_sigmoid(float);

void slow_print_default_pid();

#endif
