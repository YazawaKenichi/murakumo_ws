/**
 * @file explore.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-10-27
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#ifndef __EXPLORE_H__
#define __EXPLORE_H__

#include "switch.h"
#include "encoder.h"
#include "imu.h"
#include "course.h"
#include "flash.h"
#include "linetrace.h"
#include "geometry.h"
#include "math.h"

//! ロギング距離 [ m ]
#define SAMPLING_THRESHOLD 0.01f

void explore_init(uint8_t);
void explore_start();
void explore_main();
void explore_stop();
void explore_fin();

void logging_clear();
Pose state_transition(Twist ut, float theta_before);
void explore_logging();
void logging_save();

void explore_opening();
void explore_ending();

void explore_d_print();

#endif

