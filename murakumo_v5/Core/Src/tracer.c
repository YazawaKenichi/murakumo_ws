#include "tracer.h"

float tracer_s_error;
int tracer_before_error;
float tracer_samplingtime;
PID tracer_pid;
uint8_t started;

void tracer_init(float samplingtime_ms)
{
    started = 0;
    tracer_samplingtime = samplingtime_ms;
}

void tracer_start()
{
    if(started <= 0)
    {
        float kp, ki, kd;
        tracer_s_error = 0;
        tracer_before_error = 0;
        kp = tracer_calc_gain_kp(rotary_read_value());
        ki = tracer_calc_gain_ki(rotary_read_value());
        kd = tracer_calc_gain_kd(rotary_read_value());
        tracer_set_target_zero();
        tracer_set_gain_direct(kp, ki, kd);
    }
    started = 1;
}

void tracer_stop()
{
    tracer_set_gain_zero();
    started = 0;
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
    tracer_pid.kp = ki;
}

void tracer_set_gain_kd_direct(float kd)
{
    tracer_pid.kp = kd;
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

void tracer_print_values()
{
#if D_TRACER
#endif
}

void tracer_gain_tuning()
{
    /* tracer_gain_tuning */
}


