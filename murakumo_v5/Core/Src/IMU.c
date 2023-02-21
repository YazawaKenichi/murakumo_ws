/**
 * @file IMU.c
 * @author IGC8810 / shimotoriharuki / YazawaKenichi (s21c1036hn@gmail.com)
 * @brief ICM-20648 から加速度と角速度の値を取得することができる
 * @version 1.3
 * @date 2023-01-08
 * @details 先輩方の IMU のライブラリ ICM20648.c に YazawaKenichi が手を加えた物
*/

#include "IMU.h"

// volatile int16_t xa, ya, za;
// volatile int16_t xg, yg, zg;

uint8_t initialized = 0;
Inertial inertial;

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

/**
 * @fn imu_init()
 * @brief 
 * 
 */
void imu_init()
{
	if(initialized == 0)
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
		initialized = initialized + 1;
	}
}

uint8_t imu_initialize(uint8_t* wai)
{
	CS_RESET;
	uint8_t who_am_i, ret;
	ret = 0;

#if	INIT_ZERO
	inertial.linear = vector3_creation(0, 0, 0);
	inertial.angular = vector3_creation(0, 0, 0);
#endif

	//! User Bank 0 を選択
	imu_write_byte(REG_BANK_SEL, 0x00);
	who_am_i = imu_read_byte(0x00);
	*wai = who_am_i;
	if(who_am_i == 0xE0)
	{	// ICM-20648 is 0xE0
		ret = 1;
		//! PWR_MGMT_1 推奨値 1
		imu_write_byte(PWR_MGMT_1, 0x01);	//PWR_MGMT_1
		//! PWR_MGMt_2 推奨値 0
		// imu_write_byte(PWR_MGMT_2, 0x00);
		HAL_Delay(100);
		imu_write_byte(USER_CTRL, 0x10);	//USER_CTRL

		/**
		 * @brief 
		 * @details
		 * REG BANK SEL の USER_BANK ( 0b 00** 0000 の位置 )
		 * 	00 : User Bank 0 : Who am I や加速度と角速度の実際の値が取れる
		 * 	01 : User Bank 1 : Self Test が使える（なにこれ）
		 * 	10 : User Bank 2 : 加速度と角速度の値の設定ができる
		 * 	11 : User Bank 3 : I2C の設定が行える
		 * 
		 */
		//! User Bank 2 を選択
		imu_write_byte(REG_BANK_SEL, 0x20);	//USER_BANK2

		/**
		 * @brief 
		 * @details
		 * REG_BANK_SEL : 0x20 を指定しているので User Bank 2 が選択されている
		 * User Bank 2 に於いて 0x01 で Gyro Config が可能
		 * GYRO_CONFIG_1 : Gyro Full Scale Range / Output Data Rate を選択する
		 * GYRO_DLPFCFG : Data Low Pass Filter
		 * 					 Use 2bit
		 * 					 Detail ... Datasheet > 14.2 GYRO_CONFIG_1
		 * GYRO_FS_SEL : Gyro Full Scale Range
		 * 					 00 : +- 250  [dps]
		 * 					 01 : +- 500  [dps]
		 * 					 10 : +- 1000 [dps]
		 * 					 11 : +- 2000 [dps] 
		 * GYRP_FCHOICE : Gyro Output Data Rate
		 * 					 0 : bypass gyro DLPF 9     [kHz]
		 * 					 1 : enable gyro DLPF 1.125 [kHz]
		 * 
		 */
		//! ( +- 2000 [dps] & bypass ) -> 0b 0000 0110 -> 0x06
		imu_write_byte(0x01, 0x06);

		/**
		 * @brief 
		 * @details
		 * REG_BANK_SEL : 0x20 を指定しているので User Bank 2 が選択されている
		 * User Bank 2 に於いて 0x14 で Accel Config が可能
		 * GYRO_CONFIG_1 : Accel Full Scale Range / Output Data Rate を選択する
		 * GYRO_DLPFCFG : Data Low Pass Filter
		 * 					 Use 2bit
		 * 					 Detail ... Datasheet > 14.15 ACCEL_CONFIG
		 * ACCEL_FS_SEL : Accelerometer Full Scale Range
		 * 					 00 : +-  2 [g]
		 * 					 01 : +-  4 [g]
		 * 					 10 : +-  8 [g]
		 * 					 11 : +- 16 [g] 
		 * ACCEL_FCHOICE : Accelerometer Output Data Rate
		 * 					 0 : bypass gyro DLPF 4.5   [kHz]
		 * 					 1 : enable gyro DLPF 1.125 [kHz]
		 * 
		 */
		//! ( +- 2 [dps] & bypass ) -> 0b 0000 0000 -> 0x06
		imu_write_byte(0x14, 0x00);

		//! User Bank 0 に戻す
		imu_write_byte(REG_BANK_SEL, 0x00);
	}
#if USE_NCS
	CS_SET;
#endif
	return ret;
}

