/**
 * @file localization.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 自己位置推定するのに使うセンサの値を加工して自己位置に変換する
 * @version 1.0
 * @date 2023-05-11
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "math.h"
#include "imu.h"
#include "encoder.h"
#include "geometry.h"

void localization_init();
void localization_start();
void localization_stop();

void odometry_update();

Pose localization_read_pose();
Twist localization_read_twist();

void localization_reset();

void twist_add_to_pose(Twist, Pose *, float);
