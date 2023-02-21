#include "encoder.h"

/* encoders are updated only in encoder file. */
int16_t encoder_left, encoder_right;
float encoder;

/* public */
float encoder_length()
{
    #if D_ENCODER_WHILE
    printf("encoder.c > encoder_length() > ");
    printf("encoder * (float) LENGTHPERPULSE = %6.1f * %1.5f = %7.5f\r\n", encoder, LENGTHPERPULSE, encoder * (float) LENGTHPERPULSE);
    #endif
    //! 単位は [ um ]
    return (float) encoder * (float) LENGTHPERPULSE;
}

float encoder_length_left()
{
    #if D_ENCODER_WHILE
    printf("encoder.c > encoder_length_left() > ");
    printf("encoder_left * (float) LENGTHPERPULSE = %5d * %1.5f = %7.5f\r\n", encoder_left, LENGTHPERPULSE, encoder_left * (float) LENGTHPERPULSE);
    #endif
    return (float) encoder_left * (float) LENGTHPERPULSE;
}

float encoder_length_right()
{
    #if D_ENCODER_WHILE
    printf("encoder.c > encoder_length_right() > ");
    printf("encoder_right * (float) LENGTHPERPULSE = %5d * %1.5f = %7.5f\r\n", encoder_right, LENGTHPERPULSE, encoder_right * (float) LENGTHPERPULSE);
    #endif
    return (float) encoder_right * (float) LENGTHPERPULSE;
}

void encoder_d_print()
{
    #if D_ENCODER
    printf("encoder.c > encoder_left = %5d, encoder_left = %5d, encoder = %f\r\n", encoder_left, encoder_right, encoder);
    #endif
}

/* only read tim10_update_values */
void encoder_set()
{
    encoder_left = TIM1 -> CNT - ENCODER_MIDDLE;
    encoder_right = -(TIM3 -> CNT - ENCODER_MIDDLE);
    //! 単位 [ cnt / sampling_time_s ]
    encoder = (encoder_left + encoder_right) / (float) 2;

    #if D_ENCODER_WHILE
    printf("encoder.c > encoder_set() > ");
    printf("encoder_left = %6d, encoder_right = %6d, encoder = %6.1f\r\n", encoder_left, encoder_right, encoder);
    #endif

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
    #if D_ENCODER_WHILE
    printf("encoder.c > encoder_set_middle() > ");
    printf("TIM1 -> CNT = %6lu, TIM3 -> CNT = %6lu\r\n", TIM1->CNT, TIM3->CNT);
    #endif
}
