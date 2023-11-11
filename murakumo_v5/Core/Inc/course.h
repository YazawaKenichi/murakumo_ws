/**
 * 
 * @file course.h
 * 
 * SPDX-FileCopyrightText: 2023 YAZAWA Kenichi <s21c1036hn@gmail.com>
 * SPDX-License-Identifier: MIT-LICENSE
 * 
 */

#ifndef __COURSE_H__
#define __COURSE_H__

#include "flash.h"

/* ( コース全長 [ m ] ) / ( コースデータ量 [ 個 ] ) / ( 探索した時の直進速度 [ m / s ] ) */
#define COURSE_SAMPLING_TIME (60.0f / 60000.0f / 1.0f)     //! [ s / 個 ] < 0.256

void course_increment_state_index();

uint16_t course_state_index;

#endif
