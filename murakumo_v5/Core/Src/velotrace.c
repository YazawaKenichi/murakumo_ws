#include "velotrace.h"

double s_error;
double before_error;
double samplingtime;

PID pid;

void velotrace_init(double samplingtime_)
{
    samplingtime = samplingtime_;
}

void velotrace_start()
{
    #if D_VELOTRACE
    printf("samplingtime = 1, s_error = 0, before_error = 0\r\n");
    #endif
    s_error = 0;
    before_error = 0;
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

double velotrace_read_target(unsigned short int i)
{
    return VELOCITY_TARGET_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (double) (VELOCITY_TARGET_MAX - VELOCITY_TARGET_MIN) / (double) (VELOTRACE_STEP_SIZE - 1);
}

double velotrace_read_gain_kp(unsigned short int i)
{
    return VELOCITY_KP_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (double) (VELOCITY_KP_MAX - VELOCITY_KP_MIN) / (double) (VELOTRACE_STEP_SIZE - 1);
}

double velotrace_read_gain_ki(unsigned short int i)
{
    return VELOCITY_KI_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (double) (VELOCITY_KI_MAX - VELOCITY_KI_MIN) / (double) (VELOTRACE_STEP_SIZE - 1);
}

double velotrace_read_gain_kd(unsigned short int i)
{
    return VELOCITY_KD_MAX - ((VELOTRACE_STEP_SIZE - 1) - i) * (double) (VELOCITY_KD_MAX - VELOCITY_KD_MIN) / (double) (VELOTRACE_STEP_SIZE - 1);
}

void velotrace_set_gain(unsigned short int i)
{
    #if D_VELOTRACE
    printf("pid = velotrace_read_gain\r\n");
    #endif
    pid.kp = velotrace_read_gain_kp(i);
    pid.ki = velotrace_read_gain_ki(i);
    pid.kd = velotrace_read_gain_kd(i);
}

void velotrace_set_target(unsigned short int i)
{
    #if D_VELOTRACE
    printf("pid = velotrace_read_target\r\n");
    #endif
    pid.target = velotrace_read_target(i);
}

void velotrace_set_gain_zero()
{
    pid.kp = 0;
    pid.ki = 0;
    pid.kd = 0;
}

void velotrace_set_target_zero()
{
    pid.target = 0;
}

double velotrace_solve(double reference_)
{
    double error;
    double d_error;
    double result;

    error = reference_ - pid.target;

    d_error = (error - before_error) / (double) samplingtime;
    s_error += error * (double) samplingtime;

    result = - (pid.kp * error + pid. ki * s_error + pid.kd * d_error);

    #if D_TIM6_WHILE
    printf("velotrace_solve()\r\n");
    printf("reference_ = %5d\r\n");
    printf("%7.2f = %7.2f * %5d + %7.2f * %7.2f + %7.2f * %7.2f\r\n", result, pid.kp, error, pid.ki, s_error, pid.kd, d_error);
    #endif

    before_error = error;

    return result;
}

void velotrace_print_values()
{
	printf("Velotrace\r\n");
	printf("target = %5.3f\r\n", velotrace_read_target(rotary_read_value()));
	printf("kp = %5.3f, ki = %5.3f, kd = %5.3f\r\n", velotrace_read_gain_kp(rotary_read_value()), velotrace_read_gain_ki(rotary_read_value()), velotrace_read_gain_kd(rotary_read_value()));
}
