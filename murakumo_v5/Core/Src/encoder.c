/**
 * @file encoder.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-03-30
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "encoder.h"

/* encoders are updated only in encoder file. */
int16_t encoder_left, encoder_right;
float encoder;

void encoder_init()
{
    #if D_ENCODER
    printf("LENGTHPERPULSE_LEFT = %7.2f, LENGTHPERPULSE_RIGHT = %7.2f\r\n", LENGTHPERPULSE_LEFT, LENGTHPERPULSE_RIGHT);
    #endif
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

void encoder_fin()
{
    encoder_stop();
}

float encoder_read()
{
    //! 単位は [ um ]
    return (float) (encoder_length_left() + encoder_length_right()) / 2;
}

float encoder_read_left()
{
    return (float) encoder_left * (float) LENGTHPERPULSE_LEFT;
}

float encoder_read_right()
{
    return (float) encoder_right * (float) LENGTHPERPULSE_RIGHT;
}

/* only read tim10_update_values */
void encoder_set()
{
    uint16_t el_now, er_now;

    el_now = TIM1->CNT;
    er_now = TIM3->CNT;
    encoder_set_middle();

    encoder_left = el_now - ENCODER_MIDDLE_LEFT;
    encoder_right = -(er_now - ENCODER_MIDDLE_RIGHT);
    //! 単位 [ cnt / sampling_time_s ]
    //! encoder_length() で読み出しても返されるのはこの値ではないことに注意
    encoder = (encoder_left + encoder_right) / (float) 2;

}

/* private */
void encoder_set_middle()
{
    TIM1 -> CNT = ENCODER_MIDDLE_LEFT;
    TIM3 -> CNT = ENCODER_MIDDLE_RIGHT;
}

void encoder_d_print()
{
}
