#include "slow.h"

PID *base_pointer;
double slowinglength;

void slow_start(PID *_pid)
{
    /* slow_start */
    slowinglength = 0;
    base_pointer = _pid;
}

void slow_stop()
{
    /* slow_stop */
}

double slow_sigmoid(double x)
{
    return sigmoid(x, SLOW_SIGMOID_A, SLOW_LENGTH / 2);
}

void slow_set_velocity(double _velocity)
{
    slow_velocity = _velocity;
}

double slow_read_velocity()
{
    return slow_velocity;
}

void slow_set_give_velocity(double _slow_give_velocity)
{
    slow_give_velocity = _slow_give_velocity;
}

double slow_main()
{
    /* slowinglength 現在進んだ距離 */
    /* slow_main() の直前で slow_set_velocity() する必要がある */
    slowinglength += slow_read_velocity();
    if( slowinglength <= SLOW_LENGTH )
    {
        double rate;
        rate = slow_sigmoid(slowinglength);
        slow_set_give_velocity((double) base_pointer->target * rate);
        if(rate >= THREE_SIGMA)
        {
            /* 3σ を超えたら目標速度を呼び戻す */
            = base_pointer->target;
        }
    }
}
