#ifndef __TIM10_H__
#define __TIM10_H__

#include "localization.h"
#include "kcm_controller.h"
#include "velotrace.h"
#include "angletrace.h"

/* 全部 tim10 でやってしまえば良いのでは？？？ */
#include "velotrace.h"
#include "angletrace.h"
#include "motor.h"

#define TIM10_TIME_MS 1 // [ ms ]

void tim10_init();
void tim10_start();
void tim10_stop();
void tim10_fin();

void tim10_main();

void tim10_d_print();
void tim10_d_print_main();

#endif
