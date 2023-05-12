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
//! サンプリング周期
float dt;

Pose localization_get_pose()
{
    return pose_now;
}

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
    dt = 1;
}

void odometry_update()
{
	float vx, vy;

    float vl = length_read_left();
    float vr = length_read_right();
    float v = (vl + vr) / 2;
    float w = imu_read_yaw() * M_PI / 180;

    float x = pose_now.position.x;
    float y = pose_now.position.y;
    float theta = pose_now.orientation.z;

    if(theta + w * dt > 2 * M_PI)
    {
        theta = theta - 2 * M_PI;
    }
    else if(theta + w * dt < - 2 * M_PI)
    {
        theta = theta + 2 * M_PI;
    }
    theta += theta + w * dt;
    vx = v * cos(theta);
    vy = v * sin(theta);
    x = x + vx * dt;
    y = y + vy * dt;

    twist_now.linear.x = v;
    twist_now.angular.z = w;

    pose_now.position.x = x;
    pose_now.position.y = y;
    pose_now.orientation.z = theta;
}
