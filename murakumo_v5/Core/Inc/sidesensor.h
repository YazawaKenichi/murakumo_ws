#ifndef __SIDESENSOR_H__
#define __SIDESENSOR_H__

#include "defines.h"
#include "stm32f4xx_hal.h"
#include "print.h"

#define D_SIDESENSOR 0

typedef enum SIDESENSORSTATE
{
    none,
    straight,
    start,
    stop,
    curve,
    cross
} SideSensorState;

void sidesensor_start();
void sidesensor_init();
void sidesensor_stop();
uint8_t sidesensor_read();
void sidesensor_right();
void sidesensor_left();
void sidesensor_cross();
void sidesensor_main();
SideSensorState sidesensor_read_markerstate();
SideSensorState sidesensor_read_markerstate_volatile();
void sidesensor_set_state(SideSensorState);
void sidesensor_d_print();
void sidesensor_print_sidesensorstate(SideSensorState markerstate_);

#endif
