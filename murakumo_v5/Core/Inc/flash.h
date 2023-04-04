/**
 * @file flash.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-03-09
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#ifndef __FLASH_H__
#define __FLASH_H__

#include "analog.h"
#include "defines.h"
#include "print.h"
#include "string.h"
#include "stm32f4xx_hal.h"
#include "sidesensor.h"
#include "geometry.h"

#define FLASH_SECTOR_8_START_ADDRESS 0x08080000
#define FLASH_SECTOR_9_START_ADDRESS 0x080A0000
#define FLASH_SECTOR_10_START_ADDRESS 0x080C0000
#define FLASH_SECTOR_11_START_ADDRESS 0x080E0000

#define SAVE_RAM 1

#if !SAVE_RAM
#define COURSE_STATE_SIZE 6000  // 6000 = 60 [ m ] / COURSE_SAMPLING_LENGTH [ m ]
#else
#define COURSE_STATE_SIZE 1000   //! 2 [ m ] まで計測
#endif

#ifndef CALIBRATIONSIZE
#define CALIBRATIONSIZE 16
#endif

typedef struct
{
    uint16_t min[CALIBRATIONSIZE];
    uint16_t max[CALIBRATIONSIZE];
} AnalogData;

typedef struct
{
    uint16_t course_state_count_max;
    float radius[COURSE_STATE_SIZE];
    float marker[COURSE_STATE_SIZE];
} CourseData;

typedef struct
{
    float left[COURSE_STATE_SIZE];
    float right[COURSE_STATE_SIZE];
} EncoderData;

typedef struct
{
    /* 本当はこうしたい
    Vector3 accel;
    Vector3 gyro;
    */
    float yaw[COURSE_STATE_SIZE];
} ImuData;

void flash_erase(uint32_t);
void flash_writting(uint32_t, uint8_t *, uint32_t);
void flash_reading(uint32_t, uint8_t *, uint32_t);
void flash_write(unsigned);
void flash_read(unsigned);
void flash_init();
void flash_read_all();
void flash_write_all();

extern AnalogData analogdata;
extern CourseData coursedata;
extern EncoderData encoderdata;
extern ImuData imudata;

/* usuage */
/*
    run_stop()
    {
        ...
        writeFlash(start_address, (uint8_t*) &flashbuffer, sizeof(FlashBuffer));
        ...
    }
*/

#endif
