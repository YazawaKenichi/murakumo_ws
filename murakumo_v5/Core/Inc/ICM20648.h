#ifndef ICM_20648_H
#define ICM_20648_H

#include <main.h>
#include <math.h>

extern SPI_HandleTypeDef hspi2;
#define CS_RESET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define CS_SET   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

#define ACCEL_RANGE		2.0f
#define GYRO_RANGE		2000.0f
#define MAXDATA_RANGE	32764.0f
#define G_ACCELERATION	9.80665.0f

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
	int16_t x;
	int16_t y;
	int16_t z;
} Coordinate;

typedef struct
{
	double x;
	double y;
	double z;
} Coordinate_float;

typedef struct
{
	Coordinate accel;
	Coordinate gyro;
} Inertial;

typedef struct
{
	Coordinate position;
	Coordinate theta;
} Displacement;

double RADPERDEG;	// ( M_PI / 180 )	[rad / deg]

uint8_t read_byte(uint8_t);
void write_byte(uint8_t, uint8_t);
uint8_t IMU_init(uint8_t*);
void IMU_set_offset();
void IMU_fin();
void IMU_read();
void Inertial_Integral(Displacement*);
void Coordinate_Init(Coordinate*);

//extern volatile int16_t 	xa, ya, za;
//extern volatile int16_t 	xg, yg, zg;

extern volatile Inertial inertial;
extern volatile Inertial inertial_offset;
extern volatile Displacement displacement;

#endif

