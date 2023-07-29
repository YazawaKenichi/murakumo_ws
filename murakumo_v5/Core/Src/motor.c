#include "motor.h"

char enable;
Motor mot_buf;

void motor_init()
{
    motor_enable(0);
}

void motor_start()
{
    mot_buf.left = 0;
    mot_buf.right = 0;
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

char motor_read_enable()
{
    return enable;
}

void motor_enable(uint8_t enable_)
{
    enable = enable_ ? 1 : 0;
}

void motor_set(float motor_left_, float motor_right_)
{
    motor_left_ = low_pass_filter(motor_left_, mot_buf.left, 0.25f);
    motor_right_ = low_pass_filter(motor_right_, mot_buf.right, 0.25f);

    mot_buf.left = motor_left_;
    mot_buf.right = motor_right_;

    if(motor_left_ < 0)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    }

    if(motor_right_ < 0)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    }

    motor_left_ = fabs(motor_left_);
    motor_right_ = fabs(motor_right_);

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

void motor_d_print()
{
#if D_MOTOR
    printf("motlef, motrig\r\n");
    for(uint8_t index = 0; index < 30; index++)
    {
        printf("%6.3lf, %6.3lf\r\n", mot_buf.left, mot_buf.right);
    }
#endif
}
