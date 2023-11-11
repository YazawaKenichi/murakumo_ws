/**
 * @file locomotion.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-10-27
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#ifndef __LOCOMOTION_H__
#define __LOCOMOTION_H__

#include "localization.h"
#include "kcm_controller.h"
#include "velotrace.h"
#include "angletrace.h"
#include "motor.h"
#include "geometry.h"
#include "math.h"

void locomotion_init();
void locomotion_start();
void locomotion_stop();
void locomotion_fin();
void locomotion_main();
void locomotion_d_print();

#endif
