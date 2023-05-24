#include "tracer.h"

float angletracer_s_error;
int angletracer_before_error;
uint16_t angletracer_sampling_time_ms;
PID angletracer_pid;
PID angletracer_default;
uint8_t angletracer_started;

void angletracer_init(float samplingtime_ms)
{
    angletracer_started = 0;
    angletracer_sampling_time_ms = samplingtime_ms;
}

void angletracer_start()
{
    if(angletracer_started <= 0)
    {
        float kp, ki, kd;
        angletracer_s_error = 0;
        angletracer_before_error = 0;
        kp = angletracer_calc_gain_kp(rotary_read_value());
        ki = angletracer_calc_gain_ki(rotary_read_value());
        kd = angletracer_calc_gain_kd(rotary_read_value());
        angletracer_set_default_now_gain(kp, ki, kd);
        angletracer_set_target_zero();
        angletracer_set_gain_direct(kp, ki, kd);
    #if D_TRACER
        printf("kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", kp, ki, kd);
        print_pid(&angletracer_pid);
    #endif
    }
    angletracer_started = 1;
}

void angletracer_stop()
{
    angletracer_set_gain_zero();
    angletracer_started = 0;
}

/* reading */
float angletracer_read_gain_kp()
{
    return angletracer_pid.kp;
}

float angletracer_read_gain_ki()
{
    return angletracer_pid.ki;
}

float angletracer_read_gain_kd()
{
    return angletracer_pid.kd;
}

/* target setting */
void angletracer_set_gain_kp_index(unsigned short int i)
{
    angletracer_set_gain_kp_direct(tracer_calc_gain_kp(i));
}

void angletracer_set_gain_ki_index(unsigned short int i)
{
    angletracer_set_gain_ki_direct(tracer_calc_gain_ki(i));
}

void angletracer_set_gain_kd_index(unsigned short int i)
{
    angletracer_set_gain_kd_direct(tracer_calc_gain_kd(i));
}

void angletracer_set_gain_kp_direct(float kp)
{
    angletracer_pid.kp = kp;
}

void angletracer_set_gain_ki_direct(float ki)
{
    angletracer_pid.ki = ki;
}

void angletracer_set_gain_kd_direct(float kd)
{
    angletracer_pid.kd = kd;
}

void angletracer_set_gain_direct(float kp, float ki, float kd)
{
    angletracer_set_gain_kp_direct(kp);
    angletracer_set_gain_ki_direct(ki);
    angletracer_set_gain_kd_direct(kd);
}

/* kp ki kd set zero */
void angletracer_set_target_zero()
{
    angletracer_pid.target = 0;
}

void angletracer_set_gain_zero()
{
    angletracer_pid.kp = 0;
    angletracer_pid.ki = 0;
    angletracer_pid.kd = 0;
}

/* calclate pid values from rotary value */
float angletracer_calc_gain_kp(unsigned short int i)
{
    return TRACER_KP_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KP_MAX - TRACER_KP_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

float angletracer_calc_gain_ki(unsigned short int i)
{
    return TRACER_KI_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KI_MAX - TRACER_KI_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

float angletracer_calc_gain_kd(unsigned short int i)
{
    return TRACER_KD_MAX - ((TRACER_STEP_SIZE - 1) - i) * (float) (TRACER_KD_MAX - TRACER_KD_MIN) / (float) (TRACER_STEP_SIZE - 1);
}

/* set default */
void angletracer_set_gain_default()
{
    angletracer_pid = angletracer_default;
}

void angletracer_set_default_now_gain(float kp, float ki, float kd)
{
    angletracer_default.target = 0;
    angletracer_default.kp = kp;
    angletracer_default.ki = ki;
    angletracer_default.kd = kd;
}

/* all parameter */
void angletracer_set_values(PID *_pid)
{
    angletracer_set_target_zero();
    angletracer_pid.kp = _pid->kp;
    angletracer_pid.ki = _pid->ki;
    angletracer_pid.kd = _pid->kd;
}

PID* angletracer_read_values()
{
    return &angletracer_pid;
}

float angletracer_solve(int reference_)
{
    int error;
    float d_error;
    float result;

    #if D_TRACER_WHILE
    printf("tracer.c > tracer_solve() > ");
    printf("reference_ = %5d\r\n", reference_);
    #endif

    error = reference_ - angletracer_pid.target;

    d_error = (error - angletracer_before_error) / (float) (angletracer_sampling_time_ms / (float) 1000);
    angletracer_s_error += error * (float) (angletracer_sampling_time_ms / (float) 1000);

    result = angletracer_pid.kp * error + angletracer_pid.ki * angletracer_s_error + angletracer_pid.kd * d_error;

    #if D_TRACER_WHILE
    printf("angletracer.c > angletracer_solve() > ");
    printf("%7.2f = %7.2f * %5d + %7.2f * %7.2f + %7.2f * %7.2f\r\n", result, angletracer_pid.kp, error, angletracer_pid.ki, angletracer_s_error, angletracer_pid.kd, d_error);
    #endif

    angletracer_before_error = error;

    return result;
}

void angletracer_print_values()
{
#if D_TRACER
    printf("trac > kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", angletracer_pid.kp, angletracer_pid.ki, angletracer_pid.kd);
#endif
}

void angletracer_gain_tuning()
{
    /* angletracer_gain_tuning */
}


