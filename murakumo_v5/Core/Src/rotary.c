#include "rotary.h"

PlayMode playmode;
uint8_t value;

void rotary_init()
{
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

    value = rotary_value_;
}

uint8_t rotary_read()
{
    return value;
}

PlayMode rotary_read_playmode()
{
    return playmode;
}

void rotary_set_playmode()
{
    playmode = rotary_read();
}

void rotary_set_value()
{
    value = rotary_read();
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

/* Usuage */
/*
    void main()
    {
        ...
        rotary_set_playmode();
        ...
        while(1)
        {
            ...
            switch(rotary_read())
            {
                case hoge:
                    ...
                    break;
                case fuga:
                    ...
                    break;
                case piyo:
                    ...
                    break;
                default:
                    break;
            }
            ...
        }
    }
*/
