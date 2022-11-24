#ifndef __TIM7_H__
#define __TIM7_H__

#include "print.h"
#include "defines.h"
#include "flash.h"
#include "analog.h"
#include "tracer.h"

#define D_TIM7 1

void tim7_init();
void tim7_start();
void tim7_stop();
void tim7_main();
void tim7_d_print();

#endif
