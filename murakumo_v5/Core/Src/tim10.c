#include "print.h"
#include "tim10.h"

/* lengths is updated only in tim10 file. */
unsigned int tim10_samplingtime_ms;
unsigned int __debug_main_count__;
PlayMode tim10_playmode;

/* only use in main.c */
void tim10_init()
{
	__debug_main_count__ = 0;
	tim10_samplingtime_ms = TIM10_TIME_MS;
	tim10_playmode = rotary_read_playmode();
	explore_init(tim10_samplingtime_ms);
	shortcut_init(tim10_samplingtime_ms);
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
	switch(tim10_playmode)
	{
		case pm_explore:
			printf("tim10_start : explore\r\n");
			explore_start();
			break;
		case pm_shortcut:
			printf("tim10_start : shortcut\r\n");
			shortcut_start();
			break;
		default :
			printf("tim10_start : default\r\n");
			break;
	}
	HAL_TIM_Base_Start_IT(&htim10);
}

void tim10_stop()
{
	HAL_TIM_Base_Stop_IT(&htim10);
	shortcut_stop();
	explore_stop();
}

void tim10_fin()
{
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_main()
{
	switch(tim10_playmode)
{
		case pm_explore:
			explore_main();
			break;
		case pm_shortcut:
			shortcut_main();
			break;
		default :
			break;
	}
}

void tim10_d_print()
{
	/*
	explore_d_print();
	shortcut_d_print();
	*/
	printf("tim10_d_print : %d\r\n", __debug_main_count__);
}

void tim10_d_print_main()
{
}
