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
#define PULSEPERROTATE 4096 /* [cnt] */
#define PINION 25
#define SUPER 64

#ifndef __OBSOLETE_MATH
#define M_PI 3.14159265358979f
#endif

#define REDUCTION_RATIO (PINION / (float) SUPER)
#define LENGTHPERPULSE (M_PI * TIREDIAMETER * REDUCTION_RATIO / (float) PULSEPERROTATE)    /* [um / cnt] */
#define ENCODER_MIDDLE (PULSEPERROTATE / 2)

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
