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
    printf("ENCODER_MIDDLE_LEFT = %7.2f, ENCODER_MIDDLE_RIGHT = %7.2f\r\n", ENCODER_MIDDLE_LEFT, ENCODER_MIDDLE_RIGHT);
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

void encoder_update()
{
    uint16_t el_now, er_now;

    el_now = TIM1->CNT;
    er_now = TIM3->CNT;

    encoder_set_middle();

    encoder_left = low_pass_filter(el_now - ENCODER_MIDDLE_LEFT, encoder_left, 0.25f);
    encoder_right = low_pass_filter(-(er_now - ENCODER_MIDDLE_RIGHT), encoder_right, 0.25f);
    encoder = low_pass_filter((encoder_left + encoder_right) / (float) 2, encoder, 0.25);
}

float encoder_read()
{
    //! 単位は [ um ]
    return (float) (encoder_read_left() + encoder_read_right()) / 2;
}

float encoder_read_left()
{
    return (float) encoder_left * (float) LENGTHPERPULSE_LEFT;
}

float encoder_read_right()
{
    return (float) encoder_right * (float) LENGTHPERPULSE_RIGHT;
}

/* private */
void encoder_set_middle()
{
    TIM1 -> CNT = ENCODER_MIDDLE_LEFT;
    TIM3 -> CNT = ENCODER_MIDDLE_RIGHT;
}

void encoder_d_print()
{
#if D_ENCODER
    printf("TIM1->CNT = %d, TIM3->CNT = %d\r\n", TIM1->CNT, TIM3->CNT);
    printf("encoder_left = %d, encoder_right = %d, encoder = %f\r\n", encoder_left, encoder_right, encoder);
    // printf("\x1b[2A]");
#endif
}

void encoder_d_print_main()
{
#if D_ENCODER
#endif
}
