/**
 * @file linetrace.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-07
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#ifndef __LINETRACE_H__
#define __LINETRACE_H__

#include "analog.h"
#include "encoder.h"
#include "tracer.h"
#include "velotrace.h"
#include "motor.h"

void linetrace_init();
void linetrace_start();
void linetrace_main();
void linetrace_stop();
void linetrace_fin();

int linetrace_read_direction();
float linetrace_read_velocity();
void linetrace_set_gain_short();
void linetrace_set_gain_long();

#endif
