#include "length.h"

double length_left, length_right;
double velocity_left, velocity_right;
double length_update_sampling_time_s;

void length_set_sampling_time_ms(unsigned short int samplingtime_ms)
{
    length_update_sampling_time_s = samplingtime_ms / (double) 1000;
}

void length_init(unsigned short int samplingtime_ms)
{
    length_set_sampling_time_ms(samplingtime_ms);
    encoder_init();
}

void length_start()
{
    length_left = 0;
    length_right = 0;
    velocity_left = 0;
    velocity_right = 0;
    encoder_start();
}

void length_stop()
{
    encoder_stop();
}

void length_fin()
{
    encoder_fin();
}

//! course_state_function() を呼び出すたびに length_reset() する
void length_reset()
{
    length_left = 0;
    length_right = 0;
}

//! 中央の長さを取る
double length_read()
{
    return (length_left + length_right) / 2;
}

double length_read_left()
{
    return length_left;
}

double length_read_right()
{
    return length_right;
}

double velocity_read()
{
    return (velocity_left + velocity_right) / 2;
}

void length_update()
{
    double encoder_left, encoder_right;
    double sampling_time_s;
    sampling_time_s = length_update_sampling_time_s;
    /* encoder をセットしてから encoder_length を読み出さないといけない */
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
  printf("tim10.c > ");
  printf("tim10_d_print() > velocity_left = %7.2f, velocity_right = %7.2f, velocity = %7.2f\r\n", velocity_left, velocity_right, velocity);
  printf("tim10_d_print() > length_left = %7.2f, length_right = %7.2f, length = %7.2f\r\n", length_left, length_right, length);
  #endif
}
