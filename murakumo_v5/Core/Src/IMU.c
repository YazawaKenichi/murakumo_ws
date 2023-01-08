/**
 * @file IMU.c
 * @author IGC8810 / shimotoriharuki / YazawaKenichi (s21c1036hn@gmail.com)
 * @brief ICM-20648 から加速度と角速度の値を取得することができる
 * @version 1.3
 * @date 2023-01-08
 * @details 先輩方の IMU のライブラリ ICM20648.c に YazawaKenichi が手を加えた物
*/

#include "IMU.h"

#define USE_NCS 1
#define INIT_ZERO 1

// volatile int16_t xa, ya, za;
// volatile int16_t xg, yg, zg;

volatile Inertial inertial;
volatile Displacement displacement;
volatile Inertial inertial_offset;

Coordinate COORDINATE_ZERO;

uint8_t imu_read_byte( uint8_t reg )
{ 
	uint8_t ret,val;

	ret = reg | 0x80;
#if USE_NCS
	CS_RESET;
#endif
	HAL_SPI_Transmit(&hspi2, &ret, 1, 100);
	HAL_SPI_Receive(&hspi2, &val, 1, 100);
#if USE_NCS
	CS_SET;
#endif

	return val;
}

void imu_write_byte(uint8_t reg, uint8_t val)
{
	uint8_t ret;

	ret = reg & 0x7F;

#if USE_NCS
	CS_RESET;
#endif

	HAL_SPI_Transmit(&hspi2, &ret, 1, 100);
	HAL_SPI_Transmit(&hspi2, &val, 1, 100);

#if USE_NCS
	CS_SET;
#endif
}

void imu_init()
{
	printf("Starting SPI2 (IMU)\r\n");
	uint8_t wai, ret;
	ret = imu_initialize(&wai);
	printf("who_am_i = %d\r\n", wai);
	if(ret == 1)
	{
		printf("SPI INIT COLLECT!\r\n");
	}
	else
	{
		printf("SPI INIT FAILURE x_x \r\n");
	}
}

uint8_t imu_initialize(uint8_t* wai)
{
	CS_RESET;
	uint8_t who_am_i,ret;
	ret = 0;

	COORDINATE_ZERO.x = 0;
	COORDINATE_ZERO.y = 0;
	COORDINATE_ZERO.z = 0;

	RADPERDEG = ((double) M_PI / (double) 180);

#if	INIT_ZERO
	inertial.accel = COORDINATE_ZERO;
	inertial.gyro = COORDINATE_ZERO;
	displacement.position = COORDINATE_ZERO;
	displacement.theta = COORDINATE_ZERO;
#endif

	who_am_i = imu_read_byte(0x00);
	*wai = who_am_i;
	if(who_am_i == 0xE0)
	{	// ICM-20648 is 0xE0
		ret = 1;
		imu_write_byte(PWR_MGMT_1, 0x01);	//PWR_MGMT_1
		HAL_Delay(100);
		imu_write_byte(USER_CTRL, 0x10);	//USER_CTRL
		imu_write_byte(REG_BANK_SEL, 0x20);	//USER_BANK2
		// shimotoriharuki
		//write_byte(0x01,0x06);	//range±2000dps DLPF disable	// range+-2000
		// igc8810
		imu_write_byte(0x01, 0x07);	//range±2000dps DLPF enable DLPFCFG = 0
		//write_byte(0x01,0x0F);	//range±2000dps DLPF enable DLPFCFG = 1
		//write_byte(0x01,0x17);	//range±2000dps DLPF enable DLPFCFG = 2
		//2:1 GYRO_FS_SEL[1:0] 00:±250	01:±500 10:±1000 11:±2000
		// igc8810
		imu_write_byte(0x14, 0x00);	//range±2g
		// shimotoriharuki
		//write_byte(0x14,0x06);	// range+-16
		//2:1 ACCEL_FS_SEL[1:0] 00:±2	01:±4 10:±8 11:±16
		imu_write_byte(REG_BANK_SEL, 0x00);	//USER_BANK0
		imu_set_offset();
	}
#if USE_NCS
	CS_SET;
#endif
	return ret;
}

void imu_stop()
{
#if !USE_NCS
	CS_SET;
#endif
}

void imu_set_offset()
{
	imu_read();
	inertial_offset = inertial;
}

/**
 * @fn
 * 
 * @brief inertial 変数に、現在の加速度・角速度の値を代入する関数
 * @details
 * @attention 値を代入したら外部参照変数を呼び出して値を取得することになる
*/
void imu_read()
{
	inertial.accel.x = ((int16_t)imu_read_byte(ACCEL_XOUT_H) << 8) | ((int16_t)imu_read_byte(ACCEL_XOUT_L));
	inertial.accel.y = ((int16_t)imu_read_byte(ACCEL_YOUT_H) << 8) | ((int16_t)imu_read_byte(ACCEL_YOUT_L));
	inertial.accel.z = ((int16_t)imu_read_byte(ACCEL_ZOUT_H) << 8) | ((int16_t)imu_read_byte(ACCEL_ZOUT_L));
	inertial.gyro.x = ((int16_t)imu_read_byte(GYRO_XOUT_H) << 8) | ((int16_t)imu_read_byte(GYRO_XOUT_L));
	inertial.gyro.y = ((int16_t)imu_read_byte(GYRO_YOUT_H) << 8) | ((int16_t)imu_read_byte(GYRO_YOUT_L));
	inertial.gyro.z = ((int16_t)imu_read_byte(GYRO_ZOUT_H) << 8) | ((int16_t)imu_read_byte(GYRO_ZOUT_L));
}


