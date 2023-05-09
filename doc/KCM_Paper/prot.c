/**
 * @file prot.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief This is a prototype coding of KANAYAMA CONTROL METHOD Algorithm.
 * @version 1.0
 * @date 2023-04-26
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

/// 入力 ///
//! 一走目保存データ
encl[] = 左エンコーダ
encr[] = 右エンコーダ
yaw[] = IMU の Yaw 角
i = 現在の区間番号
dt = i-1 -> i になるまでにかかった時間
//! 二走目中センサの値
encl_now = 左エンコーダ（現在）
encr_now = 右エンコーダ（現在）
onega_now = IMU の Yaw 角（現在）
//! 時間やインデックス
Dt = 前回計算してから今回までの時間

/// システム ///
//! 角度誤差
theta_c += omega_now;
theta_r += yaw[i];
theta_e = theta_c - theta_r;
theta_c_bef = theta_c;
theta_r_bef = theta_r;

//! 速度情報
v_c = (encl_now + encr_now) / 2;
v_r = (encl[i] + encr[i]) / 2;

//! x 座標誤差
x_c += v_c * cos(theta_c) * Dt;
x_r += v_r * cos(yaw[i]) * dt;
x_e = x_c - x_r;

//! y 座標誤差
y_c += v_c * sin(theta_c) * Dt;
y_r += v_r * sin(yaw[i]) * dt;
y_e = x_c - x_r;

/// 出力 ///
//! ゲイン（定数）
K_x = x 軸方向（ P_e にかけるので前後方向 ）のゲイン値
K_y = y 軸方向（ P_e にかけるので左右方向 ）のゲイン値
K_theta = ヨー角方向（ P_e にかけるので現在の車体方向基準 ）のゲイン値

v_out = v_r * cos(theta_e) + K_x * x_e;
omega_out = omega_r + v_r * (K_y * y_e + K_theta * sin(theta_e));








