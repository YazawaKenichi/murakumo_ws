#include "rotary.h"

PlayMode playmode;
uint8_t rotary_value;

void rotary_init()
{
    printf("rotary_init()\r\n");
    rotary_update();
    rotary_set_playmode();
    rotary_set_value();
}

void rotary_update()
{
    uint8_t rotary_value_ = 0;

    rotary_value_ += (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) ? 0 : 1) << 0;
    rotary_value_ += (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) ? 0 : 1) << 1;
    rotary_value_ += (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) ? 0 : 1) << 2;
    rotary_value_ += (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) ? 0 : 1) << 3;

    rotary_value = rotary_value_;
}

uint8_t rotary_read()
{
    return rotary_value;
}

PlayMode rotary_read_playmode()
{
    return playmode;
}

void rotary_set_playmode()
{
    printf("rotary_set_playmode()\r\n");
    playmode = rotary_read();
    printf("playmode = %d\r\n", playmode);
}

void rotary_set_value()
{
    rotary_value = rotary_read();
}

void rotary_print_playmode()
{
	printf("playmode = ");
	switch(rotary_read_playmode())
	{
		case pm_calibration:
			printf("calibration");
			break;
		case pm_explore:
			printf("explore");
			break;
		case pm_shortcut:
			printf("shortcut");
			break;
		case pm_accel:
			printf("accel");
			break;
        case pm_free:
            printf("free");
            break;
		case pm_print:
			printf("print");
			break;
		default:
			printf("unknown playmode...");
			break;
	}
	printf("\r\n");
}