void imu_start()
{
	/* imu_start */
}

void imu_stop()
{
#if !USE_NCS
	CS_SET;
#endif
}

/**
 * @fn imu_update_gyro()
 * 
 * @brief inertial 変数に、現在の角速度の値を代入する関数
 * @details
 * imu_read_byte(***_XOUT_H) で、Accel か Gyro の上位バイトが読める
 * imu_read_byte(***_XOUT_L) で、Accel か Gyro の下位バイトが読める
 *  | 演算で上位バイトと上位バイトを合成する
 * --- --- --- --- --- --- --- --- --- ---
 *  ***_XOUT_H       :           **** ****
 *  ***_XOUT_L       :           #### ####
 * --- --- --- --- --- --- --- --- --- ---
 *  ***_XOUT_H << 8  : **** **** 0000 0000
 *  ***_XOUT_L << 0  : 0000 0000 #### ####
 * --- --- --- --- --- --- --- --- --- ---
 * imu.inertial.***.* : **** **** #### ####
 * --- --- --- --- --- --- --- --- --- ---
 * @attention 値を代入したら外部参照変数を呼び出して値を取得することになる
 *
*/
void imu_update_gyro()
{
	float k_gyro;
	int16_t byte_data;
	float tmp;

	k_gyro = (GYRO_RANGE / (float) MAXDATA_RANGE);

	byte_data = ((int16_t)imu_read_byte(GYRO_XOUT_H) << 8) | ((int16_t)imu_read_byte(GYRO_XOUT_L));
	tmp = (float) byte_data * k_gyro;
	inertial.angular.x = low_pass_filter(tmp, inertial.angular.x, LPF_RATE);

	byte_data = ((int16_t)imu_read_byte(GYRO_YOUT_H) << 8) | ((int16_t)imu_read_byte(GYRO_YOUT_L));
	tmp = (float) byte_data * k_gyro;
	inertial.angular.y = low_pass_filter(tmp, inertial.angular.y, LPF_RATE);

	byte_data = ((int16_t)imu_read_byte(GYRO_ZOUT_H) << 8) | ((int16_t)imu_read_byte(GYRO_ZOUT_L));
	tmp = (float) byte_data * k_gyro;
	inertial.angular.z = low_pass_filter(tmp, inertial.angular.z, LPF_RATE);

	/**
	 * typedef struct
	 * {
	 * 		Vector3 angular;
	 * 		Vector3 linear;
	 * } Inertial;
	 * 
	 * typedef struct
	 * {
	 * 		float x;
	 * 		float y;
	 * 		float z;
	 * } Vector3;
	 * 
	 */
}

/**
 * @fn imu_update_accel()
 * 
 * @brief inertial 変数に、現在の加速度の値を代入する関数
 * @details
 * imu_read_byte(***_XOUT_H) で、Accel か Gyro の上位バイトが読める
 * imu_read_byte(***_XOUT_L) で、Accel か Gyro の下位バイトが読める
 *  | 演算で上位バイトと上位バイトを合成する
 * --- --- --- --- --- --- --- --- --- ---
 *  ***_XOUT_H       :           **** ****
 *  ***_XOUT_L       :           #### ####
 * --- --- --- --- --- --- --- --- --- ---
 *  ***_XOUT_H << 8  : **** **** 0000 0000
 *  ***_XOUT_L << 0  : 0000 0000 #### ####
 * --- --- --- --- --- --- --- --- --- ---
 *    inertial.***.* : **** **** #### ####
 * --- --- --- --- --- --- --- --- --- ---
 * @attention 値を代入したら外部参照変数を呼び出して値を取得することになる
 *
*/
void imu_update_accel()
{
	float k_accel;
	int16_t byte_data;

	k_accel = (ACCEL_RANGE / (float) MAXDATA_RANGE);

	byte_data = ((int16_t)imu_read_byte(ACCEL_XOUT_H) << 8) | ((int16_t)imu_read_byte(ACCEL_XOUT_L));
	inertial.linear.x = byte_data * k_accel;

	byte_data = ((int16_t)imu_read_byte(ACCEL_YOUT_H) << 8) | ((int16_t)imu_read_byte(ACCEL_YOUT_L));
	inertial.linear.y = byte_data * k_accel;

	byte_data = ((int16_t)imu_read_byte(ACCEL_ZOUT_H) << 8) | ((int16_t)imu_read_byte(ACCEL_ZOUT_L));
	inertial.linear.z = byte_data * k_accel;
}

float inertial_angular_z_buffer;
/**
 * @fn imu_read_yaw()
 * @brief 
 * 
 * @return float 
 * @attention [ degree ]
 * 
 */
float imu_read_yaw()
{
	//! バイアス補正を加味した返り値（ inertial.angular.z はすでに LPF を通されている ）
	return inertial.angular.z - (BIAS_AVERAGE - TRUE_VALUE);
}
