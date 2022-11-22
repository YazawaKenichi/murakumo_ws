#ifndef __TRACER_H__
#define __TRACER_H__

#include "pid.h"
#include "print.h"

#define D_TRACER 1

#define TRACER_STEP_SIZE 16

#define TRACER_KP_MAX 0.25f
#define TRACER_KI_MAX 0
#define TRACER_KD_MAX 0
#define TRACER_KP_MIN 0.25f
#define TRACER_KI_MIN 0
#define TRACER_KD_MIN 0

/* 追従が弱い D が大きすぎる */
#if OLD_BEST
#define TRACER_KP_MAX 17.5f
#define TRACER_KI_MAX 0
#define TRACER_KD_MAX 335.71f
#define TRACER_KP_MIN 17.5f
#define TRACER_KI_MIN 0
#define TRACER_KD_MIN 335.71f
#endif

/* s_error and d_error are zero and if search then gain and target are zero */
void tracer_start();
/* s_error and d_error are zero*/
void tracer_init(double samplingtime_);
/* read kp ki kd */
double tracer_read_gain_kp(unsigned short int i);
double tracer_read_gain_ki(unsigned short int i);
double tracer_read_gain_kd(unsigned short int i);
/* kp ki kd settings*/
void tracer_set_gain(unsigned short int i);
/* terget setting */
void tracer_set_target(double target_);
/* calclate pid solving */
double tracer_solve(int reference_);
/* calclate pid solving with pid gain */
double tracer_solve_with_gain(int, double, double, double);
void tracer_d_print();
void tracer_print_values();
/* read pid struct */
// PID tracer_read();
/* set pid struct */
// void tracer_set(PID);

/* usuage */
/*
    run_init()
    {
        ...
        tracer_init();
        tracer_set_gain(10, 8, 2);
        tracer_set_target(0);
        ...
    }

    in_timer()
    {
        ...
        motor = tracer_solve(sensorvalue);
        ...
    }
*/

#endif
