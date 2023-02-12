#ifndef __VELOTRACE_H__
#define __VELOTRACE_H__

#include "pid.h"
#include "print.h"
#include "Rotary.h"

#define D_VELOTRACE 1
#define D_VELOTRACE_WHILE 0

#define VELOTRACE_STEP_SIZE 16

#define VELOCITY_TARGET_MAX 1    /* [m/s] */
#define VELOCITY_TARGET_MIN 1
#define VELOCITY_KP_MAX 2000
#define VELOCITY_KI_MAX 200   // 100
#define VELOCITY_KD_MAX 0
#define VELOCITY_KP_MIN 2000   // 1000
#define VELOCITY_KI_MIN 200   // 100
#define VELOCITY_KD_MIN 0

//! スタートマーカを読んでから指定時間後に停止する
#define VELOTRACE_GAIN_TUNING_STOP_TIME_MS 3000

/* pre setting */
void velotrace_init(float samplingtime_);   //! s_error and d_error are zero
void velotrace_start(); //! velotrace_init(1), velotrace_set_gain_index(), velotrace_set_target_index()
void velotrace_stop();

/* reading */
float velotrace_read_target();
float velotrace_read_gain_kp();
float velotrace_read_gain_ki();
float velotrace_read_gain_kd();

/* terget setting */
void velotrace_set_target_index(unsigned short int i);
void velotrace_set_target_direct(float target);

/* gain setting */
void velotrace_set_gain_kp_index(unsigned short int i);
void velotrace_set_gain_ki_index(unsigned short int i);
void velotrace_set_gain_kd_index(unsigned short int i);
void velotrace_set_gain_kp_direct(float target);
void velotrace_set_gain_ki_direct(float target);
void velotrace_set_gain_kd_direct(float target);
void velotrace_set_gain_direct(float, float, float);

/* target kp ki kd set zero */
void velotrace_set_target_zero();
void velotrace_set_gain_zero();

/* calclate pid values from rotary value */
float velotrace_calc_target(unsigned short int i);
float velotrace_calc_gain_kp(unsigned short int i);
float velotrace_calc_gain_ki(unsigned short int i);
float velotrace_calc_gain_kd(unsigned short int i);

/* all parameter */
void velotrace_set_values(PID *_pid);
PID* velotrace_read_values();

/* calclate pid solving */
float velotrace_solve(float reference_);
void veloctracer_print_values();

void velotrace_gain_tuning();

#endif
