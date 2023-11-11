#ifndef __velotrace_left_H__
#define __velotrace_left_H__

#include "pid.h"
#include "print.h"
#include "rotary.h"

#define D_VELOTRACE_LEFT 0
#define D_VELOTRACE_LEFT_WHILE 0

#define VELOTRACE_LEFT_STEP_SIZE 16

#define VELOCITY_LEFT_TARGET_MAX 0.00f    /* [m/s] */
#define VELOCITY_LEFT_TARGET_MIN 0.00f
#define VELOCITY_LEFT_KP_MAX 2.3f
#define VELOCITY_LEFT_KI_MAX 20
#define VELOCITY_LEFT_KD_MAX 0
#define VELOCITY_LEFT_KP_MIN 2.3f
#define VELOCITY_LEFT_KI_MIN 20
#define VELOCITY_LEFT_KD_MIN 0

//! スタートマーカを読んでから指定時間後に停止する
#define VELOTRACE_LEFT_GAIN_TUNING_STOP_TIME_MS 3000

/* pre setting */
void velotrace_left_init(uint16_t samplingtime_ms);  //! s_error and d_error are zero
void velotrace_left_start(); //! velotrace_left_init(1), velotrace_left_set_gain_index(), velotrace_left_set_target_index()
void velotrace_left_stop();

/* reading */
float velotrace_left_read_target();
float velotrace_left_read_gain_kp();
float velotrace_left_read_gain_ki();
float velotrace_left_read_gain_kd();

/* terget setting */
void velotrace_left_set_target_index(unsigned short int i);
void velotrace_left_set_target_direct(float target);

/* gain setting */
void velotrace_left_set_gain_kp_index(unsigned short int i);
void velotrace_left_set_gain_ki_index(unsigned short int i);
void velotrace_left_set_gain_kd_index(unsigned short int i);
void velotrace_left_set_gain_kp_direct(float target);
void velotrace_left_set_gain_ki_direct(float target);
void velotrace_left_set_gain_kd_direct(float target);
void velotrace_left_set_gain_direct(float, float, float);

/* target kp ki kd set zero */
void velotrace_left_set_target_zero();
void velotrace_left_set_gain_zero();

/* calclate pid values from rotary value */
float velotrace_left_calc_target(unsigned short int i);
float velotrace_left_calc_gain_kp(unsigned short int i);
float velotrace_left_calc_gain_ki(unsigned short int i);
float velotrace_left_calc_gain_kd(unsigned short int i);

/* all parameter */
void velotrace_left_set_values(PID *_pid);
PID* velotrace_left_read_values();

/* calclate pid solving */
float velotrace_left_solve(float reference_);

void velotrace_left_d_print();

void velotrace_left_gain_tuning();

#endif