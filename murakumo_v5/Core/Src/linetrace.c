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

void linetrace_init();
{
    analog_init();
    encoder_init();
    tracer_init(1);
    velotrace_init(1);
    motor_init();
}

void linetrace_start()
{
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
    analog_stop();
    encoder_stop();
    tracer_stop();
    velotrace_stop();
    motor_stop();
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

    switch(analog_read_analogmode())
    {
        case analogmode_calibrating:
            break;
        case analogmode_short:
            i_count = 12;
            i_start = 0;
            break;
        case analogmode_long:
            i_count = 4;
            i_start = 12;
            break;
        case analogmode_all:
            i_count = 16;
            i_start = 0;
            break;
        default:
            /* Unknown Analog Mode */
            break;
    }

    for(unsigned char i = i_start; i < (i_count + i_start); i++)
    {
        if(i % 2 == 0)
        {
            analog_left += analog_read(i);
        }
        else
        {
            analog_right += analog_read(i);
        }
        if(i < SHORT_MIDDLE_SENSOR)
        {
            short_middle = analogl + analogr;
        }
    }

    if(short_middle <= CLOSS_IGNORE_THRESHOLD * SHORT_MIDDLE_SENSOR)
    {
        analog_left = 3 * (analog_read(12) + analog_read(14));
        analog_right = 3 * (analog_read(13) + analog_read(15));
        linetrace_tracer_set_gain_long();
    }
    else
    {
        linetrace_tracer_set_gain_short();
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

void linetrace_tracer_set_gain_short()
{
    tracer_set_gain_default();
}

void linetrace_tracer_set_gain_long()
{
    float kp, ki, kd;
    kp = linetrace_LONG_KP;
    ki = linetrace_LONG_KI;
    kd = linetrace_LONG_KD;
    tracer_set_gain_direct(kp, ki, kd);
}
