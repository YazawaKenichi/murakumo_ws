#include "tim6.h"

#if D_TIM6
MotorController motor;
// float motor.left, motor.right;
#endif

void tim6_init()
{
    motor_init();
    HAL_TIM_Base_Stop_IT(&htim6);
}

void tim6_start()
{
#if D_TIM6
    motor.left = 0;
    motor.right = 0;
    motor.left = 0;
    motor.right = 0;
#endif
    //! 速度補正
    fixed_section_start();
    motor_start();
	HAL_TIM_Base_Start_IT(&htim6);	// PID
}

void tim6_stop()
{
    motor_stop();
	HAL_TIM_Base_Stop_IT(&htim6);
    course_stop();
}

void tim6_main()
{
    PlayMode playmode;
    MotorController motor;

    playmode = rotary_read_playmode();

    #if LOCOMOTION_TEST
    odometry_update();
    #endif

    if(motor_read_enable() && playmode != motor_free)
    {
        #if !(TRACER_TUNING || VELOTRACE_TUNING)
        #if !LOCOMOTION_TEST // 起動追従のテストするときに無効
        switch(playmode)
        {
            case tracer_tuning:
                motor.left   = 0 + tim7_read_left();
                motor.right  = 0 + tim7_read_right();
                break;
            case velotrace_tuning:
                motor.left   = tim10_read_left() + 0;
                motor.right  = tim10_read_right() + 0;
                break;
            default:
                motor.left   = tim10_read_left() + tim7_read_left();
                motor.right  = tim10_read_right() + tim7_read_right();
                break;
        }
        #else // LOCOMOTION_TEST    // 起動追従のテストするときに有効になる
        //! 現在の速度と角速度を取得
        q_n = localization_get_twist();
        kcm_sample(q_n, &motor);
        #endif
        #else
        #if TRACER_TUNING
        motor.left  =  tim7_read_left();
        motor.right = tim7_read_right();
        #endif
        #if VELOTRACE_TUNING
        motor.left  =  tim10_read_left();
        motor.right = tim10_read_right();
        #endif
        #if VELOTRACE_TUNING && TRACER_TUNING
        motor.left  =  tim10_read_left() +  tim7_read_left();
        motor.right = tim10_read_right() + tim7_read_right();
        #endif
		#endif	/* !(TRACER_TUNING || VELOTRACE_TUNING) */
    }
    else
    {
        motor.left = 0;
        motor.right = 0;
    }

    if(course_read_state_count() + 1 == COURSE_STATE_SIZE)
    {
        switch_reset_enter();
        tim6_stop();
        motor_set(0, 0);
    }
    else
    {
        motor_set(motor.left, motor.right);
    }
}

void tim6_d_print()
{
    #if D_TIM6
    printf("\r\n");
    printf("tim6.c > tim6_d_print() > motor_enable = %1d, motor.left = %5.3f, motor.right = %5.3f\r\n", motor_read_enable(), motor.left, motor.right); 
    #endif
}
