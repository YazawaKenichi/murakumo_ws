#include "tim11.h"

uint8_t rotary_value;

void tim11_init()
{
    time_init();
    switch_init();
    rotary_init();
    analog_init();
    encoder_init();
    imu_init();
	HAL_TIM_Base_Start_IT(&htim11);	// 1ms	// ROTARY SWITCH
}

void tim11_start()
{
    time_start();
    analog_start();
    encoder_start();
    imu_start();
}

void tim11_stop()
{
    time_stop();
    analog_stop();
    encoder_stop();
    imu_stop();
}

void tim11_main()
{
    //! 1ms
    time_update(0.001f);
    switch_update();
    rotary_update();
    analog_update();
    encoder_update();
    imu_update_accel();
    imu_update_gyro();
}

void tim11_d_print()
{
}
