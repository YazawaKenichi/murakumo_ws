#ifndef __SLOW_H__
#define __SLOW_H__

#include "pid.h"
#include "function.h"

#define SLOW_LENGTH 300

#define THREE_SIGMA 0.9976f

#define SLOW_SIGMOID_X0 (SLOW_LENGTH / 2)
#define SLOW_SIGMOID_A  (13 / SLOW_LENGTH)

char slow_read_enable();
void slow_set_enable(char);
void slow_start(PID*);
void slow_stop();
double slow_sigmoid(double);
PID *slow_read_gain_values();
void slow_set_values(double);
void slow_set_give_velocity(double);
void slow_set_velocity(double);
double slow_read_velocity();
void slow_main();

#endif
