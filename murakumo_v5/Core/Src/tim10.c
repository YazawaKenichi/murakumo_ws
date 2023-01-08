#include "tim10.h"

/* lengths is updated only in tim10 file. */
double length, length_left, length_right;
double velocity_left, velocity_right, velocity;

double tim10_left, tim10_right;

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
  velotrace_init(1);
	encoder_init();
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
  tim10_left = 0;
  tim10_right = 0;
  /* encoder_set_middle, HAL_TIM_Encoder_Start */
  encoder_start();
  /* marker = subsensbuf = sidedeltacount = markerstate = rightmarkercount = 0 */
  velotrace_start();
  slow_start(velotrace_read_values());
  tim10_length_set_zero();
  tim10_velocity_set_zero();
  HAL_TIM_Base_Start_IT(&htim10);
}

void tim10_stop()
{
	HAL_TIM_Base_Stop_IT(&htim10);
  velotrace_stop();
  encoder_stop();
}

void tim10_main()
{
  double el, er, e;

  /* encoder をセットしてから encoder_length を読み出さないといけない */

  /* set encoder middle and update velocities */
  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > ");
  #endif
  encoder_set();

  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > ");
  #endif
  el = encoder_length_left();
  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > ");
  #endif
  er = encoder_length_right();
  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > ");
  #endif
  e = encoder_length();

  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > el = %7.2f, er = %7.2f, e = %7.2f\r\n", el, er, e);
  #endif

  /* update velocity */
  velocity_left = el * (double) TIM10_Hz;
  velocity_right = er * (double) TIM10_Hz;
  velocity = e * (double) TIM10_Hz;

  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > velocity_left = %7.2f, velocity_right = %7.2f, velocity = %7.2f\r\n", velocity_left, velocity_right, velocity);
  #endif

  /* slow start のプログラムいれたけど、できないよ！ */
  #if USE_SLOWSTART
  if(slow_read_enable())
  {
    slow_set_velocity(velocity);
    slow_main();
    velotrace_set_values(slow_read_gain_values());
  }
  #endif

  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > ");
  #endif
  tim10_left  = velotrace_solve(velocity);
  tim10_right = tim10_left;

  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > tim10_left = %7.2f, tim10_right = %7.2f\r\n", tim10_left, tim10_right);
  #endif

  /* update lengths */
  length_left += velocity_left;
  length_right += velocity_right;
  length += velocity;

  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > length_left = %7.2f, length_right = %7.2f, length = %7.2f\r\n", length_left, length_right, length);
  #endif

  /*
  if(length >= SAMPLING_LENGTH)
  {
    course_state_function();
  }
  */
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

double tim10_read_left()
{
  return tim10_left;
}

double tim10_read_right()
{
  return tim10_right;
}
