#include "tim10.h"

/* lengths is updated only in tim10 file. */
unsigned int tim10_samplingtime_ms;

/* only use in main.c */
void tim10_init()
{
	tim10_samplingtime_ms = TIM10_TIME_MS;
	explore_init();
	locomotion_init();
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
	explore_start();
	locomotion_start();
	HAL_TIM_Base_Start_IT(&htim10);
}

void tim10_stop()
{
	HAL_TIM_Base_Stop_IT(&htim10);
	locomotion_stop();
	explore_stop();
}

void tim10_fin()
{
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_main()
{
	switch()
	{
		case :
			explore_main();
		case :
			locomotion_main();
		default :
	}
}

void tim10_d_print()
{
	explore_d_print();
	locomotion_d_print();
}

void tim10_d_print_main()
{
}
