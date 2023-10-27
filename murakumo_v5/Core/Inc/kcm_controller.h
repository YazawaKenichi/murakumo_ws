/**
 * @file kcm_controller.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-11
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

//! 幾何学的・運動学的な値を扱うライブラリ
#include "geometry.h"
//! オドメトリを取得するライブラリ
#include "localization.h"

//! テスト用
#include "time.h"

//#define K 0.001f
#define K 0
#define K_x K
#define K_y K
#define K_theta K

#define DEBUG_VELOCITY 0

void kcm_init();
void kcm_start();
void kcm_stop();

Twist kcm_sample();
void kcm_reset();
Twist kcm_main_function(Pose p_e, Twist q_r);
Pose pose_error(Pose p_r, Pose p_c);

