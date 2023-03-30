#include "section_length.h"

//! 現在の区間長
float section_length_left, section_length_right;
//! 区間開始点の世界長
float section_length_buffer_global_left, section_length_buffer_global_right;
//! update 周期
float samplingtime_s;

//! update 周期を設定する
void section_length_set_sampling_time_ms(unsigned short int samplingtime_ms)
{
    samplingtime_s = samplingtime_ms / (float) 1000;
}

void section_length_init(unsigned short int samplingtime_ms)
{
    section_length_set_sampling_time_ms(samplingtime_ms);
}

void section_length_start()
{
    section_length_reset();
    section_length_buffer_reset();
    length_start();
}

void section_length_stop()
{
    length_stop();
}

void section_length_fin()
{
    length_fin();
}

void section_length_reset()
{
    section_length_right = 0;
    section_length_left = 0;
}

void section_length_buffer_reset()
{
    section_length_buffer_global_left = 0;
    section_length_buffer_global_right = 0;
}

//! 現在点区間長を返す
float section_length_read()
{
    return (section_length_read_left() + section_length_read_right()) / 2;
}

float section_length_read_left()
{
    return section_length_left;
}

float section_length_read_right()
{
    return section_length_right;
}

/**
 * @brief 
 * void timer()
 * {
 *      //! 区間開始点から現在点までの区間長を計算する
 *      section_length_update();
 * }
 * float calc_radius()
 * {
 *      ...
 *      //! 区間開始点から現在点までの区間長を取得する
 *      section_length = section_length_read();
 *      //! 区間開始点を現在点までの世界長に設定し、値の初期化もする
 *      section_length_set_buffer();
 * }
 * 
 */
//! 区間開始点を現在点の世界長にする
void section_length_set_buffer()
{
    section_length_buffer_global_left = length_read_left();
    section_length_buffer_global_right = length_read_right();
}

void section_length_update()
{
    //! 区間開始点から現在点の区間長を計算
    section_length_left = length_read_left() - section_length_buffer_global_left;
    section_length_right = length_read_right() - section_length_buffer_global_right;
}

void section_length_d_print()
{
    #if D_SECTION_LENGTH
    printf("section_length = %10.2f\r\n", section_length_read());
    #endif
}
