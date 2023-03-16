#ifndef __COURSE_H__
#define __COURSE_H__

#include "stm32f4xx_hal.h"
#include "math.h"
#include "motor.h"
#include "encoder.h"
#include "flash.h"
#include "Rotary.h"
#include "Switch.h"
#include "section_length.h"
#include "time.h"
#include "function.h"   /// Low Pass Fileter が使いたい
#include "IMU.h"
#include "print.h"
#include "velotrace.h"
#include "fixed_section.h"

#ifndef TREAD
#define TREAD 103
#endif

#define D_COURSE 0  //! これ入れると stop 処理に printf が入って遅くなる
#define D_COURSE_WHILE 0
#define LEFT_MARKER_RADIUS 0

//! フラッシュの角度情報を COURSE_RADIUS_DEFAULT で初期化する
#define COURSE_RADIUS_DEFAULT 9.99f
//! フラッシュの速度情報を COURSE_SPEED_DEFAULT で初期化する
#define COURSE_SPEED_DEFAULT 0.999f
#define COURSE_SAMPLING_LENGTH (float) 0.010f // [ m ]

void course_init(unsigned short int samplingtime_ms);
void course_start();
void course_stop();
void course_update_section_degree();
void course_set_update_section_freq_ms(unsigned short int samplingtime_ms);
float course_read_section_degree();
void course_reset_section_degree();
float course_read_curvature_radius();
uint16_t course_read_state_count();
uint16_t course_read_sampling_count();
void course_increment_state_count();
void course_calclate_radius();
void course_state_function();
void course_d_print();
float course_radius2speed(float);
void course_fixing_radius2speed();
void course_print_flash();
void course_reset_flash();
float accel_max_calc(uint8_t);
void course_data_saving();

#endif
