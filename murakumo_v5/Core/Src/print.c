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
	printf("%4d, %4d | %4d, %4d\r\n", analog_read(12), analog_read(14), analog_read(15),
			analog_read(13));
	printf("%4d, %4d, %4d, %4d, %4d, %4d | %4d, %4d, %4d, %4d, %4d, %4d\r\n",
			analog_read(0), analog_read(2), analog_read(4), analog_read(6), analog_read(8), analog_read(10),
			analog_read(11), analog_read(9), analog_read(7), analog_read(5), analog_read(3),
			analog_read(1));
}

void print_bin(uint32_t bin)
{
    uint8_t count;
	count = 0;
	printf("0b");
	for(uint32_t index = (1 << (sizeof(bin) * 4 - 1)); index > 0; index = index >> 1)
	{
		if(count % 4 == 0)
		{
			printf(" ");
		}
		if(bin & index)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		count++;
	}
}

void print_pid(PID* pid_)
{
	printf("target = %7.2f, kp = %7.2f, ki = %7.2f, kd = %7.2f\r\n", pid_->target, pid_->kp, pid_->ki, pid_->kd);
}
