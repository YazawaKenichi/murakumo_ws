/**
 * @file length.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-12
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "length.h"

float length_left, length_right;
float velocity_left, velocity_right;
float length_update_sampling_time_s;
uint8_t length_started;

void length_set_sampling_time_ms(unsigned short int samplingtime_ms)
{
    length_update_sampling_time_s = samplingtime_ms / (float) 1000;
}

void length_init(unsigned short int samplingtime_ms)
{
    length_started = 0;
    length_set_sampling_time_ms(samplingtime_ms);
    encoder_init();
}

void length_start()
{
    if(0 >= length_started)
    {
        length_reset();
        encoder_start();
    }
    length_started = 1;
}

void length_stop()
{
    encoder_stop();
    length_started = 0;
}

void length_fin()
{
    encoder_fin();
}

void length_reset()
{
    length_left = 0;
    length_right = 0;
}

float length_read()
{
    return (length_read_left() + length_read_right()) / 2;
}

float length_read_left()
{
    return length_left;
}

float length_read_right()
{
    return length_right;
}

float velocity_read()
{
    return (velocity_read_left() + velocity_read_right()) / 2;
}

float velocity_read_left()
{
    return velocity_left;
}

float velocity_read_right()
{
    return velocity_right;
}

//! エンコーダの値を読み、速度と距離を計算する
void length_update()
{
    float encoder_left, encoder_right;
    float sampling_time_s;
    sampling_time_s = length_update_sampling_time_s;
    //! エンコーダの値を読み、中央値に戻す
    encoder_set();
    encoder_left = encoder_length_left();
    encoder_right = encoder_length_right();
    velocity_left = encoder_left * sampling_time_s;
    velocity_right = encoder_right * sampling_time_s;
    length_left += velocity_left * sampling_time_s;
    length_right += velocity_right * sampling_time_s;
}

void length_d_print()
{
    #if D_LENGTH
    printf("length = %10.2f, sampling_time_s = %8.6f\r\n", length_read(), length_update_sampling_time_s);
    //! printf("velocity = %10.2f\r\n", velocity_read());
    #endif
}
