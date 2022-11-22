#include "tim11.h"

uint8_t rotary_value;

void tim11_init()
{
    switch_init();
	HAL_TIM_Base_Start_IT(&htim11);	// 1ms	// ROTARY SWITCH
    rotary_init();
}

void tim11_main()
{
    switch_enter();
    rotary_set_value();
}
