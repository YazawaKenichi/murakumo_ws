/**
 * @file linetrace.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-07
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "linetrace.h"

uint8_t linetrace_sampling_time_ms;

void linetrace_init(uint8_t _linetrace_sampling_time_ms)
{
    linetrace_sampling_time_ms = _linetrace_sampling_time_ms;
    analog_init();
    encoder_init();
    tracer_init(linetrace_sampling_time_ms);
    velotrace_init(linetrace_sampling_time_ms);
    motor_init();
}

void linetrace_start()
{
    analog_set_analogmode(analogmode_short);
    analog_start();
    encoder_start();
    tracer_start();
    velotrace_start();
    motor_start();
}

void linetrace_main()
{
    float tracer_left, tracer_right;
    float velotrace_left, velotrace_right;
    int direction;
    float velocity;
    float left, right;

    direction = linetrace_read_direction();
    velocity = linetrace_read_velocity();

    tracer_left = tracer_solve(direction);
    tracer_right = -tracer_left;
    velotrace_left = velotrace_solve(velocity);
    velotrace_right = velotrace_left;

    left = tracer_left + velotrace_left;
    right = tracer_right + velotrace_right;

    motor_set(left, right);
}

void linetrace_stop()
{
    motor_stop();
    tracer_stop();
    velotrace_stop();
    analog_stop();
    encoder_stop();
}

void linetrace_fin()
{
}

int linetrace_read_direction()
{
    uint16_t analog_left, analog_right;
    uint16_t short_middle;

    analog_left = 0;
    analog_right = 0;

    AnalogMode am;
    am = analog_read_analogmode();

    if(am == analogmode_short)
    {
        analog_left = 
        analog_read(0)
        + analog_read(2)
        + analog_read(4)
        + analog_read(6)
        + analog_read(8)
        + analog_read(10);
        analog_right = 
        analog_read(1)
        + analog_read(3)
        + analog_read(5)
        + analog_read(7)
        + analog_read(9)
        + analog_read(11);
        short_middle = 
        analog_read(0)
         + analog_read(1)
         + analog_read(2)
         + analog_read(3)
         + analog_read(4)
         + analog_read(5);
    }
    if(am == analogmode_long)
    {
    }
    if(am == analogmode_all)
    {
    }

    if(short_middle <= CLOSS_IGNORE_THRESHOLD * SHORT_MIDDLE_SENSOR)
    {
        analog_left = 3 * (analog_read(12) + analog_read(14));
        analog_right = 3 * (analog_read(13) + analog_read(15));
        linetrace_set_gain_long();
    }
    else
    {
        linetrace_set_gain_short();
    }

    return analog_left - analog_right;
}

float linetrace_read_velocity()
{
    float _velocity;
    //! [ m / s ]
    _velocity = encoder_read() * 0.001;
    return _velocity;
}

void linetrace_set_gain_short()
{
    tracer_set_gain_default();
}

void linetrace_set_gain_long()
{
    float kp, ki, kd;
    kp = LINETRACE_LONG_KP;
    ki = LINETRACE_LONG_KI;
    kd = LINETRACE_LONG_KD;
    tracer_set_gain_direct(kp, ki, kd);
}

void linetrace_d_print()
{
    analog_rate_array_print();
    velotrace_d_print();
}
