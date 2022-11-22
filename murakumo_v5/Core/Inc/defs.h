#ifndef __DEFS_H__
#define __DEFS_H__
#include <ICM20648.h>
#include "stdio.h"
#include <string.h>
#include <stdint.h>

#include "velodef.h"
//#include "banquet_art.hpp"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

#define ATTACH_LONGSENSOR 0	// use normal sensor and long sensor
#define USE_LONGSENSOR 0	// only use long sensor

#define COURSE_START_TIME_PLUSE 1

#define SECOND 1

#define D_VELOCITY_CONTROL_IN_WHILE 0
#define VELOCITY_CONTROL_RELATIVE 1

#define BACKUP_FLASH_SECTOR_NUM FLASH_SECTOR_11
#define BACKUP_FLASH_SECTOR_SIZE (1024*16)
#if D_COURSE_STATE_SAVING
#define COURSE_STATE_SIZE 600/2	// over ( 60 * 10 * 1,000,000 / SAMPLING_LENGTH )
#else
#define COURSE_STATE_SIZE 10000
#endif

#define ADC_CONVERTED_DATA_BUFFER_SIZE 16	// ADC Channel Count
#define SENSGETCOUNT 9

#define ENCODER_MIDDLE (2048/2)
#define SAMPLING_TIME 1000	// ms
#define SAMPLING_LENGTH 10000	// [udm]	// 10cm	// 100,000 [udm] = 1 [m]

#ifndef __OBSOLETE_MATH
#define PI 3.14159265358979f
#define E 2.718281828459f
#endif	// __MAIN_H
#define TIREDIAMETER 21000		// um
#define PULSEPERROTATE 4096	// Pulse / Rotate
#define PINION 25
#define SUPER 64
#define TREAD 103	// mm
#define RMIN 100	// mm
#define THRESHOLDRADIUS 500	// mm
// LENGTHPUEPULSE = M_PI * TIREDIAMETER / PULSEPERROTATE

#if USE_VELOCITY_CONTROL
#define VELOCITY_MAX 8340
#if VELOCITY_CONTROL_RELATIVE
//#define VKP 20	// 27.5f
//#define VKI 0.2f	// 0.15f
#else	// VELOCITY_CONTRO_RELATIVE
// left
#define VKPL 8.0f
#define VKIL 0.025	// 0.025f
// right
#define VKPR 8.0f
#define VKIR 0.025	// 0.025f
#endif	// VELOCITY_CONTROL_RELATIVE
#if D_VELOCITY_CONTROL_TIMER
#define STOPTIME 1000 // 13188	// uint32_t [ms]
#endif
#endif	// USE_VELOCITY_CONTROL

#define PWMMAX 1000 // 3360

#if D_PWM
#define STATICPWM 1
#endif

#if ATTACH_LONGSENSOR	// use normal sensor and long sensor

#define CALIBRATIONSIZE 16
#else	// !ATTACH_LONGSENSOR
#if USE_LONGSENSOR	// only use long sensor
#define CALIBRATIONSIZE 4
#else	// !USE_LONGSENSOR
#define CALIBRATIONSIZE 12
#endif	// !USE_LONGSENSOR
#endif	// !ATTACH_LONGSENSOR

#if USE_SLOWSTART
#define THRESHOLD_STARTING_LENGTH 250000	// um
#endif

#define ESC_MAG	"\x1b[35m"
#define ESC_RED "\x1b[31m"
#define ESC_YEL	"\x1b[33m"
#define ESC_GRE	"\x1b[32m"
#define ESC_CYA	"\x1b[36m"
#define ESC_BLU	"\x1b[34m"
#define ESC_DEF "\x1b[39m"

typedef struct
{
	uint16_t course_state_time_max;
	uint16_t analogmin[CALIBRATIONSIZE];
	uint16_t analogmax[CALIBRATIONSIZE];
#if !D_COURSE_SAVING
	double radius[COURSE_STATE_SIZE];	// radius > 0 => turn right
#endif
#if D_COURSE_SAVING
	double igz[COURSE_STATE_SIZE];
	double len[COURSE_STATE_SIZE];
#endif
} FlashBuffer;

typedef struct
{
	uint16_t velocity_target[16];
	double kp[16];
	double ki[16];
	double kd[16];
} VeloGain;

typedef enum
{
    calibration,    // 0
    search,	// 1
    accel, // 2
	max_enable,	// 3
    pid_tuning,	// 4
    zero_trace,	// 5
	banquet,	// 6
    flash_print = 15
} PlayMode;

