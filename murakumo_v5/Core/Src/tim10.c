#include "print.h"
#include "tim10.h"

/* lengths is updated only in tim10 file. */
unsigned int tim10_samplingtime_ms;
PlayMode tim10_playmode;
uint16_t tim10_flash_print_index;

/* only use in main.c */
void tim10_init()
{
	tim10_samplingtime_ms = TIM10_TIME_MS;
	tim10_playmode = rotary_read_playmode();
	calibration_init();
	explore_init(tim10_samplingtime_ms);
	shortcut_init(tim10_samplingtime_ms);
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
	switch(tim10_playmode)
	{
		case pm_calibration:
			printf("tim10_start : calibration\r\n");
			calibration_start();
			printf("--debug line 01--\r\n");
			break;
		case pm_explore:
			printf("tim10_start : explore\r\n");
			explore_start();
			break;
		case pm_shortcut:
			printf("tim10_start : shortcut\r\n");
			shortcut_start();
			break;
		case pm_print:
			printf("tim10_start : print\r\n");
			tim10_flash_print_start();
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
	switch(tim10_playmode)
	{
		case pm_calibration:
			calibration_stop();
			break;
		case pm_explore:
			explore_stop();
			break;
		case pm_shortcut:
			shortcut_stop();
			break;
		case pm_print:
			tim10_flash_print_stop();
			break;
		default:
			break;
	}
}

void tim10_fin()
{
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_main()
{
	switch(tim10_playmode)
	{
		case pm_calibration:
			calibration_main();
			break;
		case pm_explore:
			explore_main();
			break;
		case pm_shortcut:
			shortcut_main();
			break;
		case pm_print:
			tim10_flash_print_main();
			break;
		default :
			break;
	}
}

void tim10_d_print()
{
	calibration_d_print();
	explore_d_print();
	shortcut_d_print();
}

void tim10_d_print_main()
{
}

void tim10_flash_print_start()
{
	tim10_flash_print_index = 0;
	flash_init();
	switch(rotary_read())
	{
		case 14:
			smoothing(imudata.yaw, COURSE_STATE_SIZE, ADJACENT);
			break;
		default:
			break;
	}
}

void tim10_flash_print_main()
{
	float raw;
	switch(rotary_read())
	{
		case 15:
		case 14:
			raw = imudata.yaw[tim10_flash_print_index];
			break;
		default:
			break;
	}
	printf("%lf\r\n", raw);
	tim10_flash_print_index++;
}

void tim10_flash_print_stop()
{
}
