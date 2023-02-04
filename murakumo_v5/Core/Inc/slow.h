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

#define SLOW_LENGTH 300

#define THREE_SIGMA 0.9976f

#define SLOW_SIGMOID_X0 (SLOW_LENGTH / 2)
#define SLOW_SIGMOID_A  (13 / SLOW_LENGTH)

char slow_read_enable();
void slow_set_enable(char);
void slow_start(PID*);
void slow_stop();
float slow_sigmoid(float);
PID *slow_read_gain_values();
void slow_set_values(float);
void slow_set_give_velocity(float);
void slow_set_velocity(float);
float slow_read_velocity();
void slow_main();

#endif
