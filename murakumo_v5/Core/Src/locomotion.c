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


/**
 * @brief KANAYAMA CONTROL METHOD の最重要関数式
 * 
 * @param p_e 目標座標のローカル位置ベクトル (x_e, y_e) と姿勢 theta_e
 * @param q_r 目標座標における目標速度 v_r と角速度 w_r
 * @return Twist 出力すべき速度 v と角速度 w
 */
Twist kanayama_control_method(Pose p_e, Twist q_r)
{
    float v_r = q_r.linear.x;
    float theta_e = p_e.quaternion.z;
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

Pose pose_error(Pose p_c, Pose p_r)
{
    Pose p_e;
    p_e = p_c.linear.x - p_r.linear.x;
    p_e = p_c.linear.y - p_r.linear.y;
    p_e = p_c.linear.z - p_r.linear.z;
}
