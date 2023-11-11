#ifndef __TRACER_H__
#define __TRACER_H__

#include "pid.h"
#include "print.h"
#include "rotary.h"

#define D_TRACER 0
#define D_TRACER_WHILE 0

#define TRACER_STEP_SIZE 16

#define TRACER_KP_MAX 0.6f
#define TRACER_KI_MAX 0
#define TRACER_KD_MAX 0.006f

#define TRACER_KP_MIN 0.6f
#define TRACER_KI_MIN 0
#define TRACER_KD_MIN 0.004f

/* pre setting */
void tracer_init(float);
void tracer_start();
void tracer_stop();

/* reading */
float tracer_read_gain_kp();
float tracer_read_gain_ki();
float tracer_read_gain_kd();

/* gain setting */
void tracer_set_gain_kp_index(unsigned short int);
void tracer_set_gain_ki_index(unsigned short int);
void tracer_set_gain_kd_index(unsigned short int);
void tracer_set_gain_kp_direct(float kp);
void tracer_set_gain_ki_direct(float ki);
void tracer_set_gain_kd_direct(float kd);
void tracer_set_gain_direct(float, float, float);

/* target kp ki kd set zero */
void tracer_set_target_zero();
void tracer_set_gain_zero();

/* calclate pid values from rotary value */
float tracer_calc_gain_kp(unsigned short int);
float tracer_calc_gain_ki(unsigned short int);
float tracer_calc_gain_kd(unsigned short int);

/* set default */
void tracer_set_gain_default();                         //! デフォルトのゲイン値を取り戻す
void tracer_set_default_now_gain(float, float, float);  //! 指定のパラメータをデフォルトのゲイン値に設定する

/* all parameter */
void tracer_set_values(PID *_pid);
PID* tracer_read_values();

/* calclate pid solving */
float tracer_solve(int);

void tracer_d_print();

/* usuage */
/*
    run_init()
    {
        ...
        tracer_init();
        / * 記述中 * /
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
