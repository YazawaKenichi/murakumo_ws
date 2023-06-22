/**
 * @file geometry.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-01-10
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "geometry.h"

/**
 * @brief 
 * 
 * @param v1 足される値
 * @param v2 足す値
 * @return Vector3 v1 + v2 の値
 * 
 */
Vector3 vector3_adder(Vector3 v1, Vector3 v2)
{
    Vector3 vector_sum;

    vector_sum.x = v1.x + v2.x;
    vector_sum.y = v1.y + v2.y;
    vector_sum.z = v1.z + v2.z;

    return vector_sum;
}

Vector3 vector3_creation(float x, float y, float z)
{
    Vector3 new;
    new.x = x;
    new.y = y;
    new.z = z;
    return new;
}

Point point_creation(float x, float y, float z)
{
    Point new;
    new.x = x;
    new.y = y;
    new.z = z;
    return new;
}

Rpy rpy_creation(float rall, float pitch, float yaw)
{
    Rpy new;
    new.roll = rall;
    new.pitch = pitch;
    new.yaw = yaw;
    return new;
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