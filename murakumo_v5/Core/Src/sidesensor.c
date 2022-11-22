#include "sidesensor.h"

unsigned char subsensbuf, marker, sidedeltacount, markerstate, rightmarkercount;
SideSensorState sidesensorstate;

uint8_t sidesensor_read()
{
    uint8_t subsens;

    subsens = 0;
    subsens += !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) ? 1 : 0;
    subsens += !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) ? 2 : 0;

    return subsens;
}

void sidesensor_start()
{
    marker = 0;
    subsensbuf = 0;
    sidedeltacount = 0;
    markerstate = 0;
    rightmarkercount = 0;
    // HAL_TIM_Base_Start_IT(&htim14);
}

void sidesensor_stop()
{
	/* sidesensor_stop */
}

SideSensorState sidesensor_read_state()
{
	return sidesensorstate;
}

void sidesensor_set_state(SideSensorState sidesensorstate_)
{
	sidesensorstate = sidesensorstate_;
}

void sidesensor_right()
{
    markerstate = start_or_stop;
    if(rightmarkercount == 1 - 1)
    {
        // start
    }
    else if(rightmarkercount == 2 - 1)
    {
        // stop
    }
    rightmarkercount++;
}

void sidesensor_left()
{
    // curve
    markerstate = curve;
}

void sidesensor_cross()
{
    // cross
    markerstate = cross;
}

void sidesensor_straight()
{
	// straight
	markerstate = straight;
}

void sidesensor_function()
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
