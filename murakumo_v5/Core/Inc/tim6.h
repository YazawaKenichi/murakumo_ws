/**
 * @file tim6.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-08
 * 
 * @copyright Copyright (c) 2023 YAZAWA Kenichi
 * 
 */

#ifndef __TIM6_H__
#define __TIM6_H__

#include "print.h"
#include "motor.h"
#include "defines.h"
#include "Rotary.h"
#include "tim7.h"
#include "tim10.h"
#include "course.h"
#include "fixed_section.h"
#include "flash.h"

#define D_TIM6 0

#define D_TIM6_WHILE (0 + D_MOTOR_WHILE + D_TIM7_WHILE + D_TIM10_WHILE + D_COURSE_WHILE)
#define D_TIM6_EXCLUSION 1
#define D_TIM6_IGNORE 0

#if D_TIM6_IGNORE
#define TRACER_TUNING 1
#define VELOTRACE_TUNING 1
#endif

#define CURVE_MARGIN 1
//! 減速位置    //! LEFT_MARKER_RADIUS が有効の時のみ使用可能
#define CURVE_MARGIN_LENGTH 0.125 // [ m ]
#define CURVE_MARGIN_THRESHOLD 700

#define TEMPORARY 0

#define TIM6_EMERGENCY_STOP 0

void tim6_init();
void tim6_start();
void tim6_stop();
void tim6_main();

void tim6_d_print();

#endif
