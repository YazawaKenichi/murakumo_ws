#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "stm32f4xx_hal.h"

typedef struct
{
    uint8_t value;
    uint8_t before;
    uint8_t press;
    uint8_t release;
} Switch;

void switch_init();
void switch_start();
void switch_stop();
void switch_update();
uint8_t switch_read();
uint8_t switch1_read();
uint8_t switch2_read();
uint8_t switch_read_enter();
void switch_set_enter();
void switch_reset_enter();

#endif
