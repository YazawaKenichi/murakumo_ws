#ifndef __TIM7_H__
#define __TIM7_H__

#include "print.h"
#include "defines.h"
#include "flash.h"
#include "analog.h"
#include "tracer.h"
#include "Switch.h"
#include "Rotary.h"
#include "sidesensor.h"

#define D_TIM7 0
#define D_TIM7_WHILE (0 + D_TRACER_WHILE)

#define TIM7_EMERGENCY_THRESHOLD 980

#define TIM7_TIME_MS 1  //! [ ms ]

/* analog short でトレースするか long でトレースするか判断用の定数 */
#define CLOSS_IGNORE_THRESHOLD 500
#define SHORT_MIDDLE_SENSOR 6

/* analogmode_long が指定された時のライントレースゲイン値 */
#define TIM7_LONG_KP 0.2f
#define TIM7_LONG_KI 0
#define TIM7_LONG_KD 0.0045f

void tim7_init();
void tim7_start();
void tim7_stop();
void tim7_main();
int tim7_read_direction();
void tim7_main_emergency();
void tim7_set_emergency(char);
char tim7_read_emergency();
float tim7_read_left();
float tim7_read_right();
void tim7_d_print();
void tim7_tracer_set_gain_short();
void tim7_tracer_set_gain_long();

#endif
