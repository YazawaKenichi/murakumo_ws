/**
 * @file localization.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 自己位置推定に使用するセンサ値を加工して自己位置を推定する
 * @version 1.0
 * @date 2023-05-11
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "localization.h"

//! 現在位置姿勢
Pose pose_now;
//! 現在速度角速度
Twist twist_now;

Pose localization_get_pose()
{
    return pose_now;
}

/**
 * @brief 現在の（角）速度を取得する
 * 
 * @return Twist 現在の（角）速度
 */
Twist localization_get_twist()
{
    return twist_now;
}

void localization_init()
{
    pose_now.position.x = 0;
    pose_now.position.y = 0;
    pose_now.position.z = 0;
    pose_now.orientation.x = 0;
    pose_now.orientation.y = 0;
    pose_now.orientation.z = 0;
    pose_now.orientation.w = 1;
    twist_now.linear.x = 0;
    twist_now.linear.y = 0;
    twist_now.linear.z = 0;
    twist_now.angular.x = 0;
    twist_now.angular.x = 0;
    twist_now.angular.x = 0;
}

void odometry_update()
{
    float vl = length_read_left();
    float vr = length_read_right();
    float v = (vl + vr) / 2;
    float w = imu_read_yaw() * M_PI / 180;

    //! twist の更新
    twist_now.linear.x = v;
    twist_now.angular.z = w;

    //! pose の更新
    twist_add_to_pose(twist_now, &pose_now, 0.001f);
}
