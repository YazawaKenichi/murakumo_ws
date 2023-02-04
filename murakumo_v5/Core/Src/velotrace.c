#include "velotrace.h"

float velotrace_s_error;
float velotrace_before_error;
float velotrace_samplingtime;

PID velotrace_pid;

void velotrace_init(float samplingtime_)
{
    velotrace_samplingtime = samplingtime_;
}

void velotrace_start()
{
    #if D_VELOTRACE
    printf("velotrace_samplingtime = 1, velotrace_s_error = 0, velotrace_before_error = 0\r\n");
    #endif
    velotrace_s_error = 0;
    velotrace_before_error = 0;
    switch(rotary_read_playmode())
    {
        case search:
            velotrace_set_gain(0);
            velotrace_set_target(0);
            break;
        case velotrace_tuning:
            velotrace_set_target_zero();
            velotrace_set_gain(rotary_read_value());
            break;
        case tracer_tuning:
            velotrace_set_target_zero();
            velotrace_set_gain_zero();
        default:
            velotrace_set_gain(rotary_read_value());
            velotrace_set_target(rotary_read_value());
            break;
    }
}

void velotrace_stop()
{
    velotrace_set_target_zero();
    velotrace_set_gain_zero();
}

float velotrace_read_target(unsigned short int i)
{
    return VELOCITY_TARGET_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_TARGET_MAX - VELOCITY_TARGET_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

float velotrace_read_gain_kp(unsigned short int i)
{
    return VELOCITY_KP_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_KP_MAX - VELOCITY_KP_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

float velotrace_read_gain_ki(unsigned short int i)
{
    return VELOCITY_KI_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_KI_MAX - VELOCITY_KI_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

float velotrace_read_gain_kd(unsigned short int i)
{
    return VELOCITY_KD_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (float) (VELOCITY_KD_MAX - VELOCITY_KD_MIN) / (float) (VELOTRACE_STEP_SIZE - 1);
}

void velotrace_set_gain(unsigned short int i)
{
    #if D_VELOTRACE
    printf("velotrace_pid = velotrace_read_gain\r\n");
    #endif
    velotrace_pid.kp = velotrace_read_gain_kp(i);
    velotrace_pid.ki = velotrace_read_gain_ki(i);
    velotrace_pid.kd = velotrace_read_gain_kd(i);
}

void velotrace_set_target(unsigned short int i)
{
    #if D_VELOTRACE
    printf("velotrace_pid = velotrace_read_target\r\n");
    #endif
    velotrace_pid.target = velotrace_read_target(i);
}

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

void velotrace_set_gain_zero()
{
    velotrace_pid.kp = 0;
    velotrace_pid.ki = 0;
    velotrace_pid.kd = 0;
}

void velotrace_set_target_zero()
{
    velotrace_pid.target = 0;
}

float velotrace_solve(float reference_)
{
    float error;
    float d_error;
    float result;

    error = reference_ - velotrace_pid.target;

    d_error = (error - velotrace_before_error) / (float) velotrace_samplingtime;
    velotrace_s_error += error * (float) velotrace_samplingtime;

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
	printf("Velotrace\r\n");
	printf("target = %5.3f\r\n", velotrace_read_target(rotary_read_value()));
	printf("kp = %5.3f, ki = %5.3f, kd = %5.3f\r\n", velotrace_read_gain_kp(rotary_read_value()), velotrace_read_gain_ki(rotary_read_value()), velotrace_read_gain_kd(rotary_read_value()));
}
