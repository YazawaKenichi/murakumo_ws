/**
 * @file kcm_controller.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-11
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "motor.h"
#include "geometry.h"
#include "localization.h"
#include "twistlist.h"

#define K_x 1
#define K_y 1
#define K_theta 1
#define LOCOMOTION_SAMPLING_TIME 0.001f // [ ms ]

#define LOCOMOTION_TEST 1

Twist kcm_sample();
Twist kcm_main_function(Pose, Twist);
void kcm_reset();
Pose pose_error(Pose, Pose);
void pose_adder(Pose *, float, float);
void velocity_to_compare(MotorController *, Twist);
