#include "tim10.h"

/* lengths is updated only in tim10 file. */
double length, length_left, length_right;
double velocity_left, velocity_right, velocity;

double tim10_left, tim10_right;

/* only use in main.c */
void tim10_init()
{
  length_init(TIM10_Hz);
  course_init();
  velotrace_init(1);
  HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
  tim10_left = 0;
  tim10_right = 0;
  /* marker = subsensbuf = sidedeltacount = markerstate = rightmarkercount = 0 */
  length_start();
  velotrace_start();
  slow_start(velotrace_read_values());
  HAL_TIM_Base_Start_IT(&htim10);
}

void tim10_stop()
{
	HAL_TIM_Base_Stop_IT(&htim10);
  velotrace_stop();
  length_stop();
}

void tim10_fin()
{
  length_fin();
  HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_main()
{
  length_update();
  tim10_update_length();
}

//! tim10_main でのみ呼び出されるべき関数
void tim10_update_length()
{
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
  tim10_left  = velotrace_solve(velocity_read());
  tim10_right = tim10_left;

  #if D_TIM10_WHILE
  printf("tim10.c > tim10_main() > tim10_left = %7.2f, tim10_right = %7.2f\r\n", tim10_left, tim10_right);
  #endif

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
  course_d_print();
}

double tim10_read_left()
{
  return tim10_left;
}

double tim10_read_right()
{
  return tim10_right;
}
