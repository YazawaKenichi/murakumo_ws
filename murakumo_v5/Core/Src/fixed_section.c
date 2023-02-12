/**
 * @file fixed_section.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 速度補正をするプログラム
 * @version 1.0
 * @date 2023-02-04
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "fixed_section.h"

/**
 * @fn
 * @brief 一定距離ごとに course_state_function() を呼び出す関数
 * @attention
 * 
 */
void fixed_section_main()
{
    float fixed_length;
    //! 現在点の区間長を取得
    fixed_length = section_length_read();
    if(fixed_length >= COURSE_SAMPLING_LENGTH)
    {
        //! 現在点の区間長が閾値を超えた時
        course_state_function();
    }
}

/**
 * @fn
 * @brief 加速度調整をする関数
 * 
 * @return float 
 * @attention
 * ( 速度 PID の目標値 ) = fixed_speed();
 * で大丈夫なはず。
 * 
 */
float fixed_speed()
{
    float section_time;
    float speed_now, speed_next;
    float accel;
    float speed_target;
    uint16_t course_state_count;

    course_state_count = course_read_state_count();
    speed_now = flashbuffer.speed[course_state_count];
    speed_next = flashbuffer.speed[course_state_count + 1];
    section_time = COURSE_SAMPLING_LENGTH / (float) (speed_next - speed_now);
    accel = (speed_next - speed_now) / section_time;
    if(accel > ACCEL_MAX)
    {
        speed_target = ACCEL_MAX * COURSE_SAMPLING_LENGTH + speed_next;
    }
    if(accel < - DEACCEL_MAX)
    {
        speed_target = - DEACCEL_MAX * COURSE_SAMPLING_LENGTH + speed_next;
    }
    else
    {
        speed_target = speed_now;
    }

    return speed_target;
}
