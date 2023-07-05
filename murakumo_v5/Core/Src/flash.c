/**
 * @file flash.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-03-09
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#include "flash.h"

#ifndef USE_WRITE_FLASH
#define USE_WRITE_FLASH 0
#endif

AnalogData analogdata;
EncoderData encoderdata;
ImuData imudata;
CourseData coursedata;

const uint32_t start_address = 0x080E0000;
const uint32_t end_address = 0x080FFFFF;

void flash_erase(uint32_t sector_num)
{
	FLASH_EraseInitTypeDef erase;
	erase.TypeErase = FLASH_TYPEERASE_SECTORS;
	erase.Sector = sector_num;
	erase.NbSectors = 1;
	erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	uint32_t pageError = 0;

	HAL_FLASHEx_Erase(&erase, &pageError);
}

void flash_writting(uint32_t address, uint8_t *data, uint32_t size)
{
	for (uint32_t add = address; add < (address + size); add++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, add, *data);
		data++;
	}
}

void flash_reading(uint32_t address, uint8_t *data, uint32_t size)
{
	memcpy(data, (uint64_t*) address, size);
}

/* FLASH_SECTOR_num を渡すとそのセクタに対応する構造体のデータを書き込んでくれる関数 */
void flash_write(unsigned sector_num)
{
	HAL_FLASH_Unlock();
	flash_erase(sector_num);

	if(sector_num == FLASH_SECTOR_8)
	{
		flash_writting(FLASH_SECTOR_8_START_ADDRESS, (uint8_t *) &analogdata, sizeof(AnalogData));
	}

	if(sector_num == FLASH_SECTOR_9)
	{
		flash_writting(FLASH_SECTOR_9_START_ADDRESS, (uint8_t *) &encoderdata, sizeof(EncoderData));
	}

	if(sector_num == FLASH_SECTOR_10)
	{
		flash_writting(FLASH_SECTOR_10_START_ADDRESS, (uint8_t *) &imudata, sizeof(ImuData));
	}

	if(sector_num == FLASH_SECTOR_11)
	{
		flash_writting(FLASH_SECTOR_11_START_ADDRESS, (uint8_t *) &coursedata, sizeof(CourseData));
	}

	HAL_FLASH_Lock();
}

/* FLASH_SECTOR_num を渡すとそのセクタに対応する構造体のデータを読み取ってくれる関数 */
void flash_read(unsigned sector_num)
{
	//! AnalogData : Sector8
	if(sector_num == FLASH_SECTOR_8)
	{
		flash_reading(FLASH_SECTOR_8_START_ADDRESS, (uint8_t *) &analogdata, sizeof(AnalogData));
	}

	//! EncoderData : Sector9
	if(sector_num == FLASH_SECTOR_9)
	{
		flash_reading(FLASH_SECTOR_9_START_ADDRESS, (uint8_t *) &encoderdata, sizeof(EncoderData));
	}

	//! ImuData : Sector10
	if(sector_num == FLASH_SECTOR_10)
	{
		flash_reading(FLASH_SECTOR_10_START_ADDRESS, (uint8_t *) &imudata, sizeof(ImuData));
	}

	//! CourseData : Sector11
	if(sector_num == FLASH_SECTOR_11)
	{
		flash_reading(FLASH_SECTOR_11_START_ADDRESS, (uint8_t *) &coursedata, sizeof(CourseData));
	}
}

/* flash_read called only this method. */
void flash_init()
{
	flash_read_all();
}

void flash_read_all()
{
	flash_read(FLASH_SECTOR_8);
	flash_read(FLASH_SECTOR_9);
	flash_read(FLASH_SECTOR_10);
	flash_read(FLASH_SECTOR_11);
}

void flash_write_all()
{
	flash_write(FLASH_SECTOR_8);
	flash_write(FLASH_SECTOR_9);
	flash_write(FLASH_SECTOR_10);
	flash_write(FLASH_SECTOR_11);
}
