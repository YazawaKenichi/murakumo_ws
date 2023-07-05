#include "angletrace.h"

float angletrace_s_error;
int angletrace_before_error;
uint16_t angletrace_sampling_time_ms;
uint16_t angletrace_gain_tuning_time_ms;
PID angletrace_pid;
uint8_t angletrace_started;

void angletrace_init(uint16_t samplingtime_ms)
{
    angletrace_sampling_time_ms = samplingtime_ms;
}

void angletrace_start()
{
    float target, kp, ki, kd;
    angletrace_s_error = 0;
    angletrace_before_error = 0;
    target = 0;
    kp = angletrace_calc_gain_kp(rotary_read_value());
    ki = angletrace_calc_gain_ki(rotary_read_value());
    kd = angletrace_calc_gain_kd(rotary_read_value());
    angletrace_set_target_direct(target);
    angletrace_set_gain_direct(kp, ki, kd);
    #if D_ANALOGTRACE
    printf("kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", kp, ki, kd);
    print_pid(&angletrace_pid);
    #endif
}

void angletrace_stop()
{
    angletrace_set_target_zero();
    angletrace_set_gain_zero();
}

/* reading */
float angletrace_read_target()
{
    return angletrace_pid.target;   //! [ rad / s ]
}

float angletrace_read_gain_kp()
{
    return angletrace_pid.kp;
}

float angletrace_read_gain_ki()
{
    return angletrace_pid.ki;
}

float angletrace_read_gain_kd()
{
    return angletrace_pid.kd;
}

/* target setting */
void angletrace_set_target_index(unsigned short int i)
{
    angletrace_pid.target = angletrace_calc_target(i);
}

void angletrace_set_target_direct(float target)
{
    angletrace_pid.target = target; //! [ rad / s ]
}

/* gain setting */
void angletrace_set_gain_kp_index(unsigned short int i)
{
    angletrace_set_gain_kp_direct(angletrace_calc_gain_kp(i));
}

void angletrace_set_gain_ki_index(unsigned short int i)
{
    angletrace_set_gain_ki_direct(angletrace_calc_gain_ki(i));
}

void angletrace_set_gain_kd_index(unsigned short int i)
{
    angletrace_set_gain_kd_direct(angletrace_calc_gain_kd(i));
}

void angletrace_set_gain_kp_direct(float kp)
{
    angletrace_pid.kp = kp;
}

void angletrace_set_gain_ki_direct(float ki)
{
    angletrace_pid.ki = ki;
}

void angletrace_set_gain_kd_direct(float kd)
{
    angletrace_pid.kd = kd;
}

void angletrace_set_gain_direct(float kp, float ki, float kd)
{
    angletrace_set_gain_kp_direct(kp);
    angletrace_set_gain_ki_direct(ki);
    angletrace_set_gain_kd_direct(kd);
}

/* target kp ki kd set zero */
void angletrace_set_target_zero()
{
    angletrace_set_target_direct(0);
}

void angletrace_set_gain_zero()
{
    angletrace_set_gain_kp_direct(0);
    angletrace_set_gain_ki_direct(0);
    angletrace_set_gain_kd_direct(0);
}

/* calclate pid values from rotary value */
float angletrace_calc_target(unsigned short int i)
{
    return ANGLE_TARGET_MAX - ((ANGLETRACE_STEP_SIZE - 1) - i) * (float) (ANGLE_TARGET_MAX - ANGLE_TARGET_MIN) / (float) (ANGLETRACE_STEP_SIZE - 1);
}

float angletrace_calc_gain_kp(unsigned short int i)
{
    return ANGLE_KP_MAX - ((ANGLETRACE_STEP_SIZE - 1) - i) * (float) (ANGLE_KP_MAX - ANGLE_KP_MIN) / (float) (ANGLETRACE_STEP_SIZE - 1);
}

float angletrace_calc_gain_ki(unsigned short int i)
{
    return ANGLE_KI_MAX - ((ANGLETRACE_STEP_SIZE - 1) - i) * (float) (ANGLE_KI_MAX - ANGLE_KI_MIN) / (float) (ANGLETRACE_STEP_SIZE - 1);
}

float angletrace_calc_gain_kd(unsigned short int i)
{
    return ANGLE_KD_MAX - ((ANGLETRACE_STEP_SIZE - 1) - i) * (float) (ANGLE_KD_MAX - ANGLE_KD_MIN) / (float) (ANGLETRACE_STEP_SIZE - 1);
}

/* all parameter */
void angletrace_set_values(PID *_pid)
{
    angletrace_pid.target = _pid->target;   //! [ rad / s ]
    angletrace_pid.kp = _pid->kp;
    angletrace_pid.ki = _pid->ki;
    angletrace_pid.kd = _pid->kd;
}

PID* angletrace_read_values()
{
    return &angletrace_pid;
}

float angletrace_solve(float reference_rad)
{
    float error;
    float d_error;
    float result;

    error = reference_rad - angletrace_pid.target;

    d_error = (error - angletrace_before_error) / (float) (angletrace_sampling_time_ms / (float) 1000);
    angletrace_s_error += error * (float) (angletrace_sampling_time_ms / (float) 1000);

    result = - (angletrace_pid.kp * error + angletrace_pid.ki * angletrace_s_error + angletrace_pid.kd * d_error);

    #if D_ANALOGTRACE_WHILE
    printf("angletrace_solve()\r\n");
    printf("reference_ - angletrace_pid.target = %7.2f - %7.2f = %7.2f\r\n", reference_, angletrace_pid.target, reference_ - angletrace_pid.target);
    printf("%7.2f = %7.2f * %7.2f + %7.2f * %7.2f + %7.2f * %7.2f\r\n", result, angletrace_pid.kp, error, angletrace_pid.ki, angletrace_s_error, angletrace_pid.kd, d_error);
    #endif

    angletrace_before_error = error;

    return result * 180 / M_PI;
}

void angletrace_print_values()
{
#if D_ANALOGTRACE
	printf("velo > target = %5.3f\r\n", angletrace_read_target());
	//! printf("kp = %5.3f, ki = %5.3f, kd = %5.3f\r\n", angletrace_calc_gain_kp(rotary_read_value()), angletrace_calc_gain_ki(rotary_read_value()), angletrace_calc_gain_kd(rotary_read_value()));
#endif
}

void angletrace_gain_tuning()
{
    //! 右センサを読んでからの時間を格納する
    angletrace_gain_tuning_time_ms += angletrace_sampling_time_ms;
    //! 停止時間になったら
    if(angletrace_gain_tuning_time_ms >= ANGLETRACE_GAIN_TUNING_STOP_TIME_MS)
    {
        //! 速度の目標値をゼロにする
        angletrace_pid.target = 0;
    }
}
