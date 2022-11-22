#include "print.h"

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart6, (uint8_t*) &ch, 1, 0xFFFF);
	return ch;
}

void print_rotary_value()
{
	printf("rotary_value = %2d\r\n", rotary_read_value());
}

void print_analog_rate()
{
	printf("\x1b[24C");	// Cursor move right *24
	printf("%4d, %4d | %4d, %4d\r\n", analog_sensor_get(12), analog_sensor_get(14), analog_sensor_get(15),
			analog_sensor_get(13));
	printf("%4d, %4d, %4d, %4d, %4d, %4d | %4d, %4d, %4d, %4d, %4d, %4d\r\n",
			analog_sensor_get(0), analog_sensor_get(2), analog_sensor_get(4), analog_sensor_get(6), analog_sensor_get(8), analog_sensor_get(10),
			analog_sensor_get(11), analog_sensor_get(9), analog_sensor_get(7), analog_sensor_get(5), analog_sensor_get(3),
			analog_sensor_get(1));
}
