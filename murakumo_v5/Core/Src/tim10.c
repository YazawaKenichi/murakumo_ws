#include "tim10.h"

/* lengths is updated only in tim10 file. */
double length, length_left, length_right;
double velocity_left, velocity_right, velocity;

double tim10_read_length_left()
{
  return length_left;
}

double tim10_read_length_right()
{
  return length_right;
}

double tim10_read_length()
{
  return length;
}

double tim10_read_velocity_left()
{
  return velocity_left;
}

double tim10_read_velocity_right()
{
  return velocity_right;
}

double tim10_read_velocity()
{
  return velocity;
}

/* only use in main.c */
void tim10_init()
{
  tim10_length_set_zero();
  tim10_velocity_set_zero();
	encoder_init();
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
  /* encoder_set_middle, HAL_TIM_Encoder_Start */
  encoder_start();
  /* marker = subsensbuf = sidedeltacount = markerstate = rightmarkercount = 0 */
  sidesensor_start();
  tim10_length_set_zero();
  tim10_velocity_set_zero();
  HAL_TIM_Base_Start_IT(&htim10);
}

void tim10_stop()
{
	HAL_TIM_Base_Stop_IT(&htim10);
  sidesensor_stop();
  encoder_stop();
}

void tim10_main()
{
  double el, er, e;

  /* encoder をセットしてから encoder_length を読み出さないといけない */

  /* set encoder middle and update velocities */
  encoder_set();

  el = encoder_length_left();
  er = encoder_length_right();
  e = encoder_length();

  /* update velocity */
  velocity_left = el * (double) TIM10_Hz;
  velocity_right = er * (double) TIM10_Hz;
  velocity = e * (double) TIM10_Hz;

  /* update lengths */
  length_left += velocity_left;
  length_right += velocity_right;
  length += velocity;

  /*
  if(length >= SAMPLING_LENGTH)
  {
    course_state_function();
  }
  */

  sidesensor_function();
}

void tim10_d_print()
{
  #if D_TIM10
  printf("tim10.c > ");
  printf("tim10_d_print() > encoder_length_left() = %7.5f, encoder_length_right() = %7.5f, encoder_length() = %7.5f\r\n", encoder_length_left(), encoder_length_right(), encoder_length());
  printf("tim10_d_print() > velocity_left = %7.2f, velocity_right = %7.2f, velocity = %7.2f\r\n", velocity_left, velocity_right, velocity);
  printf("tim10_d_print() > length_left = %7.2f, length_right = %7.2f, length = %7.2f\r\n", length_left, length_right, length);
  #endif
  #if D_ENCODER
  encoder_d_print();
  #endif
}

/* private */
void tim10_length_set_zero()
{
  length_left = 0;
  length_right = 0;
  length = 0;
}

void tim10_velocity_set_zero()
{
  velocity_left = 0;
  velocity_right = 0;
  velocity = 0;
}
