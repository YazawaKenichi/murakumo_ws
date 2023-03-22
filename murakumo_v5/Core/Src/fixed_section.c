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

//! 使ってないから切って良い
#ifdef USE_FIXED_SPEED
/**
 * @fn
 * @brief 加速度調整をする関数
 * 
 * @return float 
 * @attention
 * ( 速度 PID の目標値 ) = fixed_speed();
 * で大丈夫なはず。
 * 
 * course_state_count がインクリメントされる前に呼び出されている
 * そのため現在の速度は coursedata.radius[course_state_count] で、
 * 今から coursedata.radius[course_state_count + 1] に変更する必要がある
 * 
 */
float fixed_speed()
{
    float speed_now, speed_next;
    float speed_target;
    uint16_t course_state_count;
	float accel_length;
	accel_length = COURSE_SAMPLING_LENGTH * (float) (ACCEL_MAX_MAX + ACCEL_MAX_MIN) / (float) 2;

    /* この関数は course_state_count がインクリメントされる前に呼び出されていることに注意 */
    course_state_count = course_read_state_count();
    speed_next = coursedata.speed[course_state_count + 1];
#if FIX_LPF
    /* LPF 通してみる */
    speed_now = coursedata.speed[course_state_count];
    //! v2 の設定
    speed_next = low_pass_filter(speed_next, speed_now, 0.5f);
#endif
    //! v1 の設定
    speed_now = fixed_section_speed_now;
    if(accel_length >= pow(speed_next - speed_now, 2))
    {
        speed_target = speed_next;
    }
    else
    {
        /* 俺のやり方（これが wiki のやり方と一致しているのかしてないのかよくわからない） */
#if FIX_WIKI
        if(speed_next >= speed_now)
        {
            speed_target = sqrt(accel_length) + speed_now;
        }
        else
        {
            speed_target = speed_now - sqrt(accel_length);
        }
#endif
    }

    /* 今回指定された目標値を現在の速度値として記憶させる */
    fixed_section_speed_now = speed_target;

    return speed_target;
}

#endif
