#include "tracer.h"

double s_error;
int before_error;
double samplingtime;

PID tracer_pid;

void tracer_start()
{
    tracer_init(1);
    tracer_set_gain(rotary_read_value());
    tracer_set_target(0);
    #if D_TRACER
    printf("tracer.c > tracer_start > ");
    printf("target = %5.2f\r\n", tracer_pid.target);
    printf("tracer.c > tracer_start > ");
    printf("kp = %7.3f, ki = %7.3f, kd = %7.3f\r\n", tracer_pid.kp, tracer_pid.ki, tracer_pid.kd);
    #endif
}

void tracer_init(double samplingtime_)
{
    #if D_TRACER
    printf("tracer.c > ");
    printf("tracer_init > ");
    printf("sampling_time = 1, s_error = 0, before_error = 0\r\n");
    #endif
    samplingtime = samplingtime_;
    s_error = 0;
    before_error = 0;
}

double tracer_read_gain_kp(unsigned short int i)
{
    return TRACER_KP_MAX - ((TRACER_STEP_SIZE - 1) - i) * (double) (TRACER_KP_MAX - TRACER_KP_MIN) / (double) (TRACER_STEP_SIZE - 1);
}

double tracer_read_gain_ki(unsigned short int i)
{
    return TRACER_KI_MAX - ((TRACER_STEP_SIZE - 1) - i) * (double) (TRACER_KI_MAX - TRACER_KI_MIN) / (double) (TRACER_STEP_SIZE - 1);
}

double tracer_read_gain_kd(unsigned short int i)
{
    return TRACER_KD_MAX - ((TRACER_STEP_SIZE - 1) - i) * (double) (TRACER_KD_MAX - TRACER_KD_MIN) / (double) (TRACER_STEP_SIZE - 1);
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
    printf("kp = %7.3f, ki = %7.3f, kd = %7.3f\r\n", tracer_pid.kp, tracer_pid.ki, tracer_pid.kd);
    #endif
}

void tracer_set_target(double target_)
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

double tracer_solve(int reference_)
{
    int error;
    double d_error;
    double result;

    error = reference_ - tracer_pid.target;

    d_error = error - before_error / samplingtime;
    s_error += error * samplingtime;

    result = tracer_pid.kp * error + tracer_pid.ki * s_error + tracer_pid.kd * d_error;

    before_error = error;

    return result;
}

double tracer_solve_with_gain(int reference_, double kp_, double ki_, double kd_)
{
    int error;
    int d_error;
    double result;

    error = reference_;

    d_error = error - before_error;
    s_error += error;

    result = kp_ * error + ki_ * s_error * samplingtime + kd_ * d_error / samplingtime;

    before_error = error;

    return result;
}

void tracer_d_print()
{
    printf("tracer.c > tracer_d_print() > target = %5d, kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", 0, tracer_read_gain_kp(0), tracer_read_gain_ki(0), tracer_read_gain_kd(0));
    printf("tracer.c > tracer_d_print() > before_error = %5d, s_error = %7.2f\r\n", before_error, s_error);
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
