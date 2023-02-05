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

#include "length.h"
#include "course.h"

//! 最大加速度
#define ACCEL_MAX 17 // [ m / s / s ]
//! 最大減速度
#define DEACCEL_MAX 17  // [ m / s / s ]

void fixed_section_main();
float fixed_speed();

#endif
