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
//! 目標速度角速度
Twist q_reference;

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

    //! 出力速度角速度
    Twist q;

    //! 現在位置姿勢
    Pose p_c;

    //! 現在位置姿勢と目標位置姿勢とのギャップ
    Pose p_e;

    /********** 本来 「こういう 位置姿勢・速度角速度 を描いてほしい」 の計算 **********/
    //! 目標速度・角速度の取得
    q_r = kcm_read_twist_reference();
    //! 速度 q_r で進んだ時の位置 p_reference の更新
    twist_add_to_pose(q_r, &p_reference, 0.001f);

    /********** でも 「実際はどういう 位置姿勢・速度角速度なの？」 の計算 **********/
    //! 実際のの位置を取得
    p_c = localization_read_pose();

    //! p_e に理想と現実のギャップが代入される
    p_e = pose_error(p_reference, p_c);

    /********** 「じゃあどうしたら良いの？」 の計算 **********/
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

void kcm_set_twist_reference(Twist _q)
{
    q_reference = _q;
}

Twist kcm_read_twist_reference()
{
    return q_reference;
}
