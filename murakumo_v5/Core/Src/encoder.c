#include "encoder.h"

/* encoders are updated only in encoder file. */
int16_t encoder_left, encoder_right;
double encoder;

/* public */
double encoder_length()
{
    return (double) encoder * (double) LENGTHPERPULSE;
}

double encoder_length_left()
{
    return (double) encoder_left * (double) LENGTHPERPULSE;
}

double encoder_length_right()
{
    return (double) encoder_right * (double) LENGTHPERPULSE;
}

void encoder_d_print()
{
    #if D_ENCODER
    printf("encoder.c > encoder_left = %5d, encoder_left = %5d, encoder = %7.2f\r\n", encoder_left, encoder_right, encoder);
    #endif
}

/* only read tim10_main */
void encoder_set()
{
    encoder_left = TIM1 -> CNT - ENCODER_MIDDLE;
    encoder_right = -(TIM3 -> CNT - ENCODER_MIDDLE);
    encoder = (encoder_left + encoder_right) / (double) 2;

    encoder_set_middle();
}

void encoder_init()
{
    #if D_ENCODER
    printf("LENGTHPERPULSE = %7.2f\r\n", LENGTHPERPULSE);
    #endif
}

void encoder_fin()
{
    encoder_stop();
}

void encoder_start()
{
    encoder_left = 0;
    encoder_right = 0;
    encoder = 0;

    encoder_set_middle();

	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_Base_Start_IT(&htim10);
}

void encoder_stop()
{
	HAL_TIM_Encoder_Stop(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Stop(&htim3, TIM_CHANNEL_ALL);
}

/* private */
void encoder_set_middle()
{
    TIM1 -> CNT = ENCODER_MIDDLE;
    TIM3 -> CNT = ENCODER_MIDDLE;
}
