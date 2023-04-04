#include "tim10.h"

/* lengths is updated only in tim10 file. */
float tim10_left, tim10_right;
unsigned int tim10_samplingtime_ms;
float samplingtime_s;
uint32_t __debug_tim10_count__, __debug_tim10_count_2__;

/* only use in main.c */
void tim10_init()
{
	samplingtime_s = TIM10_TIME_MS / (float) 1000;
	tim10_samplingtime_ms = TIM10_TIME_MS;
	length_init(tim10_samplingtime_ms);
	section_length_init(tim10_samplingtime_ms);
	course_init(tim10_samplingtime_ms);
	velotrace_init(1);
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
	tim10_left = 0;
	tim10_right = 0;
	__debug_tim10_count__ = 0;
	__debug_tim10_count_2__ = 0;
	course_start();
	length_start();
	section_length_start();
	velotrace_start();
	slow_start(velotrace_read_values());
	HAL_TIM_Base_Start_IT(&htim10);
}

void tim10_stop()
{
	HAL_TIM_Base_Stop_IT(&htim10);
	velotrace_stop();
	section_length_stop();
	length_stop();
	course_stop();
}

void tim10_fin()
{
	length_fin();
	section_length_fin();
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_main()
{
	PlayMode rrpm;
	//! 角度をアップデートし続ける
	course_update_section_degree();
	//! 長さをアップデートし続ける
	length_update();
	//! 区間長をアップデートし続ける
	section_length_update();
	//! 速度制御の指令値をアップデートし続ける
	tim10_update_values();
	rrpm = rotary_read_playmode();
	__debug_tim10_count_2__ = __debug_tim10_count_2__ + 1;
#if 0	//! TIM6 に fixed_section_main() があり、そこで同じような処理をしているため飛ばす
	if(rrpm == search || rrpm == accel)
	{
		if(COURSE_SAMPLING_LENGTH < section_length_read())
		{
			//! 区間長の長さリセットは既にこの関数内に入っている
			course_state_function();
			__debug_tim10_count__ = __debug_tim10_count__ + 1;
		}
	}
#endif
	if(rotary_read_playmode() == velotrace_tuning_2)
	{
		if(virtual_marker_read_markerstate() == straight)
		{
			velotrace_gain_tuning();
		}
	}
}

//! tim10_main でのみ呼び出されるべき関数
//! 速度制御の指令値を更新する
void tim10_update_values()
{
#if USE_SLOWSTART
	if(rotary_read_playmode() == search)
	{
		slow_main();
	}
#endif

	tim10_left  = velotrace_solve(velocity_read());
	tim10_right = tim10_left;
}

float tim10_read_left()
{
	return tim10_left;
}

float tim10_read_right()
{
	return tim10_right;
}

void tim10_d_print()
{
#if D_TIM10
	// printf("tim10_left = %f, tim10_right = %f\r\n", tim10_left, tim10_right);
	// printf("__debug_tim10_count  __ = %16ld\r\n__debug_tim10_count_2__ = %16ld\r\n", __debug_tim10_count__, __debug_tim10_count_2__);
#endif
	length_d_print();
	course_d_print();
	velotrace_print_values();
	section_length_d_print();
	slow_print_default_pid();
}
