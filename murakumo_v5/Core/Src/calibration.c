/**
 * 
 * @file calibration.c
 * 
 * SPDX-FileCopyrightText: 2023 YAZAWA Kenichi <s21c1036hn@gmail.com>
 * SPDX-License-Identifier: MIT-LICENSE
 * 
 */

#include "calibration.h"

void calibration_init()
{
	flash_init();
    analog_init();
}

void calibration_start()
{
    analog_start();
	analog_set_analogmode(analogmode_all);
    analog_reset_minmax();
	analog_print_max();
	analog_print_min();
}

void calibration_main()
{
	analog_update_minmax();
}

void calibration_stop()
{
	/* analog_calibration_stop */
	analog_set_analogmode(analogmode_all);
	/* HAL_ADC_Stop_DMA */
	analog_stop();
	analog_print_max();
	analog_print_min();
	/* analogdata.min/max = analogmin/max */
	analog_read_minmax(analogdata.min, analogdata.max);
	analog_print_max();
	analog_print_min();
	//! FLASH_SECTOR_8 is AnalogData
	flash_write(FLASH_SECTOR_8);
}

void calibration_fin()
{
}

void calibration_d_print()
{
}
