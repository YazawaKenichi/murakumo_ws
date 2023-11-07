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

#include "analog.h"
#include "encoder.h"
#include "tracer.h"
#include "velotrace.h"
#include "motor.h"

//! ロギング距離 [ m ]
#define SAMPLING_THRESHOLD 0.01f

void explore_init();
void explore_start();
void explore_main();
void explore_stop();
void explore_fin();

void explore_logging();

#endif
