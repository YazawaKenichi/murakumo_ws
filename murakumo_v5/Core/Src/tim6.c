#include "tim6.h"

#if D_TIM6
MotorController motor;
// float motor.left, motor.right;
#endif

float tim6_angle;

void tim6_init()
{
    angletrace_init(1);    // [ ms ]
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
    //! 角度 PID
    angletrace_start();
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
    angletrace_stop();
}

void tim6_main()
{
    PlayMode playmode;
    MotorController motor;

    tim6_update_angle();

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
            case angletrace_tuning:
                motor.left  = - tim6_read_angle();
                motor.right = + tim6_read_angle();
                break;
            case kcm_tester:
                break;
            default:
                motor.left   = tim10_read_left()  + tim7_read_left()  - tim6_read_angle();
                motor.right  = tim10_read_right() + tim7_read_right() + tim6_read_angle();
                break;
        }
        #else // LOCOMOTION_TEST    // 起動追従のテストするときに有効になる
        //! 現在の速度と角速度を取得
        q_n = localization_get_twist();
        p_c = localization_get_pose();
        //! 出すべき（角）速度を取得
        q = kcm_sample(q_n, p_c);
        //! （角）速度からモータ出力に変換する（ここで（角）速度制御する）
        velocity_to_compare(&motor, q);
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

    if(course_read_state_count() + 1 >= COURSE_STATE_SIZE)
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
    angletrace_print_values();
}

/**
 * @brief 出力すべきあ値からモータの PWM 値に変換する
 * この中で（角）速度の PID 制御を行う
 * 
 * @param motor モータの PWM 値
 * @param q 出力すべき（角）速度
 */
void velocity_to_compare(MotorController *motor, Twist q)
{
    //! 出すべき前進速度
    float v = q.linear.x;
    //! 出すべき左旋回速度（ degree で角速度の PID できるようにしちゃったので degree に直す ）
    float w = q.angular.z * 180 / M_PI;

    //! （角）速度の目標値を教える
    //! 本来ここで（角）加速度を考慮する必要が出てくる
    velotrace_set_target_direct(v);
    angletrace_set_target_direct(w);

    //! 本当はここで一回 PID 指令値を計算しなくてはならない
    //! tim*_read_***() は tim*_update() で計算された指令値を読んでいるので最後に update されたタイミングの指令値を使って compare してしまう

    //! PID 制御する
    motor->left = tim10_read_left() - tim6_read_angle();
    motor->right = tim10_read_right() + tim6_read_angle();
}

void tim6_update_angle()
{
    tim6_angle = angletrace_solve(imu_read_yaw());
}

float tim6_read_angle()
{
    return tim6_angle;
}
