#include "tim10.h"

/* lengths is updated only in tim10 file. */
float length, length_left, length_right;
float velocity_left, velocity_right, velocity;
float tim10_left, tim10_right;
unsigned int samplingtime_ms;
float samplingtime_s;

/* only use in main.c */
void tim10_init()
{
	samplingtime_s = TIM10_TIME_MS / (float) 1000;
	samplingtime_ms = TIM10_TIME_MS;
	length_init(samplingtime_ms);
	section_length_init(samplingtime_ms);
	course_init(samplingtime_ms);
	velotrace_init(1);
	HAL_TIM_Base_Stop_IT(&htim10);
}

void tim10_start()
{
	tim10_left = 0;
	tim10_right = 0;
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
	//! 角度をアップデートし続ける
	course_update_section_degree();
	//! 長さをアップデートし続ける
	length_update();
	//! 区間長をアップデートし続ける
	section_length_update();
	//! 速度制御の指令値をアップデートし続ける
	tim10_update_values();
	if(rotary_read_playmode() == velotrace_tuning)
	{
		if(sidesensor_read_markerstate() == straight)
		{
			velotrace_gain_tuning();
		}
	}
}

//! tim10_main でのみ呼び出されるべき関数
//! 速度制御の指令値を更新する
void tim10_update_values()
{
	/* slow start のプログラムいれたけど、できないよ！ */
	#if USE_SLOWSTART
	if(slow_read_enable())
	{
		//! 
		slow_set_velocity(velocity);
		slow_main();
		//! slow で設定された目標速度と PID ゲイン値を velotrace に渡す
		velotrace_set_values(slow_read_gain_values());
	}
	#endif

	tim10_left  = velotrace_solve(velocity_read());
	tim10_right = tim10_left;
}

 /*
	if(length >= SAMPLING_LENGTH)
	{
		course_state_function();
	}
 */

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
	length_d_print();
	course_d_print();
	velotrace_print_values();
	section_length_d_print();
}
