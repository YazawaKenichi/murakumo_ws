/**
 * @file locomotion.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-10-27
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

void locomotion_init()
{
    localization_init();
    kcm_init();
    velotrace_init(1);
    angletrace_init();
}

void locomotion_start()
{
    localization_start();
    kcm_start();
    velotrace_start();
    angletrace_start();
    motor_start();
}

void locomotion_stop()
{
    motor_stop();
    localization_stop();
    kcm_stop();
    velotrace_stop();
    angletrace_stop();
}

void locomotion_fin()
{
}

/**
 * @brief KCM にしたがってモータ制御を行う
 * 
 */
void locomotion_main()
{
	Twist q_n, q_o;
	float v, w, vel, ang, left, right;
	float enc;

	//! 現在の位置を更新
	odometry_update();
	//! 現在の位置を取得
	q_n = localization_read_twist();
	//! 現在の位置から出すべき（角）速度を求める
	q_o = kcm_sample(q_n);

	//! 出力すべき（角）速度
	v = q_o.linear.x;	//! [ m / s ]
	w = q_o.angular.z;	//! [ rad / s ]

	//! （角）速度の PID 目標値を変更する
	velotrace_set_target_direct(v);
	angletrace_set_target_direct(w);

	//! PID 指令値の計算
	enc = encoder_read();
	vel = velotrace_solve(enc);
	ang = angletrace_solve(imu_read_yaw() * M_PI / 180);

	//! 指令値の重ね合わせ
	left = vel  - ang;
	right = vel + ang;

	//! モータ出力
	motor_set(left, right);
}

void locomotion_d_print()
{
    motor_d_print();
    encoder_d_print();
    localization_d_print();
    velotrace_d_print();
    angletrace_d_print();
}

