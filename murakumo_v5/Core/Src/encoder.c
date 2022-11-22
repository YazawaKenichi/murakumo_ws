#include "encoder.h"

double LENGTHPERPULSE;
/* encoders are updated only in encoder file. */
double encoder_left, encoder_right, encoder;

/* private */
void encoder_init()
{
    LENGTHPERPULSE = M_PI * TIREDIAMETER * PINION / (double) PULSEPERROTATE / (double) SUPER;
    #if D_ENCODER
    printf("LENGTHPERPULSE = %7.3f\r\n", LENGTHPERPULSE);
    #endif
}

double encoder_LENGTHPERPULSE()
{
    return LENGTHPERPULSE;
}

double encoder_length()
{
  return (double) encoder_read() * (double) LENGTHPERPULSE;
}

double encoder_length_left()
{
  return (double) encoder_read_left() * (double) LENGTHPERPULSE;
}

double encoder_length_right()
{
  return (double) encoder_read_right() * (double) LENGTHPERPULSE;
}

void encoder_finalize()
{
    encoder_stop();
}

/* private */
void encoder_set_middle()
{
    TIM1 -> CNT = ENCODER_MIDDLE;
    TIM2 -> CNT = ENCODER_MIDDLE;
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

double encoder_read()
{
    return encoder;
}

double encoder_read_left()
{
    return encoder_left;
}

double encoder_read_right()
{
    return encoder_right;
}

/* only read tim10_main */
void encoder_set()
{
    encoder_left = TIM1 -> CNT - ENCODER_MIDDLE;
    encoder_right = -(TIM3 -> CNT - ENCODER_MIDDLE);
    encoder = (encoder_left + encoder_right) / 2;

    encoder_set_middle();
}

void encoder_d_print()
{
    #if D_ENCODER
    printf("[encoder] > encoder_read_left() = %7.3f, encoder_read_left() = %7.3f, encoder_read() = %7.3f\r\n", encoder_read_left(), encoder_read_right(), encoder_read());
    #endif
}
