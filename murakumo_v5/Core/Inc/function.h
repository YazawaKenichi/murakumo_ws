#ifndef __DEFS_H__
#define __DEFS_H__

/* ↓これ何に使ってん？
#include "string.h"
#include "stdint.h"
*/

#include "math.h"

#define COURSE_START_TIME_PLUSE 1

#define SECOND 1

#define D_VELOCITY_CONTROL_IN_WHILE 0
#define VELOCITY_CONTROL_RELATIVE 1

#define SAMPLING_TIME 1000	// ms
#define SAMPLING_LENGTH 10000	// [udm]	// 10cm	// 100,000 [udm] = 1 [m]

#define TREAD 103	// mm
#define RMIN 100	// mm
#define THRESHOLDRADIUS 500	// mm
// LENGTHPUEPULSE = M_PI * TIREDIAMETER / PULSEPERROTATE

#define PWMMAX 1000 // 3360

#define STATICPWM 1

#define THRESHOLD_STARTING_LENGTH 250000	// um

// analog
#if D_PWM
#define PWM_STEP_AMPLITUDE 1000		// (288 + 1024 * 3) // PWM Pulse Amplitude
#define PWM_STEP_OMEGA 100	// PWM Step Omega (unit mrad / s)
uint32_t pwmstepoutput;	// PWM Duty
uint32_t pwmsteptime;	// PWM Step Time
char pwmstepud;	// PWM Step upword or downword
#endif

#if D_VELOCITY_CONTROL_TIMER
		double stoptime;	// ms
#endif

double low_pass_filter(double val, double pre_val, double gamma);
double sigmoid(double x, double a, double x0);

#ifndef __OBSOLETE_MATH
double pow(double a, double b);
double exp(double a);
#endif

#endif
