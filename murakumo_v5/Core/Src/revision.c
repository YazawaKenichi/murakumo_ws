/**
 * @file revision.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief センサの調整や補正に使用する
 * @version 1.0
 * @date 2023-01-23
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "revision.h"

//! バイアス補正用カウンタ
unsigned int imu_revision_count;
double imu_revision_sum;
double imu_revision_average;

void imu_revision_init()
{
    //! course_init() されていることが前提で空関数
}

void imu_revision_start()
{
    imu_revision_count = 1;
    course_start();
    HAL_Delay(5000);
}

void imu_revision_stop()
{
    course_stop();
}

void imu_revision_print()
{
	//! バイアス補正用標準出力
	if(imu_revision_count <= IMU_REVISION_COUNT_MAX)
	{
        imu_revision_sum = imu_revision_sum + imu_read_yaw();
        imu_revision_average = imu_revision_sum / (double) imu_revision_count;
		printf("%7d, %lf\r\n", imu_revision_count, imu_revision_average);
        imu_revision_count = imu_revision_count + 1;
	}
}

void revision_print()
{
    #if IMU_REVISION
    imu_revision_print();
    #endif
}
