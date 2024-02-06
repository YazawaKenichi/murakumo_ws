/**
 * 
 * @file explore.c
 * 
 * SPDX-FileCopyrightText: 2023 YAZAWA Kenichi <s21c1036hn@gmail.com>
 * SPDX-License-Identifier: MIT-LICENSE
 * 
 */

#include "explore.h"

uint8_t explore_sampling_time_ms;
uint8_t logging_count;

void explore_init(uint8_t _sampling_time_ms)
{
    explore_sampling_time_ms = _sampling_time_ms;
    flash_init();
    linetrace_init(explore_sampling_time_ms);
}

void explore_start()
{
    uint16_t index;
    course_reset_state_index();
    index = course_read_state_index();
    printf("explore_start : index = %d\r\n", index);
    encoderdata.left[index] = 0;
    encoderdata.right[index] = 0;
    imudata.yaw[index] = 0;
    linetrace_start();
}

void explore_main()
{
    explore_opening();
    linetrace_main();
    explore_logging();
    explore_ending();
}

void explore_stop()
{
    linetrace_stop();
    logging_clear();
    logging_save();
}

void explore_fin()
{
    linetrace_fin();
}

void logging_clear()
{
    flash_erase(FLASH_SECTOR_9);
    flash_erase(FLASH_SECTOR_10);
}

Pose state_transition(Twist ut, float theta_bef)
{
    float vt = ut.linear.x;
    float wt = ut.angular.z;
    float dt = explore_sampling_time_ms * 0.001;
    Pose pt;
    if(wt = 0)
    {
        pt.linear.x = vt * cos(theta_bef) * dt;
        pt.linear.y = vt * sin(theta_bef) * dt;
        pt.angular.z = wt * dt;
    }
    else
    {
        pt.linear.x = vt / wt * (sin(theta_bef + wt * dt) - sin(theta_bef));
        pt.linear.y = vt / wt * (-cos(theta_bef + wt * dt) + cos(theta_bef));
        pt.angular.z = wt * dt;
    }
    return pt;
}

void explore_logging()
{
    float _left, _right;
    // float _v;
    float _w;

    //! データ取得
    _left = encoder_read_left() * 0.001;
    _right = encoder_read_right() * 0.001;
    _w = imu_read_yaw() * 0.001;
    // _v = (_left + _right) / 2;

    //! ロギング用積分
    uint16_t index;
    index = course_read_state_index();
    encoderdata.left[index] += _left;
    encoderdata.right[index] += _right;
    imudata.yaw[index] += _w;

    logging_count++;

    //! ロギング間隔
    if(logging_count * (0.001f * explore_sampling_time_ms) >= COURSE_SAMPLING_TIME)
    {
        course_increment_state_index();
        index = course_read_state_index();
        encoderdata.left[index] = 0;
        encoderdata.right[index] = 0;
        imudata.yaw[index] = 0;
        logging_count = 0;
    }
}

void logging_save()
{
    flash_write(FLASH_SECTOR_9);
    flash_write(FLASH_SECTOR_10);
}

void explore_opening()
{
    if(sidesensor_read_markerstate_volatile() == start)
    {
        course_reset_state_index();
    }
}

void explore_ending()
{
    if(sidesensor_read_markerstate() == stop)
    {
        switch_reset_enter();
    }
}

void explore_d_print()
{
    linetrace_d_print();
}

