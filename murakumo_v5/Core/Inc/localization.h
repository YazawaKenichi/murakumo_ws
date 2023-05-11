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

#include "length.h"
#include "imu.h"
#include "geometry.h"

Pose localization_get_pose();
Twist localization_get_twist();
void localization_init();
void odometry_update();
