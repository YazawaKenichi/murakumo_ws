#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "math.h"
#include "defines.h"
#include "print.h"

#ifndef D_ENCODER
#define D_ENCODER 1
#endif

// #define ENCODER_MIDDLE (4096/2)
#define ENCODER_MIDDLE (4096/2)

/* LENGTH PER PULSE */
#define TIREDIAMETER 21000
#define PULSEPERROTATE 4096
#define PINION 25
#define SUPER 64

#ifndef __OBSOLETE_MATH
#define M_PI 3.14159265358979f
#endif

void encoder_init();
void encoder_finalize();
void encoder_set_middle();
void encoder_start();
void encoder_stop();
double encoder_read();
double encoder_read_left();
double encoder_read_right();
double encoder_length_left();
double encoder_length_right();
double encoder_length();
void encoder_set();

extern double LENGTHPERPULSE;

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
