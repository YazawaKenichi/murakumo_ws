#ifndef __ANALOG_H__
#define __ANALOG_H__

#include "print.h"
#include "defines.h"

#define ANALOG_CALIBRATION_IN_WHILE 0
#define ATTACH_LONGSENSOR 0	// use normal sensor and long sensor
#define USE_LONGSENSOR 0	// only use long sensor

#define SENSGETCOUNT 9

#ifndef CALIBRATIONSIZE
#define CALIBRATIONSIZE 16
#endif

typedef enum ANALOGMODE
{
    calibrating = 0,
    all = 16
} AnalogMode;

void analog_print();
void analog_print_min();
void analog_print_max();
void analog_print_analogmode();
void analog_set_analogmode(AnalogMode);
AnalogMode analog_read_analogmode();
void analog_set_on_flash(uint16_t *, uint16_t *);
void analog_set_from_flash(uint16_t *, uint16_t *);
void analog_set_calibrationsize(uint8_t calibrationsize_);
uint8_t analog_read_calibrationsize();
void analog_calibration_start();
void analog_calibration_stop();
void analog_init();
void analog_start();
void analog_stop();
void analog_sensor_start();
void analog_sensor_stop();
uint16_t analog_sensor_get(unsigned char i);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef * AdcHandle);
void analog_get_and_sort();

#endif
