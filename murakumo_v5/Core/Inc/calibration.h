/**
 * 
 * @file calibration.h
 * 
 * SPDX-FileCopyrightText: 2023 YAZAWA Kenichi <s21c1036hn@gmail.com>
 * SPDX-License-Identifier: MIT-LICENSE
 * 
 */

#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

#include "switch.h"
#include "analog.h"

void calibration_init();
void calibration_start();
void calibration_main();
void calibration_stop();
void calibration_fin();
void calibration_d_print();

#endif

