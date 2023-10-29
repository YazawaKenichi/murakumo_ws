#ifndef __TIM10_H__
#define __TIM10_H__

#include "explore.h"
#include "locomotion.h"

#define TIM10_TIME_MS 1 // [ ms ]

#define D_TIM10 1

void tim10_init();
void tim10_start();
void tim10_stop();
void tim10_fin();

void tim10_main();

void tim10_d_print();
void tim10_d_print_main();

#endif
