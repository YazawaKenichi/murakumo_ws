#include "tracer.h"

float tracer_s_error;
int tracer_before_error;
uint16_t tracer_sampling_time_ms;
PID tracer_pid;
PID tracer_default;

void tracer_init(float samplingtime_ms)
{
    tracer_sampling_time_ms = samplingtime_ms;
}

void tracer_start()
{
    float kp, ki, kd;
    tracer_s_error = 0;
    tracer_before_error = 0;
    kp = tracer_calc_gain_kp(rotary_read());
    ki = tracer_calc_gain_ki(rotary_read());
    kd = tracer_calc_gain_kd(rotary_read());
    tracer_set_default_now_gain(kp, ki, kd);
    tracer_set_target_zero();
    tracer_set_gain_direct(kp, ki, kd);
    #if D_TRACER
    printf("kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", kp, ki, kd);
    print_pid(&tracer_pid);
    #endif
}

void tracer_stop()
{
    tracer_set_gain_zero();
}

/* reading */
float tracer_read_gain_kp()
{
    return tracer_pid.kp;
}

float tracer_read_gain_ki()
{
    return tracer_pid.ki;
}

float tracer_read_gain_kd()
{
    return tracer_pid.kd;
}

/* target setting */
void tracer_set_gain_kp_index(unsigned short int i)
{
    tracer_set_gain_kp_direct(tracer_calc_gain_kp(i));
}

void tracer_set_gain_ki_index(unsigned short int i)
{
    tracer_set_gain_ki_direct(tracer_calc_gain_ki(i));
}

void tracer_set_gain_kd_index(unsigned short int i)
{
    tracer_set_gain_kd_direct(tracer_calc_gain_kd(i));
}

void tracer_set_gain_kp_direct(float kp)
{
    tracer_pid.kp = kp;
}

void tracer_set_gain_ki_direct(float ki)
{
    tracer_pid.ki = ki;
}

void tracer_set_gain_kd_direct(float kd)
{
    tracer_pid.kd = kd;
}

void tracer_set_gain_direct(float kp, float ki, float kd)
{
    tracer_set_gain_kp_direct(kp);
    tracer_set_gain_ki_direct(ki);
    tracer_set_gain_kd_direct(kd);
}

/* kp ki kd set zero */
void tracer_set_target_zero()
{
    tracer_pid.target = 0;
}

void tracer_set_gain_zero()
{
    tracer_pid.kp = 0;
    tracer_pid.ki = 0;
    tracer_pid.kd = 0;
}

/* calclate pid values from rotary value */
float tracer_calc_gain_kp(unsigned short int i)
{
    return TRACER_KP_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KP_MAX - TRACER_KP_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

float tracer_calc_gain_ki(unsigned short int i)
{
    return TRACER_KI_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KI_MAX - TRACER_KI_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

float tracer_calc_gain_kd(unsigned short int i)
{
    return TRACER_KD_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KD_MAX - TRACER_KD_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

/* set default */
void tracer_set_gain_default()
{
    tracer_pid = tracer_default;
}

void tracer_set_default_now_gain(float kp, float ki, float kd)
{
    tracer_default.target = 0;
    tracer_default.kp = kp;
    tracer_default.ki = ki;
    tracer_default.kd = kd;
}

/* all parameter */
void tracer_set_values(PID *_pid)
{
    tracer_set_target_zero();
    tracer_pid.kp = _pid->kp;
    tracer_pid.ki = _pid->ki;
    tracer_pid.kd = _pid->kd;
}

PID* tracer_read_values()
{
    return &tracer_pid;
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

    error = reference_ - tracer_pid.target;

    d_error = (error - tracer_before_error) / (float) (tracer_sampling_time_ms / (float) 1000);
    tracer_s_error += error * (float) (tracer_sampling_time_ms / (float) 1000);

    result = tracer_pid.kp * error + tracer_pid.ki * tracer_s_error + tracer_pid.kd * d_error;

    #if D_TRACER_WHILE
    printf("tracer.c > tracer_solve() > ");
    printf("%7.2f = %7.2f * %5d + %7.2f * %7.2f + %7.2f * %7.2f\r\n", result, tracer_pid.kp, error, tracer_pid.ki, tracer_s_error, tracer_pid.kd, d_error);
    #endif

    tracer_before_error = error;

    return result;
}

void tracer_d_print()
{
#if D_TRACER
    printf("trac > kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", tracer_pid.kp, tracer_pid.ki, tracer_pid.kd);
#endif
}

void tracer_gain_tuning()
{
    /* tracer_gain_tuning */
}


