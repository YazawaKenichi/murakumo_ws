#include "motor.h"

char enable;

void motor_init()
{
    motor_enable(0);
}

void motor_start()
{
    #if D_MOTOR
    printf("HAL_TIM_PWM_Start, motor_enable(1)\r\n");
    #endif
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);	// 50kHz (0.02ms)
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
#if PLAY
    motor_enable(1);
#endif
}

void motor_stop()
{
    motor_enable(0);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
}

void motor_enable(uint8_t enable_)
{
    enable = enable_ ? 1 : 0;
}

char motor_read_enable()
{
    return enable;
}

void motor_set(double motor_left_, double motor_right_)
{
    if(motor_left_ < 0)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
        motor_left_ = motor_left_ * -1;
    }
    else
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    }

    if(motor_right_ < 0)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        motor_right_ = motor_right_ * -1;
    }
    else
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    }

    motor_left_ = motor_left_ > PWMMAX ? PWMMAX : motor_left_;
    motor_right_ = motor_right_ > PWMMAX ? PWMMAX : motor_right_;

    if(!enable)
    {
        motor_left_ = 0;
        motor_right_ = 0;
    }

    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, motor_left_);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, motor_right_);
}

/* usuage */
/*
    run_init()
    {
        ...
        tracer_init();
        tracer_set_gain(10, 8, 2);
        tracer_set_target(0);
        ...
    }

    in_timer()
    {
        ...
        motor_set(velotrace_solve(velocityvalue) + tracer_solve(sensorvalue), velotrace_solve(velocityvalue) + tracer_solve(sensorvalue));
        ...
    }
*/

