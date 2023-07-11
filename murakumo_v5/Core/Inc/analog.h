#ifndef __ANALOG_H__
#define __ANALOG_H__

#include "print.h"
#include "defines.h"
#include "flash.h"
#include "function.h"

#define D_ANALOG 0

#define ANALOG_CALIBRATION_IN_WHILE 0
#define ATTACH_LONGSENSOR 0	// use normal sensor and long sensor
#define USE_LONGSENSOR 0	// only use long sensor

#define SENSGETCOUNT 9

#ifndef CALIBRATIONSIZE
#define CALIBRATIONSIZE 16
#endif

#define ANALOG_LPF_GAMMA 0

typedef enum ANALOGMODE
{
    analogmode_calibrating = 0,
    analogmode_long = 4,
    analogmode_short = 12,
    analogmode_all = 16
} AnalogMode;

//! control
void analog_init();
void analog_start();
void analog_stop();

void analog_dma_start();
void analog_dma_stop();

void analog_calibration_start();
void analog_calibration_stop();

//! update
void analog_update();
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef * AdcHandle);

//! read
uint16_t analog_read(unsigned char i);
AnalogMode analog_read_analogmode();
uint8_t analog_read_calibrationsize();

//! set
void analog_set_analogmode(AnalogMode);
void analog_set_on_flash(uint16_t *, uint16_t *);
void analog_set_from_flash(uint16_t *, uint16_t *);
void analog_set_calibrationsize(uint8_t calibrationsize_);

//! function
void analog_get_and_sort();

//! print
void analog_print();
void analog_d_print();
void analog_array_print(uint16_t *analog_);
void analog_rate_array_print();
void analog_print_min();
void analog_print_max();
void analog_print_analogmode();

#endif
