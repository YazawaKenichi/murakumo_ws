#include "velotrace_right.h"

double velotrace_right_s_error;
float velotrace_right_before_error;
uint16_t velotrace_right_sampling_time_ms;
uint16_t velotrace_right_gain_tuning_time_ms;
PID velotrace_right_pid;

/* pre setting */
void velotrace_right_init(uint16_t samplingtime_ms)
{
    velotrace_right_sampling_time_ms = samplingtime_ms;
}

void velotrace_right_start()
{
    float target, kp, ki, kd;
    velotrace_right_s_error = 0;
    velotrace_right_before_error = 0;
    velotrace_right_gain_tuning_time_ms = 0;

    target = velotrace_right_calc_target(rotary_read());
    kp = velotrace_right_calc_gain_kp(rotary_read());
    ki = velotrace_right_calc_gain_ki(rotary_read());
    kd = velotrace_right_calc_gain_kd(rotary_read());

    velotrace_right_set_target_direct(target);
    velotrace_right_set_gain_direct(kp, ki, kd);
}

void velotrace_right_stop()
{
    velotrace_right_set_target_zero();
    velotrace_right_set_gain_zero();
}

/* reading */
float velotrace_right_read_target()
{
    return velotrace_right_pid.target;
}

float velotrace_right_read_gain_kp()
{
    return velotrace_right_pid.kp;
}

float velotrace_right_read_gain_ki()
{
    return velotrace_right_pid.ki;
}

float velotrace_right_read_gain_kd()
{
    return velotrace_right_pid.kd;
}

/* target setting */
void velotrace_right_set_target_index(unsigned short int i)
{
    velotrace_right_pid.target = velotrace_right_calc_target(i);
}

void velotrace_right_set_target_direct(float target)
{
    velotrace_right_pid.target = target;
}

/* gain setting */
void velotrace_right_set_gain_kp_index(unsigned short int i)
{
    velotrace_right_set_gain_kp_direct(velotrace_right_calc_gain_kp(i));
}

void velotrace_right_set_gain_ki_index(unsigned short int i)
{
    velotrace_right_set_gain_ki_direct(velotrace_right_calc_gain_ki(i));
}

void velotrace_right_set_gain_kd_index(unsigned short int i)
{
    velotrace_right_set_gain_kd_direct(velotrace_right_calc_gain_kd(i));
}

void velotrace_right_set_gain_kp_direct(float kp)
{
    velotrace_right_pid.kp = kp;
}

void velotrace_right_set_gain_ki_direct(float ki)
{
    velotrace_right_pid.ki = ki;
}

void velotrace_right_set_gain_kd_direct(float kd)
{
    velotrace_right_pid.kd = kd;
}

void velotrace_right_set_gain_direct(float kp, float ki, float kd)
{
    velotrace_right_set_gain_kp_direct(kp);
    velotrace_right_set_gain_ki_direct(ki);
    velotrace_right_set_gain_kd_direct(kd);
}

/* target kp ki kd set zero */
void velotrace_right_set_target_zero()
{
    velotrace_right_set_target_direct(0);
}

void velotrace_right_set_gain_zero()
{
    velotrace_right_set_gain_kp_direct(0);
    velotrace_right_set_gain_ki_direct(0);
    velotrace_right_set_gain_kd_direct(0);
}

/* calclate pid values from rotary value */
float velotrace_right_calc_target(unsigned short int i)
{
    return VELOCITY_RIGHT_TARGET_MAX - ((VELOTRACE_RIGHT_STEP_SIZE - 1) - i) * (float) (VELOCITY_RIGHT_TARGET_MAX - VELOCITY_RIGHT_TARGET_MIN) / (float) (VELOTRACE_RIGHT_STEP_SIZE - 1);
}

float velotrace_right_calc_gain_kp(unsigned short int i)
{
    return VELOCITY_RIGHT_KP_MAX - ((VELOTRACE_RIGHT_STEP_SIZE - 1) - i) * (float) (VELOCITY_RIGHT_KP_MAX - VELOCITY_RIGHT_KP_MIN) / (float) (VELOTRACE_RIGHT_STEP_SIZE - 1);
}

float velotrace_right_calc_gain_ki(unsigned short int i)
{
    return VELOCITY_RIGHT_KI_MAX - ((VELOTRACE_RIGHT_STEP_SIZE - 1) - i) * (float) (VELOCITY_RIGHT_KI_MAX - VELOCITY_RIGHT_KI_MIN) / (float) (VELOTRACE_RIGHT_STEP_SIZE - 1);
}

float velotrace_right_calc_gain_kd(unsigned short int i)
{
    return VELOCITY_RIGHT_KD_MAX - ((VELOTRACE_RIGHT_STEP_SIZE - 1) - i) * (float) (VELOCITY_RIGHT_KD_MAX - VELOCITY_RIGHT_KD_MIN) / (float) (VELOTRACE_RIGHT_STEP_SIZE - 1);
}

/* all parameter */
void velotrace_right_set_values(PID *_pid)
{
    velotrace_right_pid.target = _pid->target;
    velotrace_right_pid.kp = _pid->kp;
    velotrace_right_pid.ki = _pid->ki;
    velotrace_right_pid.kd = _pid->kd;
}

PID* velotrace_right_read_values()
{
    return &velotrace_right_pid;
}

float velotrace_right_solve(float reference_)
{
    float error;
    float d_error;
    float result;

    error = reference_ - velotrace_right_pid.target;

    d_error = (error - velotrace_right_before_error) / (float) (velotrace_right_sampling_time_ms / (float) 1000);
    velotrace_right_s_error += error * (float) (velotrace_right_sampling_time_ms / (float) 1000);

    result = - (velotrace_right_pid.kp * error + velotrace_right_pid.ki * velotrace_right_s_error + velotrace_right_pid.kd * d_error);

    velotrace_right_before_error = error;

    return result;
}

void velotrace_right_d_print()
{
#if D_VELOTRACE
	printf("velo > target = %5.3f\r", velotrace_right_read_target());
#endif
}

void velotrace_right_gain_tuning()
{
    //! 右センサを読んでからの時間を格納する
    velotrace_right_gain_tuning_time_ms += velotrace_right_sampling_time_ms;
    //! 停止時間になったら
    if(velotrace_right_gain_tuning_time_ms >= VELOTRACE_RIGHT_GAIN_TUNING_STOP_TIME_MS)
    {
        //! 速度の目標値をゼロにする
        velotrace_right_pid.target = 0;
    }
}
