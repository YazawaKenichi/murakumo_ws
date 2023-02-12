#include "slow.h"

PID *base_pointer;
PID slow_pid;
float slowinglength;
float slow_velocity;
uint8_t slow_enable;

void slow_init()
{
    /* slow_init */
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

void slow_fin()
{
    /* slow_fin */
}

/**
 * @fn slow_main()
 * @brief 
 * tim10_update() で呼び出される関数
 * これ一つを tim10_update() で実行するだけで slow start / slow stop するようにしたい
 * 
 */
void slow_main()
{
}

uint8_t slow_read_enable()
{
}

float slow_read_velocity()
{
    /* slow_read_velocity */
}

/**
 * @brief 
 * 
 * @return PID* 
 */
PID *slow_read_gain_values()
{
    /* slow_read_gain_values */
}

void slow_set_enable(uint8_t enable_)
{
    /* slow_set_enable */
}

void slow_set_values(float _rate)
{
    /* slow_set_values */
}

void slow_set_velocity(float _velocity)
{
    /* slow_set_give_velocity */
}

float slow_sigmoid(float x)
{
    return sigmoid(x, SLOW_SIGMOID_A, SLOW_LENGTH / 2);
}
