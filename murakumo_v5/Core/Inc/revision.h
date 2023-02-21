/**
 * @file revision.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief センサの補正や調整に使用
 * @version 1.0
 * @date 2023-01-23
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#ifndef __REVISION_H__
#define __REVISION_H__

#include "stm32f4xx_hal.h"
#include "IMU.h"
#include "course.h"

#define IMU_REVISION 0

#define IMU_REVISION_COUNT_MAX 180000
#define IMU_REVISION_DELAY_MS 0

void imu_revision_init();
void imu_revision_start();
void imu_revision_stop();
void imu_revision_print();

void revision_print();

#endif
