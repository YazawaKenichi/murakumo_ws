#ifndef __TIM6_H__
#define __TIM6_H__

#include "print.h"
#include "motor.h"
#include "defines.h"
#include "Rotary.h" /* rotary_read_playmode() */
#include "sidesensor.h"
#include "tim7.h"
#include "tim10.h"

#define D_TIM6 (0 + D_MOTOR + D_SIDESENSOR + D_TIM7 + D_TIM10)

#define D_TIM6_WHILE (0 + D_MOTOR_WHILE + D_TIM7_WHILE + D_TIM10_WHILE)
#define D_TIM6_EXCLUSION 1
#define D_TIM6_IGNORE 1

#if D_TIM6_IGNORE
#define TRACER_TUNING 1
#define VELOTRACE_TUNING 1
#endif

#define TEMPORARY 0

#define TIM6_EMERGENCY_STOP 0

void tim6_init();
void tim6_start();
void tim6_stop();
void tim6_main();

void tim6_d_print();

#endif
