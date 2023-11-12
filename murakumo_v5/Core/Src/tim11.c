#include "tim11.h"

uint8_t tim11_started;

void tim11_init()
{
    printf("tim11_init()\r\n");
    tim11_started = 0;
    time_init();
    switch_init();
    rotary_init();
    sidesensor_init();
    analog_init();
    encoder_init();
    imu_init();
    HAL_TIM_Base_Start_IT(&htim11);	// 1ms	// ROTARY SWITCH
}

void tim11_start()
{
    time_start();
    sidesensor_start();
    analog_start();
    encoder_start();
    imu_start();
    tim11_started = 1;
}

void tim11_stop()
{
    time_stop();
    sidesensor_stop();
    analog_stop();
    encoder_stop();
    imu_stop();
    tim11_started = 0;
}

void tim11_main()
{
    //! 1ms
    time_update(0.001f);
    switch_update();
    rotary_update();
    sidesensor_main();
    if(tim11_started == 1)
    {
        analog_update();
        encoder_update();
        imu_update_accel();
        imu_update_gyro();
    }
}

void tim11_d_print()
{
    encoder_d_print();
}

void tim11_d_print_main()
{
    encoder_d_print_main();
}
