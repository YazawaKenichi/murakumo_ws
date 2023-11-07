#ifndef __TIM11_H__
#define __TIM11_H__

#include "print.h"
#include "switch.h"
#include "rotary.h"
#include "sidesensor.h"
#include "defines.h"
#include "analog.h"
#include "encoder.h"
#include "imu.h"
#include "time.h"

void tim11_init();
void tim11_start();
void tim11_stop();

void tim11_main();

void tim11_d_print();
void tim11_d_print_main();

#endif