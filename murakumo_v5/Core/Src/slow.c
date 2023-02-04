#include "slow.h"

PID *base_pointer;
PID slow_pid;
float slowinglength;
float slow_velocity;
char slow_enable;

char slow_read_enable()
{
    return slow_enable;
}

void slow_set_enable(char slow_enable_)
{
    slow_enable = slow_enable_;
}

void slow_start(PID *_pid)
{
    /* slow_start */
    slowinglength = 0;
    base_pointer = _pid;
    slow_pid.target = 0;
    slow_pid.kp = 0;
    slow_pid.ki = 0;
    slow_pid.kd = 0;
    slow_enable = 1;
}

void slow_stop()
{
    /* slow_stop */
}

float slow_sigmoid(float x)
{
    return sigmoid(x, SLOW_SIGMOID_A, SLOW_LENGTH / 2);
}

PID *slow_read_gain_values()
{
    PID* slow_pid_ = &slow_pid;
    return slow_pid_;
}

void slow_set_values(float _rate)
{
    slow_pid.target = (float) base_pointer->target * _rate;
    slow_pid.kp = (float) base_pointer->kp * _rate;
    slow_pid.ki = (float) base_pointer->ki * _rate;
    slow_pid.kd = (float) base_pointer->kd * _rate;
}

void slow_set_velocity(float _velocity)
{
    slow_velocity = _velocity;
}

float slow_read_velocity()
{
    return slow_velocity;
}

void slow_main()
{
    float rate;
    /* slowinglength 現在進んだ距離 */
    /* slow_main() の直前で slow_set_velocity() する必要がある */
    slowinglength += slow_read_velocity();
    rate = slow_sigmoid(slowinglength);
    if(rate < 0.2f)
    {
        rate = 0.2f;
    }
    if( slowinglength <= SLOW_LENGTH )
    {
        slow_set_values(rate);
    }
    else
    {
        slow_set_values(1.0f);
        slow_set_enable(0);
    }
}
