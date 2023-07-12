/**
 * @file locomotion.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief KANAYAMA Control Method
 * @version 1.0
 * @date 2023-05-09
 *
 * Copyright 2023 YAZAWA Kenichi
 *
 */

#include "kcm_controller.h"

//! 目標位置姿勢
Pose p_reference;

void kcm_init()
{
    kcm_reset();
}

void kcm_start()
{
    kcm_reset();
}

void kcm_stop()
{
}

/**
 * @brief 実際に使ってみるときの関数
 *
 * @param q_n 現在の速度・角速度
 */
Twist kcm_sample()
{
    //! 目標速度角速度
    Twist q_r;
    q_r.linear.x = DEBUG_VELOCITY;
    q_r.linear.y = 0;
    q_r.linear.z = 0;
    q_r.angular.x = 0;
    q_r.angular.y = 0;
    q_r.angular.z = 0;

    //! 出力速度角速度
    Twist q;

    //! 現在位置姿勢
    Pose p_c;

    //! 現在位置姿勢と目標位置姿勢とのギャップ
    Pose p_e;
    //! 実際に出してほしい速度と角速度
    if (time_read() > 10)
    {
        q_r.linear.x = 0;
    }

    //! 現在の位置を取得
    p_c = localization_read_pose();

    //! 現在出すべき速度角速度
    /* 出すべき（角）速度をどうにかして与える */
    //! q_r = {1, 0, 0, 0, 0, 0};
    //! 速度角速度から現在いるべき座標の取得
    twist_add_to_pose(q_r, &p_reference, 0.001f);

    //! p_r には現在いるべき目標座標が入る
    p_e = pose_error(p_reference, p_c);
    //! 出力するべき（角）速度
    q = kcm_main_function(p_e, q_r);

    return q;
}

void kcm_reset()
{
    p_reference.position.x = 0;
    p_reference.position.y = 0;
    p_reference.position.z = 0;
    p_reference.orientation.x = 0;
    p_reference.orientation.y = 0;
    p_reference.orientation.z = 0;
    p_reference.orientation.w = 1;
}

/* Private */
/**
 * @brief KANAYAMA CONTROL METHOD の最重要関数式
 *
 * @param p_e 目標座標のローカル位置ベクトル (x_e, y_e) と姿勢 theta_e
 * @param q_r 目標座標における目標速度 v_r と角速度 w_r
 * @return Twist 出力すべき速度 v と角速度 w
 */
Twist kcm_main_function(Pose p_e, Twist q_r)
{
    float v_r = q_r.linear.x;
    float theta_e = p_e.orientation.z;
    float x_e = p_e.position.x;
    float w_r = q_r.angular.z;
    float y_e = p_e.position.y;

    //! solution
    float v, w;
    Twist q;

    v = v_r * cos(theta_e) + K_x * x_e;
    w = w_r + v_r * (K_y * y_e + K_theta * sin(theta_e));

    q.linear.x = v;
    q.angular.z = w;

    return q;
}

/**
 * @brief 目標座標と現在座標とのギャップを計算する関数
 *
 * @param p_r 目標座標
 * @param p_c 現在座標
 * @return Pose ギャップ
 */
Pose pose_error(Pose p_r, Pose p_c)
{
    Pose p_e;
    p_e.position.x = p_r.position.x - p_c.position.x;
    p_e.position.y = p_r.position.y - p_c.position.y;
    p_e.orientation.z = p_r.orientation.z - p_c.orientation.z;
    return p_e;
}
