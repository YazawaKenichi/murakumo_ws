#include "time.h"

long double time_s;

void time_init()
{
}

void time_start()
{
    time_s = 0;
}

void time_stop()
{
}

void time_update(float dt)
{
    time_s += dt;
}

long double time_read()
{
    return time_s;
}
