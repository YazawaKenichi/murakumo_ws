#ifndef __VELOTRACE_H__
#define __VELOTRACE_H__

#include "pid.h"
#include "print.h"
#include "Rotary.h"

#define D_VELOTRACE 0
#define D_VELOTRACE_WHILE 0

#define VELOTRACE_STEP_SIZE 16

#define VELOCITY_TARGET_MAX 1    /* [m/s] */
#define VELOCITY_TARGET_MIN 1
#define VELOCITY_KP_MAX 1000
#define VELOCITY_KI_MAX 100
#define VELOCITY_KD_MAX 0
#define VELOCITY_KP_MIN 1000
#define VELOCITY_KI_MIN 100
#define VELOCITY_KD_MIN 0

/* velotrace_init(1), velotrace_set_gain(), velotrace_set_target() */
void velotrace_start();
void velotrace_stop();
/* s_error and d_error are zero */
void velotrace_init(float samplingtime_);
/* read target kp ki kd */
float velotrace_read_target(unsigned short int i);
float velotrace_read_gain_kp(unsigned short int i);
float velotrace_read_gain_ki(unsigned short int i);
float velotrace_read_gain_kd(unsigned short int i);
/* terget setting */
void velotrace_set_target(unsigned short int i);
void velotrace_set_values(PID*);
PID *velotrace_read_values();
/* kp ki kd settings */
void velotrace_set_gain(unsigned short int i);
/* target kp ki kd set zero */
void velotrace_set_gain_zero();
void velotrace_set_target_zero();
/* calclate pid solving */
float velotrace_solve(float reference_);
void veloctracer_print_values();
void velotrace_set_values(PID*);

#endif
