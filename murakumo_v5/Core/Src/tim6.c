#include "tim6.h"

float tim6_angle;

void tim6_init()
{
    //! 速度 PID プログラムの初期化
    velotrace_init(1);  // [ms]
    //! 姿勢 PID プログラムの初期化
    angletrace_init(1);    // [ ms ]
    //! 世界長管理プログラムの初期化
    length_init(1)  // [ms]
    //! 区間長の管理プログラムの初期化
    section_length_init(1)  // [ms]
    //! モータドライバの初期化
    motor_init();
    HAL_TIM_Base_Stop_IT(&htim6);
}

void tim6_start()
{
    //! 速度 PID
    velotrace_start();
    //! 角度 PID
    angletrace_start();
    //! 世界長管理プログラムのスタート
    length_start();
    //! 区間長管理プログラムのスタート
    section_length_start();
    //! モータドライバのスタート
    motor_start();
	HAL_TIM_Base_Start_IT(&htim6);
}

void tim6_stop()
{
	HAL_TIM_Base_Stop_IT(&htim6);
    //! モータのストップ
    motor_stop();
    //! 速度 PID のストップ
	velotrace_stop();
    //! 姿勢 PID のストップ
    angletrace_stop();
    //! 世界長管理プログラムのストップ
    length_stop();
    //! 区間長管理プログラムのストップ
	section_length_stop();
}

void tim6_main()
{
    PlayMode playmode;
    MotorController motor;

    playmode = rotary_read_playmode();
    odometry_update();

    if(motor_read_enable() && playmode != motor_free)
    {
        float reference_velocity, reference_angle;
        //! モータにとっての速度の単位に変換
        reference_velocity = velotrace_solve(velocity_read());
        reference_angle = angletrace_solve(imu_read_yaw());

        //! 指令値の重ね合わせ
        motor.left = reference_velocity - reference_angle;
        motor.right = reference_velocity + reference_angle;
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
 * @attention 使ってない
 * @brief 出力すべきあ値からモータの PWM 値に変換する
 * この中で（角）速度の PID 制御を行う
 * 
 * @param motor モータの PWM 値
 * @param q 出力すべき（角）速度
 */
void velocity_to_compare(MotorController *motor, Twist q)
{
    //! hoge
}

void tim6_update_angle()
{
    tim6_angle = angletrace_solve(imu_read_yaw());
}

float tim6_read_angle()
{
    return tim6_angle;
}
