/**
 * @file shortcut.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-07
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "shortcut.h"

void shortcut_init()
{
    locomotion_init();
}

void shortcut_start()
{
    smoothing(imudata->yaw, COURSE_STATE_SIZE, ADJACENT);
    smoothing(encoderdata->left, COURSE_STATE_SIZE, ADJACENT);
    smoothing(encoderdata->right, COURSE_STATE_SIZE, ADJACENT);
    locomotion_start();
}

void shortcut_main()
{
    float v, w;
    //! 目標速度と目標角速度を取得
    shortcut_read_twist_reference(&v, &w);
    //! 速度と角速度をセット
    shortcut_set_kcm_twist_reference(v, w);
    //! セットした速度と角速度を基に KCM を実行
    locomotion_main();

    shortcut_count++;

    //! 目標速度の更新間隔
    if(shortcut_count * (0.001f * sampling_time_ms) >= COURSE_SAMPLING_TIME)
    {
        course_increment_state_index();
        shortcut_count = 0;
    }
}

void shortcut_stop()
{
    locomotion_stop();
}

void shortcut_fin()
{
}

void shortcut_set_kcm_twist_reference(float v, float w)
{
    Twist _q;

    //! ここを v とするか 1 [ m / s ] とするか悩み
    _q.linear.x = v;
    _q.linear.y = 0;
    _q.linear.z = 0;
    _q.angular.x = 0;
    _q.angular.y = 0;
    _q.angular.z = w;

    kcm_set_twist_reference(_q);
}

void shortcut_read_twist_reference(float *v, float *w)
{
    float _left = encoderdata->left[course_state_index];
    float _right = encoderdata->right[course_state_index];
    float _v = (_left + _right) / 2;
    float _w = imudata->yaw[course_state_index];
    *v = _v;
    *w = _w;
}
