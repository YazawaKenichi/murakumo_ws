#ifndef __SIDESENSOR_H__
#define __SIDESENSOR_H__

#include "defines.h"

typedef enum SIDESENSORSTATE
{
    straight = 0,
    start_or_stop = 1,
    curve = 2,
    cross = 3
} SideSensorState;

void sidesensor_start();
void sidesensor_init();
void sidesensor_stop();
uint8_t sidesensor_read();
void sidesensor_right();
void sidesensor_left();
void sidesensor_cross();
void sidesensor_function();
SideSensorState sidesensor_read_state();
void sidesensor_set_state(SideSensorState);

#endif

