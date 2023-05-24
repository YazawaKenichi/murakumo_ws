#ifndef __TRACER_H__
#define __TRACER_H__

#include "pid.h"
#include "print.h"
#include "Rotary.h"

#define D_ANGLETRACER 1
#define D_ANGLETRACER_WHILE 0

#define ANGLETRACER_STEP_SIZE 16

#define ANGLETRACER_KP_MAX 10
#define ANGLETRACER_KI_MAX 0
#define ANGLETRACER_KD_MAX 0

#define ANGLETRACER_KP_MIN 0
#define ANGLETRACER_KI_MIN 0
#define ANGLETRACER_KD_MIN 0

/* pre setting */
void angletracer_init(float);
void angletracer_start();
void angletracer_stop();

/* reading */
float angletracer_read_gain_kp();
float angletracer_read_gain_ki();
float angletracer_read_gain_kd();

/* gain setting */
void angletracer_set_gain_kp_index(unsigned short int);
void angletracer_set_gain_ki_index(unsigned short int);
void angletracer_set_gain_kd_index(unsigned short int);
void angletracer_set_gain_kp_direct(float kp);
void angletracer_set_gain_ki_direct(float ki);
void angletracer_set_gain_kd_direct(float kd);
void angletracer_set_gain_direct(float, float, float);

/* target kp ki kd set zero */
void angletracer_set_target_zero();
void angletracer_set_gain_zero();

/* calclate pid values from rotary value */
float angletracer_calc_gain_kp(unsigned short int);
float angletracer_calc_gain_ki(unsigned short int);
float angletracer_calc_gain_kd(unsigned short int);

/* set default */
void angletracer_set_gain_default();                         //! デフォルトのゲイン値を取り戻す
void angletracer_set_default_now_gain(float, float, float);  //! 指定のパラメータをデフォルトのゲイン値に設定する

/* all parameter */
void angletracer_set_values(PID *_pid);
PID* angletracer_read_values();

/* calclate pid solving */
float angletracer_solve(float);
void angletracer_print_values();

/* usuage */
/*
    run_init()
    {
        ...
        angletracer_init();
        / * 記述中 * /
        ...
    }

    in_timer()
    {
        ...
        motor = angletracer_solve(sensorvalue);
        ...
    }
*/

#endif
