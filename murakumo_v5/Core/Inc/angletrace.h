#ifndef __ANGLETRACE_H__
#define __ANGLETRACE_H__

#include "pid.h"
#include "print.h"
#include "Rotary.h"
#include "math.h"

#define D_ANGLETRACE 1
#define D_ANGLETRACE_WHILE 0

#define ANGLETRACE_STEP_SIZE 16

#define ANGLE_TARGET_MAX 0
#define ANGLE_KP_MAX 4
#define ANGLE_KI_MAX 80
#define ANGLE_KD_MAX 0

#define ANGLE_TARGET_MIN 0
#define ANGLE_KP_MIN 4
#define ANGLE_KI_MIN 40
#define ANGLE_KD_MIN 0

//! 指定時間後に停止する
#define ANGLETRACE_GAIN_TUNING_STOP_TIME_MS 10000

/* pre setting */
void angletrace_init(uint16_t samplingtime_ms);   //! s_error and d_error are zero
void angletrace_start(); //! angletrace_init(1), angletrace_set_gain_index(), angletrace_set_target_index()
void angletrace_stop();

/* reading */
float angletrace_read_target();
float angletrace_read_gain_kp();
float angletrace_read_gain_ki();
float angletrace_read_gain_kd();

/* terget setting */
void angletrace_set_target_index(unsigned short int i);
void angletrace_set_target_direct(float target);

/* gain setting */
void angletrace_set_gain_kp_index(unsigned short int i);
void angletrace_set_gain_ki_index(unsigned short int i);
void angletrace_set_gain_kd_index(unsigned short int i);
void angletrace_set_gain_kp_direct(float target);
void angletrace_set_gain_ki_direct(float target);
void angletrace_set_gain_kd_direct(float target);
void angletrace_set_gain_direct(float, float, float);

/* target kp ki kd set zero */
void angletrace_set_target_zero();
void angletrace_set_gain_zero();

/* calclate pid values from rotary value */
float angletrace_calc_target(unsigned short int i);
float angletrace_calc_gain_kp(unsigned short int i);
float angletrace_calc_gain_ki(unsigned short int i);
float angletrace_calc_gain_kd(unsigned short int i);

/* all parameter */
void angletrace_set_values(PID *_pid);
PID* angletrace_read_values();

/* calclate pid solving */
float angletrace_solve(float reference_);
void angletrace_print_values();

void angletrace_gain_tuning();

#endif
