#ifndef __TIM10_H__
#define __TIM10_H__

#include "print.h"
#include "rotary.h"
#include "explore.h"
#include "shortcut.h"
#include "calibration.h"

#define TIM10_TIME_MS 1 // [ ms ]

#define D_TIM10 1

void tim10_init();
void tim10_start();
void tim10_stop();
void tim10_fin();

void tim10_main();

void tim10_d_print();
void tim10_d_print_main();

void tim10_flash_print_start();
void tim10_flash_print_main();
void tim10_flash_print_stop();

#endif
