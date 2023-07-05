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

void localization_init()
{
    localization_reset();
}

void localization_start()
{
    localization_reset();
}

void localization_stop()
{
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
    twist_add_to_pose(twist_now, &pose_now, 1.0f / (float) 1000);
}

Pose localization_read_pose()
{
    return pose_now;
}

Twist localization_read_twist()
{
    return twist_now;
}

void localization_reset()
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
    twist_now.angular.y = 0;
    twist_now.angular.z = 0;
}

/**
 * @brief 位置に速度角速度を与えて新しい位置にする
 * 
 * @param q_n 
 * @param p_n 
 */
void twist_add_to_pose(Twist q_n, Pose *p_n, float dt)
{
	float vx, vy;

    float x = p_n->position.x;
    float y = p_n->position.y;
    float theta = p_n->orientation.z;

    float v = q_n.linear.x;
    float w = q_n.angular.z;

    //! サンプリング周期 [ s ]
    // dt = 0.001f;

    if(theta + w * dt > 2 * M_PI)
    {
        theta = theta - 2 * M_PI;
    }
    else if(theta + w * dt < - 2 * M_PI)
    {
        theta = theta + 2 * M_PI;
    }

    theta += w * dt;
    vx = v * cos(theta);
    vy = v * sin(theta);
    x += vx * dt;
    y += vy * dt;

    p_n->position.x = x;
    p_n->position.y = y;
    p_n->orientation.z = theta;
}
