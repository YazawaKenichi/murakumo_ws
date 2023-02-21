/**
 * @file fixed_section.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-04
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#ifndef __FIXED_SECTION_H__
#define __FIXED_SECTION_H__

#include "course.h"
#include "function.h"

#define FIX_WIKI 1
#define FIX_LPF 0

//! 最大加速度
#define ACCEL_MAX_MAX 1 // [ m / s / s ]
#define ACCEL_MAX_MIN 0.5f
#define ACCEL_STEP_SIZE 16
//! 最大減速度  //! 使ってない
//! #define DEACCEL_MAX ACCEL_MAX  // [ m / s / s ]
//! 使ってない
//! #define ACCEL_LENGTH ((float) ACCEL_MAX * (float) COURSE_SAMPLING_LENGTH)

//! LPF のガンマ値
#define FIXED_SPEED_GAMMA 0.25f

void fixed_section_start();
void fixed_section_main();
float fixed_speed();

#endif
