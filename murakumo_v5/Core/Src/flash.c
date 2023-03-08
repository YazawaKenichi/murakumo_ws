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

void flash_writting(uint32_t sector_num)
{
	uint32_t start_address;
	uint8_t *ptr;
	uint32_t len;

	HAL_FLASH_Unlock();
	flash_erase(sector_num);

	//! AnalogData : Sector8
	if(sector_num == FLASH_SECTOR_8)
	{
		start_address = FLASH_SECTOR_8_START_ADDRESS;
		ptr = (uint8_t *) analogdata;
		len = sizeof(AnalogData)
	}

	//! EncoderData : Sector9
	if(sector_num == FLASH_SECTOR_9)
	{
		start_address = FLASH_SECTOR_9_START_ADDRESS;
		ptr = (uint8_t *) encoderdata;
		len = sizeof(EncoderData)
	}

	//! ImuData : Sector10
	if(sector_num == FLASH_SECTOR_10)
	{
		start_address = FLASH_SECTOR_10_START_ADDRESS;
		ptr = (uint8_t *) imudata;
		len = sizeof(ImuData)
	}

	//! CourseData : Sector11
	if(sector_num == FLASH_SECTOR_11)
	{
		start_address = FLASH_SECTOR_11_START_ADDRESS;
		ptr = (uint8_t *) coursedata;
		len = sizeof(CourseData)
	}

	for (uint32_t add = start_address; add < (start_address + len); add++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, add, *ptr);
		data++;
	}

	HAL_FLASH_Lock();
}

void flash_reading(uint32_t address, uint8_t *data, uint32_t size)
{
	memcpy(data, (uint64_t*) address, size);
}

void flash_write(uint32_t sector_num)
{
	flash_writting(sector_num);
}

void flash_read(uint32_t start_address)
{
	uint32_t start_address;
	uint_8 *ptr;
	uint32_t size;

	//! AnalogData : Sector8
	if(sector_num == FLASH_SECTOR_8)
	{
		start_address = FLASH_SECTOR_8_START_ADDRESS;
		ptr = (uint8_t *) analogdata;
		size = sizeof(AnalogData)
	}

	//! EncoderData : Sector9
	if(sector_num == FLASH_SECTOR_9)
	{
		start_address = FLASH_SECTOR_9_START_ADDRESS;
		ptr = (uint8_t *) encoderdata;
		size = sizeof(EncoderData)
	}

	//! ImuData : Sector10
	if(sector_num == FLASH_SECTOR_10)
	{
		start_address = FLASH_SECTOR_10_START_ADDRESS;
		ptr = (uint8_t *) imudata;
		size = sizeof(ImuData)
	}

	//! CourseData : Sector11
	if(sector_num == FLASH_SECTOR_11)
	{
		start_address = FLASH_SECTOR_11_START_ADDRESS;
		ptr = (uint8_t *) coursedata;
		size = sizeof(CourseData)
	}

	flash_reading(start_address, ptr, size);
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

