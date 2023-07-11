#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "math.h"
#include "defines.h"
#include "function.h"
#include "stm32f4xx_hal_tim.h"
#include "print.h"

#define D_ENCODER 0
#define D_ENCODER_WHILE 0

/* LENGTH PER PULSE */
#define TIREDIAMETER 21000  /* [um] */
#define ERROR -32000

//! 左右のエンコーダの分解能を記入する
#define PULSEPERROTATE_LEFT (1024 * 5) /* [cnt] */
#define PULSEPERROTATE_RIGHT (1024 * 10) /* [cnt] */

#define PINION 25
#define SUPER 64

#ifndef __OBSOLETE_MATH
#define M_PI 3.14159265358979f
#endif

#define REDUCTION_RATIO (PINION / (float) SUPER)
//! LENGTHPERPULSE = (pi * 21000 * (25 / 64)) / 4096 = 6.29 [ um / cnt ]
#define LENGTHPERPULSE_LEFT (M_PI * (TIREDIAMETER - ERROR) * REDUCTION_RATIO / (float) PULSEPERROTATE_LEFT)    /* [um / cnt] */
#define LENGTHPERPULSE_RIGHT (M_PI * (TIREDIAMETER - ERROR) * REDUCTION_RATIO / (float) PULSEPERROTATE_RIGHT)

#define ENCODER_MIDDLE_LEFT (PULSEPERROTATE_LEFT / (float) 2)
#define ENCODER_MIDDLE_RIGHT (PULSEPERROTATE_RIGHT / (float) 2)

void encoder_init();
void encoder_start();
void encoder_stop();
void encoder_fin();

void encoder_update();

float encoder_read();
float encoder_read_left();
float encoder_read_right();

void encoder_set();
void encoder_set_middle();

void encoder_d_print();

#endif
