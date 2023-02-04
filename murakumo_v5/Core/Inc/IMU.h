/**
 * @file IMU.h
 * @author IGC8810 / shimotoriharuki / YazawaKenichi (s21c1036hn@gmail.com)
 * @brief ICM-20648 から加速度と角速度の値を取得することができる
 * @version 1.3
 * @date 2023-01-08
 * @details 先輩方の IMU のライブラリ ICM20648.h に YazawaKenichi が手を加えた物
*/

#ifndef ICM_20648_H
#define ICM_20648_H

#include "defines.h"
#include "stm32f4xx_hal.h"
#include "math.h"
#include "function.h"
#include "geometry.h"
#include "print.h"

#define USE_NCS 1
#define INIT_ZERO 1

#define CS_RESET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define CS_SET   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

#define ACCEL_RANGE		2.0f
#define GYRO_RANGE		2000.0f
#define MAXDATA_RANGE	32768.0f
#define G_ACCELERATION	9.806650f

#define USER_CTRL 0x03
#define PWR_MGMT_1 0x06
#define ACCEL_XOUT_H 0x2D
#define ACCEL_XOUT_L 0x2E
#define ACCEL_YOUT_H 0x2F
#define ACCEL_YOUT_L 0x30
#define ACCEL_ZOUT_H 0x31
#define ACCEL_ZOUT_L 0x32
#define GYRO_XOUT_H 0x33
#define GYRO_XOUT_L 0x34
#define GYRO_YOUT_H 0x35
#define GYRO_YOUT_L 0x36
#define GYRO_ZOUT_H 0x37
#define GYRO_ZOUT_L 0x38
//! This address (127) can selsct "User Bank" index
#define REG_BANK_SEL 0x7F

//! (M_PI / 180) [rad / deg]
#define RADPERDEG (M_PI / (float) 180)

//! バイアス補正
#define BIAS_AVERAGE (-0.137694f + 0.0025f)  // 求めた平均値
#define TRUE_VALUE 0    // 真値

//! Low Pass Filter
#define LPF_RATE 0.3f

uint8_t imu_read_byte(uint8_t);
void imu_write_byte(uint8_t, uint8_t);
void imu_init();
uint8_t imu_initialize(uint8_t*);
void imu_start();
void imu_stop();
void imu_update_gyro();
void imu_update_accel();
float imu_read_yaw();
float imu_read_direct_yaw();

//extern volatile int16_t 	xa, ya, za;
//extern volatile int16_t 	xg, yg, zg;

#endif

