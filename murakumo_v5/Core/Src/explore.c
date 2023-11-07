/**
 * @file explore.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-10-30
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "explore.h"

uint16_t course_state_index;

void explore_init();
{
    flash_init();
    linetrace_init();
}

void explore_start()
{
    course_state_index = 0;
    encoder_data->left[course_state_index] = 0;
    encoder_data->right[course_state_index] = 0;
    imudata->yaw[course_state_index] = 0;
    linetrace_start();
}

void explore_main()
{
    linetrace_main();
    explore_logging();
}

void explore_stop()
{
    logging_clear();
    logging_save();
    linetrace_stop();
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

void explore_logging()
{
    float _left, _right, _v, _w;

    //! データ取得
    _left = encoder_read_left() * 0.001;
    _right = encoder_read_right() * 0.001;
    _w = imu_read_yaw() * 0.001;
    _v = (_left + _right) / 2;

    //! ロギング用積分
    encoderdata -> left[course_state_index] += _left;
    encoderdata -> right[course_state_index] += _right;
    imudata -> yaw[course_state_index] += _w;

    //! ロギング距離
    if(_v >= SAMPLING_THRESHOLD)
    {
        increment_course_state_index();
        encoder_data->left[course_state_index] = 0;
        encoder_data->right[course_state_index] = 0;
        imudata->yaw[course_state_index] = 0;
    }
}

void logging_save()
{
    flash_write(FLASH_SECTOR_9);
    flash_write(FLASH_SECTOR_10);
}

void increment_course_state_index()
{
    course_state_index++;
    if(course_state_index >= COURSE_STATE_SIZE - 1)
    {
        course_state_index = COURSE_STATE_SIZE - 1;
    }
}