// analog
uint16_t analograw[ADC_CONVERTED_DATA_BUFFER_SIZE];	// Analog Data

uint16_t analog[CALIBRATIONSIZE];
uint16_t analogmax[CALIBRATIONSIZE];
uint16_t analogmin[CALIBRATIONSIZE];
uint16_t analogbuffers[SENSGETCOUNT][CALIBRATIONSIZE];

uint16_t analograte[CALIBRATIONSIZE];
uint16_t analogr, analogl;	// Sum Right Analog Sensor, Sum Left Analog Sensor
int direction, beforedirection, sdirection;	// = analogr - analogl
unsigned char sensgettime;
uint8_t calibrationsize;

double kp, kd, ki;
#if USE_SLOWSTART
double base_p, base_i, base_d;
#endif

unsigned char subsensbuf, marker, sidedeltacount, markerstate, rightmarkercount;// 0 ~ 255(2^8-1)
short int encoder;
short int encoder_l, encoder_r;
double LENGTHPERPULSE;	// (um / pulse)

#if SECOND
// uint8_t velocity[COURSELENGTH * 1000];
#endif

#if D_PWM
#define PWM_STEP_AMPLITUDE 1000		// (288 + 1024 * 3) // PWM Pulse Amplitude
#define PWM_STEP_OMEGA 100	// PWM Step Omega (unit mrad / s)
uint32_t pwmstepoutput;	// PWM Duty
uint32_t pwmsteptime;	// PWM Step Time
char pwmstepud;	// PWM Step upword or downword
#endif

#if D_ENCODER
uint16_t d_encoder_left, dd_encoder_left, pre_d_encoder_left, d_encoder_right,
		dd_encoder_right, pre_d_encoder_right;
uint16_t enc1, enc2, enc3;
short int s_encoder, s_encoder_l, s_encoder_r;
#endif

double velocity_l, velocity_l_raw;
double velocity_r, velocity_r_raw;
#if VELOCITY_CONTROL_RELATIVE
double velocity_target;
#if USE_SLOWSTART
double base_velocity_target;
#endif
double velocity, s_velocity, velocity_error, s_velocity_error, velocity_next, velocity_raw;
double s_velocity_l, s_velocity_r;
double left_length, right_length;
#if USE_SLOWSTART
	double starting_length;
#endif
//		short int s_velocity_l, s_velocity_r;
#else	// VELOCITY_CONTROL_RELATIVE
		double velocity_error_l, s_velocity_error_l, velocity_next_l, nextspeed_l;
		double velocity_error_r, s_velocity_error_r, velocity_next_r, nextspeed_r;
#endif	// VELOCITY_CONTROL_RELATIVE
#if D_VELOCITY_CONTROL_TIMER
		double stoptime;	// ms
#endif

uint16_t sampling_time;
double m_velocity;
double mm_length;

// motor
short int commonspeed;
double leftmotor;
double rightmotor;

// switch
uint8_t rotary_value;
uint8_t rv;
char enter;
int timtim1, timtim2;

PlayMode playmode;
VeloGain low_velo, high_velo;

#if USE_SLOWSTART
uint8_t slow;
#endif

#if USE_FLASH
FlashBuffer flash_buffer;
uint16_t course_state_time;
#endif

Coordinate_float my_gyro;
uint16_t before_igz;
double theta;

// flag
uint8_t motorenable;

PUTCHAR_PROTOTYPE;
#if USE_LED
void led_rgb(char r, char g, char b);
void set_led(char, char);
#endif

uint8_t read_sidesens();

void sidesens_function();
void encoder_set_function();
void velocity_control_function();
void slow_start_function();
void velocity_control_switch_function();
void course_state_function();

void radius_calc();
void led_brink();

void running_initialize();
void running_finalize();
void sensor_initialize();
void sensor_finalize();
void pid_gain_initialize();
void pid_initialize();

void playmode_print();
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle);
#ifndef __OBSOLETE_MATH
double pow(double, double);
double exponential(double);
#endif
double sigmoid(double, double, double);
void encoder_initialize();
void encoder_finalize();
#if USE_FLASH
void eraseFlash(void);
void writeFlash(uint32_t, uint8_t*, uint32_t);
void loadFlash(uint32_t, uint8_t*, uint32_t);
#endif
void d_print();
double low_pass_filter(double val, double pre_val, double gamma);

#endif	// __DEFS_H__
