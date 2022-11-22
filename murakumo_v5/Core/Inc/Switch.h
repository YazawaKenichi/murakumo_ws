#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "print.h"
#include "defines.h"

typedef struct
{
    uint8_t value;
    uint8_t before;
    uint8_t press;
    uint8_t release;
} Switch;

void switch_set_enter();
void switch_reset_enter();
void switch_init();
uint8_t switch_read_enter();
uint8_t switch1_read();
uint8_t switch2_read();
uint8_t switch_read();
void switch_enter();

#endif
