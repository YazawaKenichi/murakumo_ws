#include "tracer.h"

float tracer_s_error;
int tracer_before_error;
float tracer_samplingtime;

PID tracer_pid;

void tracer_start()
{
    tracer_s_error = 0;
    tracer_before_error = 0;
    tracer_set_gain(rotary_read_value());
    tracer_set_target(0);
    #if D_TRACER
    printf("tracer.c > tracer_start > ");
    printf("target = %5.2f\r\n", tracer_pid.target);
    printf("tracer.c > tracer_start > ");
    printf("kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", tracer_pid.kp, tracer_pid.ki, tracer_pid.kd);
    #endif
}

void tracer_stop()
{
    tracer_set_target_zero();
    tracer_set_gain_zero();
}

void tracer_init(float samplingtime_)
{
    #if D_TRACER
    printf("tracer.c > ");
    printf("tracer_init > ");
    printf("sampling_time = 1, tracer_s_error = 0, tracer_before_error = 0\r\n");
    #endif
    tracer_samplingtime = samplingtime_;
}

void tracer_set_gain_zero()
{
    tracer_pid.target = 0;
}

void tracer_set_target_zero()
{
    tracer_pid.kp = 0;
    tracer_pid.ki = 0;
    tracer_pid.kd = 0;
}

float tracer_read_gain_kp(unsigned short int i)
{
    return TRACER_KP_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KP_MAX - TRACER_KP_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

float tracer_read_gain_ki(unsigned short int i)
{
    return TRACER_KI_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KI_MAX - TRACER_KI_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

float tracer_read_gain_kd(unsigned short int i)
{
    return TRACER_KD_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KD_MAX - TRACER_KD_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

void tracer_set_gain(unsigned short int i)
{
    #if D_TRACER
    printf("tracer.c > ");
    printf("tracer_set_gain() > ");
    #endif
    tracer_pid.kp = tracer_read_gain_kp(i);
    tracer_pid.ki = tracer_read_gain_ki(i);
    tracer_pid.kd = tracer_read_gain_kd(i);
    #if D_TRACER
    printf("kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", tracer_pid.kp, tracer_pid.ki, tracer_pid.kd);
    #endif
}

void tracer_set_target(float target_)
{
    #if D_TRACER
    printf("tracer.c > ");
    printf("tracer_set_target() > ");
    #endif
    tracer_pid.target = target_;
    #if D_TRACER
    printf("target_ = %5.2f, target = %5.2f\r\n", target_, tracer_pid.target);
    #endif
}

float tracer_solve(int reference_)
{
    int error;
    float d_error;
    float result;

    #if D_TRACER_WHILE
    printf("tracer.c > tracer_solve() > ");
    printf("reference_ = %5d\r\n", reference_);
    #endif

    error = reference_;

    d_error = (error - tracer_before_error) / (float) tracer_samplingtime;
    tracer_s_error += error * (float) tracer_samplingtime;

    result = tracer_pid.kp * error + tracer_pid.ki * tracer_s_error + tracer_pid.kd * d_error;

    #if D_TRACER_WHILE
    printf("tracer.c > tracer_solve() > ");
    printf("%7.2f = %7.2f * %5d + %7.2f * %7.2f + %7.2f * %7.2f\r\n", result, tracer_pid.kp, error, tracer_pid.ki, tracer_s_error, tracer_pid.kd, d_error);
    #endif

    tracer_before_error = error;

    return result;
}

float tracer_solve_with_gain(int reference_, float kp_, float ki_, float kd_)
{
    int error;
    int d_error;
    float result;

    error = reference_;

    d_error = error - tracer_before_error;
    tracer_s_error += error;

    result = kp_ * error + ki_ * tracer_s_error * tracer_samplingtime + kd_ * d_error / tracer_samplingtime;

    tracer_before_error = error;

    return result;
}

void tracer_d_print()
{
    printf("tracer.c > tracer_d_print() > target = %5d, kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", 0, tracer_read_gain_kp(0), tracer_read_gain_ki(0), tracer_read_gain_kd(0));
    printf("tracer.c > tracer_d_print() > tracer_before_error = %5d, tracer_s_error = %7.2f\r\n", tracer_before_error, tracer_s_error);
}

void tracer_print_values()
{
	printf("Tracer\r\n");
	printf("target = 0\r\n");
	printf("kp = %5.3f, ki = %5.3f, kd = %5.3f\r\n", tracer_read_gain_kp(rotary_read_value()), tracer_read_gain_ki(rotary_read_value()), tracer_read_gain_kd(rotary_read_value()));
}

/*
PID tracer_read()
{
    return pid;
}
*/

/*
void tracer_set(PID pid_)
{
    pid = pid_;
}
*/
