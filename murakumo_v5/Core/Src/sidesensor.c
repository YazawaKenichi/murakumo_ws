#include "sidesensor.h"

/* marker : 一回目の左右の色と二回目の左右の色が格納される */
/* markerstate : 直前のマーカの種類が格納される */
/* markerstate_volatile : 左右マーカを読み取った瞬間だけ格納され、次の周でデフォルトに戻される */
/* rightmarkercount : 右マーカの数が格納される */

unsigned char subsensbuf, marker, sidedeltacount, rightmarkercount;
SideSensorState markerstate, markerstate_volatile;
char sidesensor_start_or_stop;

uint8_t sidesensor_read()
{
    uint8_t subsens;

    subsens = 0;
    subsens += !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) ? 1 : 0;
    subsens += !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) ? 2 : 0;

    return subsens;
}

void sidesensor_init()
{
	/* sidesensor_init */
}

void sidesensor_start()
{
    marker = 0;
    subsensbuf = 0;
    sidedeltacount = 0;
    rightmarkercount = 0;
	markerstate = none;
	markerstate_volatile = none;
}

void sidesensor_stop()
{
	/* sidesensor_stop */
}

SideSensorState sidesensor_read_markerstate()
{
	return markerstate;
}

SideSensorState sidesensor_read_markerstate_volatile()
{
	SideSensorState _markerstate_volatile;
	_markerstate_volatile = markerstate_volatile;
	markerstate_volatile = none;
	return markerstate_volatile;
}

void sidesensor_right()
{
    if(rightmarkercount == 1 - 1)
    {
        // start
		markerstate_volatile = straight;
		markerstate = straight;
    }
    else if(rightmarkercount == 2 - 1)
    {
        // stop
		markerstate_volatile = stop;
		markerstate = stop;
    }
    rightmarkercount++;
}

void sidesensor_left()
{
    // curve
    markerstate = curve;
	markerstate_volatile = curve;
}

void sidesensor_cross()
{
    // cross
    markerstate = cross;
	markerstate_volatile = cross;
}

void sidesensor_straight()
{
	// straight
	markerstate = straight;
	markerstate_volatile = straight;
}

void sidesensor_main()
{
	unsigned char subsens;

	subsens = sidesensor_read();

	if(subsens != subsensbuf)
	{
		subsensbuf = subsens;
		marker += subsens << (2 * sidedeltacount);
		if(subsens == 0b00 && sidedeltacount != 0)
		{
            unsigned char first, second;
			first = (marker & 0b0011);
			second = (marker & 0b1100) >> 2;
			if (second == 0b00)
			{
				if (first == 0b01)
				{
					// right -> start / stop
                    sidesensor_right();
				}
				else if (first == 0b10)
				{
					// left -> curve
                    sidesensor_left();
				}
				else
				{
					// cross
                    sidesensor_cross();
				}
			}
			else
			{
				// cross
                sidesensor_cross();
			}
			sidedeltacount = 0;
			marker = 0;
		}
		else
		{
			sidedeltacount++;
		}
	}
}

void sidesensor_print_sidesensorstate(SideSensorState markerstate_)
{
	switch(markerstate_)
	{
		case none:
			printf("none\r\n");
			break;
		case straight:
			printf("straight\r\n");
			break;
		case start:
			printf("start\r\n");
			break;
		case stop:
			printf("stop\r\n");
			break;
		case curve:
			printf("curve\r\n");
			break;
		case cross:
			printf("cross\r\n");
			break;
		default:
		 	printf("unknown SideSensorState x_x\r\n");
			break;
	}
}

void sidesensor_d_print()
{
	#if D_SIDESENSOR
	printf("sidesensor.c > sidesensor_d_print() > ");
	sidesensor_print_sidesensorstate(markerstate);
	#endif
}
