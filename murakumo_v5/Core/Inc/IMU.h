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

#include "math.h"
#include "print.h"

extern SPI_HandleTypeDef hspi2;
#define CS_RESET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define CS_SET   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

#define ACCEL_RANGE		2.0f
#define GYRO_RANGE		2000.0f
#define MAXDATA_RANGE	32764.0f
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
#define REG_BANK_SEL 0x7F

typedef struct
{
	/* data */
	float x,
	float y,
	float z
} Position;

typedef struct
{
	/* data */
	float roll,
	float pitch,
	float yaw
} Rpy;


typedef struct
{
	Coordinate accel;
	Coordinate gyro;
} Inertial;

typedef struct
{
	Position position;
	Rpy rpy;
} Pose;

double RADPERDEG;	// ( M_PI / 180 )	[rad / deg]

uint8_t imu_read_byte(uint8_t);
void imu_write_byte(uint8_t, uint8_t);
void imu_init();
uint8_t imu_initialize(uint8_t*);
void imu_stop();
void imu_set_offset();
void imu_read();
void Inertial_Integral(Pose*);
void Coordinate_Init(Coordinate*);
void Coordinate_Set(Coordinate *, Coordinate *);

//extern volatile int16_t 	xa, ya, za;
//extern volatile int16_t 	xg, yg, zg;

extern volatile Inertial inertial;
extern volatile Inertial inertial_offset;
extern volatile Pose pose;

#endif

