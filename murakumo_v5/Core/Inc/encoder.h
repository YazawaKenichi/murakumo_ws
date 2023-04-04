#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "math.h"
#include "defines.h"
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

#define ENCODER_MIDDLE_LEFT (PULSEPERROTATE_LEFT / 2)
#define ENCODER_MIDDLE_RIGHT (PULSEPERROTATE_RIGHT / 2)

float encoder_length_left();
float encoder_length_right();
float encoder_length();
void encoder_d_print();
void encoder_set();
void encoder_init();
void encoder_fin();
void encoder_start();
void encoder_stop();
void encoder_set_middle();

#endif

/* usuage */
/*
    enc_init()
    {
        ...
        encoder_init();
        HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
        HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
        ...
    }
*/
