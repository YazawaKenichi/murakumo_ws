#include "velotrace.h"

float velotrace_s_error;
float velotrace_before_error;
uint16_t velotrace_sampling_time_ms;
uint16_t velotrace_gain_tuning_time_ms;
PID velotrace_pid;
uint8_t velotrace_started;

/* pre setting */
void velotrace_init(uint16_t samplingtime_ms)
{
    velotrace_started = 0;
    velotrace_sampling_time_ms = samplingtime_ms;
}

void velotrace_start()
{
    if(velotrace_started <= 0)
    {
        float target, kp, ki, kd;
        #if D_VELOTRACE
        printf("velotrace_sampling_time_ms = 1, velotrace_s_error = 0, velotrace_before_error = 0\r\n");
        #endif
        velotrace_s_error = 0;
        velotrace_before_error = 0;
        velotrace_gain_tuning_time_ms = 0;
        switch(rotary_read_playmode())
        {
            case search:
            case accel:
                target = VELOCITY_TARGET_MIN;
                kp = 1000;
                ki = 100;
                kd = 0;
                break;
            case velotrace_tuning:
                target = 0;
                kp = velotrace_calc_gain_kp(rotary_read_value());
                ki = velotrace_calc_gain_ki(rotary_read_value());
                kd = velotrace_calc_gain_kd(rotary_read_value());
                break;
            case velotrace_tuning_2:
                target = VELOCITY_TARGET_MIN;
                kp = velotrace_calc_gain_kp(rotary_read_value());
                ki = velotrace_calc_gain_ki(rotary_read_value());
                kd = velotrace_calc_gain_kd(rotary_read_value());
                break;
            case tracer_tuning:
            default:
                target = 0;
                kp = 0;
                ki = 0;
                kd = 0;
                break;
        }
        velotrace_set_target_direct(target);
        velotrace_set_gain_direct(kp, ki, kd);
    }
    velotrace_started = 1;
}

void velotrace_stop()
{
    velotrace_set_target_zero();
    velotrace_set_gain_zero();
    velotrace_started = 0;
}

/* reading */
float velotrace_read_target()
{
    return velotrace_pid.target;
}

float velotrace_read_gain_kp()
{
    return velotrace_pid.kp;
}

float velotrace_read_gain_ki()
{
    return velotrace_pid.ki;
}

float velotrace_read_gain_kd()
{
    return velotrace_pid.kd;
}

/* target setting */
void velotrace_set_target_index(unsigned short int i)
{
    velotrace_pid.target = velotrace_calc_target(i);
}

void velotrace_set_target_direct(float target)
{
    velotrace_pid.target = target;
}

/* gain setting */
void velotrace_set_gain_kp_index(unsigned short int i)
{
    velotrace_set_gain_kp_direct(velotrace_calc_gain_kp(i));
}

void velotrace_set_gain_ki_index(unsigned short int i)
{
    velotrace_set_gain_ki_direct(velotrace_calc_gain_ki(i));
}

void velotrace_set_gain_kd_index(unsigned short int i)
{
    velotrace_set_gain_kd_direct(velotrace_calc_gain_kd(i));
}

void velotrace_set_gain_kp_direct(float kp)
{
    velotrace_pid.kp = kp;
}

void velotrace_set_gain_ki_direct(float ki)
{
    velotrace_pid.ki = ki;
}

void velotrace_set_gain_kd_direct(float kd)
{
    velotrace_pid.kd = kd;
}

void velotrace_set_gain_direct(float kp, float ki, float kd)
{
    velotrace_set_gain_kp_direct(kp);
    velotrace_set_gain_ki_direct(ki);
    velotrace_set_gain_kd_direct(kd);
}

/* target kp ki kd set zero */
void velotrace_set_target_zero()
{
    velotrace_set_target_direct(0);
}

void velotrace_set_gain_zero()
{
    velotrace_set_gain_kp_direct(0);
    velotrace_set_gain_ki_direct(0);
    velotrace_set_gain_kd_direct(0);
}

/* calclate pid values from rotary value */
float velotrace_calc_target(unsigned short int i)
{
    return VELOCITY_TARGET_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_TARGET_MAX - VELOCITY_TARGET_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

float velotrace_calc_gain_kp(unsigned short int i)
{
    return VELOCITY_KP_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_KP_MAX - VELOCITY_KP_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

float velotrace_calc_gain_ki(unsigned short int i)
{
    return VELOCITY_KI_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_KI_MAX - VELOCITY_KI_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

float velotrace_calc_gain_kd(unsigned short int i)
{
    return VELOCITY_KD_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_KD_MAX - VELOCITY_KD_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

/* all parameter */
void velotrace_set_values(PID *_pid)
{
    velotrace_pid.target = _pid->target;
    velotrace_pid.kp = _pid->kp;
    velotrace_pid.ki = _pid->ki;
    velotrace_pid.kd = _pid->kd;
}

PID* velotrace_read_values()
{
    return &velotrace_pid;
}

float velotrace_solve(float reference_)
{
    float error;
    float d_error;
    float result;

    error = reference_ - velotrace_pid.target;

    d_error = (error - velotrace_before_error) / (float) (velotrace_sampling_time_ms / (float) 1000);
    velotrace_s_error += error * (float) (velotrace_sampling_time_ms / (float) 1000);

    result = - (velotrace_pid.kp * error + velotrace_pid.ki * velotrace_s_error + velotrace_pid.kd * d_error);

    #if D_VELOTRACE_WHILE
    printf("velotrace_solve()\r\n");
    printf("reference_ - velotrace_pid.target = %7.2f - %7.2f = %7.2f\r\n", reference_, velotrace_pid.target, reference_ - velotrace_pid.target);
    printf("%7.2f = %7.2f * %7.2f + %7.2f * %7.2f + %7.2f * %7.2f\r\n", result, velotrace_pid.kp, error, velotrace_pid.ki, velotrace_s_error, velotrace_pid.kd, d_error);
    #endif

    velotrace_before_error = error;

    return result;
}

void velotrace_print_values()
{
#if D_VELOTRACE
	printf("Velotrace\r\n");
	printf("target = %5.3f\r\n", velotrace_read_target());
	//! printf("kp = %5.3f, ki = %5.3f, kd = %5.3f\r\n", velotrace_calc_gain_kp(rotary_read_value()), velotrace_calc_gain_ki(rotary_read_value()), velotrace_calc_gain_kd(rotary_read_value()));
#endif
}

void velotrace_gain_tuning()
{
    //! 右センサを読んでからの時間を格納する
    velotrace_gain_tuning_time_ms += velotrace_sampling_time_ms;
    //! 停止時間になったら
    if(velotrace_gain_tuning_time_ms >= VELOTRACE_GAIN_TUNING_STOP_TIME_MS)
    {
        //! 速度の目標値をゼロにする
        velotrace_pid.target = 0;
    }
}
