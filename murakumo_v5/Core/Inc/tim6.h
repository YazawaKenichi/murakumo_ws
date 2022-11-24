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

#if VELOTRACE_IN_TIM10
#include "tim10.h"
#endif

#define D_TIM6 0

#define D_TIM6_WHILE 0
#define D_TIM6_EXCLUSION 1
#define D_TIM6_IGNORE 1

#if D_TIM6_IGNORE
#define TRACER_TUNING 0
#define VELOTRACE_TUNING 0
#endif

#define TEMPORARY 0

#define TIM6_EMERGENCY_STOP 0

void tim6_init();
void tim6_start();
void tim6_stop();
void tim6_main();

void tim6_d_print();

#endif
