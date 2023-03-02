#ifndef __FLASH_H__
#define __FLASH_H__

#include "analog.h"
#include "defines.h"
#include "print.h"
#include "string.h"
#include "stm32f4xx_hal.h"
#include "sidesensor.h"

#define BACKUP_FLASH_SECTORNUM FLASH_SECTOR_11
#define BACKUP_FLASH_SECTOR_SIZE (1024*16)
#define COURSE_STATE_SIZE 6000  // 6000 = 60 [ m ] / COURSE_SAMPLING_LENGTH [ m ]

#ifndef CALIBRATIONSIZE
#define CALIBRATIONSIZE 16
#endif

typedef struct
{
    uint16_t course_state_count_max;
    uint16_t analogmin[CALIBRATIONSIZE];
    uint16_t analogmax[CALIBRATIONSIZE];
} AnalogData;

typedef struct
{
    float speed[COURSE_STATE_SIZE];
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
    Vector3 accel;
    Vector3 gyro;
} ImuData;

void flash_erase(void);
void flash_writting(uint32_t, uint8_t*, uint32_t);
void flash_reading(uint32_t, uint8_t*, uint32_t);
void flash_write();
void flash_read();
void flash_init();

extern AnalogData analogdata;
extern CourseData coursedata;
extern EncoderData encoderdata;
extern ImuData;

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
