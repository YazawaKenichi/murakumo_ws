#ifndef __TIM7_H__
#define __TIM7_H__

#include "print.h"
#include "defines.h"
#include "flash.h"
#include "analog.h"
#include "tracer.h"
#include "Switch.h"
#include "Rotary.h"

#define D_TIM7 (0 + D_TRACER + D_ANALOG)
#define D_TIM7_WHILE (0 + D_TRACER_WHILE)

#define TIM7_EMERGENCY_THRESHOLD 980

void tim7_init();
void tim7_start();
void tim7_stop();
void tim7_main();
int tim7_read_direction();
void tim7_main_emergency();
void tim7_set_emergency(char);
char tim7_read_emergency();
double tim7_read_left();
double tim7_read_right();
void tim7_d_print();

#endif
