#ifndef __TIM6_H__
#define __TIM6_H__

#include "print.h"
#include "analog.h"
#include "flash.h"
#include "motor.h"
#include "velotrace.h"
#include "tracer.h"
#include "defines.h"
#include "Rotary.h" /* rotary_read_playmode() */

#define D_TIM6 1

#define D_TIM6_WHILE 1
#define EXCLUSION 1

void tim6_init();
void tim6_start();
void tim6_stop();
void tim6_main();

void tim6_d_print();

#endif
