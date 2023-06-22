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

#include "locomotion.h"

//! 目標位置姿勢
Pose p_reference;

/**
 * @brief 実際に使ってみるときの関数
 * 
 * @param q_n 現在の速度・角速度
 * @param p_c 現在の位置・姿勢
 * @return Twist 出力すべき速度と加速度
 */
Twist kcm_sample(Twist q_n, Pose p_c)
{
    //! 目標速度角速度
    Twist q_r;
    //! 現在位置姿勢と目標位置姿勢とのギャップ
    Pose p_e;

    //! 現在出すべき速度角速度
    q_r = get_twistlist();
    //! 速度角速度から座標の取得
    twist_add_to_pose(q_r, &p_reference, 0.001f);

    //! p_r には現在いるべき目標座標が入る
    p_e = pose_error(p_reference, p_c);
    return kcm_main_function(p_e, q_r);
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

/**
 * @brief 現在座標を更新する関数
 * @attention 結局使ってない（ localization.c でやってる ）
 * 
 * @param p_n 前回サンプリングした位置姿勢
 * @param v_c 
 * @param w_c 
 */
void pose_adder(Pose *p_n, float v_c, float w_c)
{
    float dt;
    float x_n, y_n;
    float theta_n;

    dt = 1 / (float) 1000;	// [ s ]

    //! 前回計算したときのグローバル位置
    x_n = p_n -> position.x;
    y_n = p_n -> position.y;
    //! 現在のグローバル姿勢
    p_n -> orientation.z += w_c * dt;
    theta_n = p_n -> orientation.z;

    //! (x_n, y_n) はグローバル座標であることに注意
    x_n += v_c * cos(theta_n) * dt;
    y_n += v_c * sin(theta_n) * dt;

    //! 現在位置の更新
    p_n -> position.x = x_n;
    p_n -> position.y = y_n;
}

