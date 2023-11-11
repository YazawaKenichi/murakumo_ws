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

uint8_t shortcut_sampling_time_ms;
uint8_t shortcut_count;

void shortcut_init(uint8_t _sampling_time_ms)
{
    shortcut_sampling_time_ms = _sampling_time_ms;
    flash_init();
    locomotion_init(shortcut_sampling_time_ms);
}

void shortcut_start()
{
    shortcut_count = 0;
    printf("----- Debug Line 01 -----\r\n");
    smoothing(imudata.yaw, COURSE_STATE_SIZE, ADJACENT);
    printf("----- Debug Line 02 -----\r\n");
    smoothing(encoderdata.left, COURSE_STATE_SIZE, ADJACENT);
    printf("----- Debug Line 03 -----\r\n");
    smoothing(encoderdata.right, COURSE_STATE_SIZE, ADJACENT);
    printf("----- Debug Line 04 -----\r\n");
    locomotion_start();
    printf("----- Debug Line 05 -----\r\n");
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
    if(shortcut_count * (0.001f * shortcut_sampling_time_ms) >= COURSE_SAMPLING_TIME)
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
    uint16_t index;
    index = course_read_state_index();
    float _left = encoderdata.left[index];
    float _right = encoderdata.right[index];
    float _v = (_left + _right) / 2;
    float _w = imudata.yaw[index];
    *v = _v;
    *w = _w;
}

void shortcut_d_print()
{
}
