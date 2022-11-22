#include "flash.h"

#ifndef USE_WRITE_FLASH
#define USE_WRITE_FLASH 0
#endif

FlashBuffer flashbuffer;
uint16_t course_state_time;

const uint32_t start_address = 0x080E0000;
const uint32_t end_address = 0x080FFFFF;

void flash_erase(void)
{
	FLASH_EraseInitTypeDef erase;
	erase.TypeErase = FLASH_TYPEERASE_SECTORS;
	erase.Sector = FLASH_SECTOR_11;
	erase.NbSectors = 1;
	erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	uint32_t pageError = 0;

	HAL_FLASHEx_Erase(&erase, &pageError);
}

void flash_writting(uint32_t address, uint8_t *data, uint32_t size)
{
#if USE_WRITE_FLASH
	HAL_FLASH_Unlock();
	flash_erase();

	for (uint32_t add = address; add < (address + size); add++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, add, *data);
		data++;
	}

	HAL_FLASH_Lock();
#endif
}

void flash_reading(uint32_t address, uint8_t *data, uint32_t size)
{
	memcpy(data, (uint64_t*) address, size);
}

void flash_write()
{
	flash_writting(start_address, (uint8_t *) &flashbuffer, sizeof(FlashBuffer));
}

void flash_read()
{
	flash_reading(start_address, (uint8_t *) &flashbuffer, sizeof(FlashBuffer));
}

/* flash_read called only this method. */
void flash_init()
{
	flash_read();
}

