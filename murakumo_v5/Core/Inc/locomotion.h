/**
 * @file locomotion.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-11
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */


#ifndef __LOCOMOTION_H__
#define __LOCOMOTION_H__

#include "geometry.h"
#include "twistlist.h"
#include "localization.h"

#define K_x 1
#define K_y 1
#define K_theta 1

#define LOCOMOTION_TEST 1

Twist kcm_sample(Twist, Pose);
Twist kcm_main_function(Pose, Twist);
Pose pose_error(Pose, Pose);
void pose_adder(Pose *, float, float);

#endif
