#include "analog.h"

unsigned int sensgettime;
uint8_t calibrationsize;

uint16_t analograw[CALIBRATIONSIZE];
uint16_t analog[CALIBRATIONSIZE];
uint16_t analogmax[CALIBRATIONSIZE];
uint16_t analogmin[CALIBRATIONSIZE];
uint16_t analograte[CALIBRATIONSIZE];
uint16_t analogbuffers[SENSGETCOUNT][CALIBRATIONSIZE];

AnalogMode analogmode;

void analog_array_print(uint16_t *analog_)
{
	printf("\x1b[24C");	// Cursor move right *24
	printf("%4d, %4d | %4d, %4d\r\n", *(analog_ + 12), *(analog_ + 14), *(analog_ + 15), *(analog_ + 13));
	printf("%4d, %4d, %4d, %4d, %4d, %4d | %4d, %4d, %4d, %4d, %4d, %4d\r\n", *(analog_ + 0), *(analog_ + 2), *(analog_ + 4), *(analog_ + 6), *(analog_ + 8), *(analog_ + 10), *(analog_ + 11), *(analog_ + 9), *(analog_ + 7), *(analog_ + 5), *(analog_ + 3), *(analog_ + 1));
}

void analog_rate_array_print()
{
	printf("\r\n");
	printf("\x1b[24C");	// Cursor move right *24
	printf("%4d, %4d | %4d, %4d\r\n", analog_sensor_get(12), analog_sensor_get(14), analog_sensor_get(15), analog_sensor_get(13));
	printf("%4d, %4d, %4d, %4d, %4d, %4d | %4d, %4d, %4d, %4d, %4d, %4d\r\n", analog_sensor_get(0), analog_sensor_get(2), analog_sensor_get(4), analog_sensor_get(6), analog_sensor_get(8), analog_sensor_get(10), analog_sensor_get(11), analog_sensor_get(9), analog_sensor_get(7), analog_sensor_get(5), analog_sensor_get(3), analog_sensor_get(1));
	printf("\r\n");

	uint16_t sum_, size_;

	sum_ = 0;
	size_ = 16;

	for(unsigned char i; i < size_; i++)
	{
		sum_ += analog_sensor_get(i);
	}

	printf("average = %4.2f\r\n\r\n", sum_ / (float) size_);
}

void analog_d_print()
{
#if D_ANALOG
	analog_print_analogmode();
	analog_rate_array_print();
	// analog_array_print(analog);
#endif
}

void analog_print_analogmode()
{
	printf("analogmode = ");
	switch(analog_read_analogmode())
	{
		case analogmode_calibrating:
			printf("analogmode_calibrating\r\n");
			break;
		case analogmode_long:
			printf("analogmode_long\r\n");
			break;
		case analogmode_short:
			printf("analogmode_short\r\n");
			break;
		case analogmode_all:
			printf("analogmode_all\r\n");
			break;
		default:
			printf("Unknown analogmode ... \r\n");
			break;
	}
	printf("\r\n");
}

void analog_print()
{
	printf("analog_print\r\n");
	printf("sensgettime = %2d\r\n", sensgettime);
	analog_print_analogmode();
	analog_array_print(analog);
}

void analog_print_max()
{
	printf(ESC_RED);
	printf("analog_print_max\r\n");
	analog_array_print(analogmax);
	printf(ESC_DEF);
}

void analog_print_min()
{
	printf(ESC_CYA);
	printf("analog_print_min\r\n");
	analog_array_print(analogmin);
	printf(ESC_DEF);
}

void analog_set_on_flash(uint16_t *analogmin_, uint16_t *analogmax_)
{
	printf("analog_set_to_flash()\r\n");
	for(unsigned int i = 0; i < CALIBRATIONSIZE; i++)
	{
		printf(ESC_MAG);
		printf("flash.analogmin[%2d] = %5d, flash.analogmax[%2d] = %5d\r\n", i, flashbuffer.analogmin[i], i, flashbuffer.analogmax[i]);
		printf(ESC_DEF);
		*(analogmin_ + i) = analogmin[i];
		*(analogmax_ + i) = analogmax[i];
		printf(ESC_GRE);
		printf("flash.analogmin[%2d] = %5d, flash.analogmax[%2d] = %5d\r\n", i, flashbuffer.analogmin[i], i, flashbuffer.analogmax[i]);
		printf(ESC_DEF);
	}
}

void analog_set_from_flash(uint16_t *analogmin_, uint16_t *analogmax_)
{
	#if D_ANALOG
	printf("analog_set_from_flash()\r\n");
	#endif
	for(unsigned int i = 0; i < CALIBRATIONSIZE; i++)
	{
		#if D_ANALOG
		printf("flash.analogmin[%2d] = %5d, flash.analogmax[%2d] = %5d\r\n", i, flashbuffer.analogmin[i], i, flashbuffer.analogmax[i]);
		#endif
		analogmin[i] = *(analogmin_ + i);
		analogmax[i] = *(analogmax_ + i);
		#if D_ANALOG
		printf("flash.analogmin[%2d] = %5d, flash.analogmax[%2d] = %5d\r\n", i, flashbuffer.analogmin[i], i, flashbuffer.analogmax[i]);
		#endif
	}
}

void analog_set_calibrationsize(uint8_t calibrationsize_)
{
	calibrationsize = calibrationsize_;
}

uint8_t analog_read_calibrationsize()
{
	return calibrationsize;
}

void analog_set_analogmode(AnalogMode analogmode_)
{
	analogmode = analogmode_;
}

AnalogMode analog_read_analogmode()
{
	return analogmode;
}

void analog_calibration_start()
{
	analog_set_analogmode(analogmode_all);
    for(unsigned char i = 0; CALIBRATIONSIZE > i; i++)
    {
        analogmax[i] = 0;
        analogmin[i] = 4096;
    }
	analog_print_max();
	analog_print_min();
	analog_sensor_start();
}

void analog_calibration_stop()
{
	/* analog_calibration_stop */
	analog_set_analogmode(analogmode_all);
	/* HAL_ADC_Stop_DMA */
	analog_stop();
	analog_print_max();
	analog_print_min();
	/* flashbuffer.analogmin/max = analogmin/max */
	analog_set_on_flash(flashbuffer.analogmin, flashbuffer.analogmax);
	flash_write();
}

void analog_init()
{
	analog_set_calibrationsize(CALIBRATIONSIZE);
    if(HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }
}

void analog_start()
{
	#if D_ANALOG
	printf("analog_sensor_start()\r\n");
	#endif
	analog_sensor_start();
}

void analog_stop()
{
	analog_sensor_stop();
}

void analog_sensor_start()
{
	#if D_ANALOG
	printf("sensgettime = 0\r\nHAL_ADC_Start_DMA()\r\n");
	#endif
    sensgettime = 0;
    if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*) analograw, CALIBRATIONSIZE) != HAL_OK)
    {
        Error_Handler();
    }
}

void analog_sensor_stop()
{
	HAL_ADC_Stop_DMA(&hadc1);
}

uint16_t analog_sensor_get(unsigned char i)
{
	analograte[i] = 1000 * (analog[i] - analogmin[i]) / (float) (analogmax[i] - analogmin[i]);
#if USE_SIGMOID_TRACE
	analograte[i] = 1000 * sigmoid(analograte[i], (16 - i)/(float)800, 500);
#endif
	return analograte[i];
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
#if !ANALOG_CALIBRATION_IN_WHILE
	analog_get_and_sort();
#endif
}

void analog_get_and_sort()
{
    /* sort */
	if(sensgettime >= SENSGETCOUNT)
    {
		#if ANALOG_CALIBRATION_IN_WHILE
		// printf("sensgettime >= SENSGETCOUNT\r\n");
		#endif
		sensgettime = 0;
		for(unsigned char index = 0; index < CALIBRATIONSIZE; index++)
        {
			/* main sort */
			#if ANALOG_CALIBRATION_IN_WHILE
			// printf("main sort\r\n");
			#endif
			for(unsigned char count = 0; count < SENSGETCOUNT; count++)
            {
				for(unsigned char alphaindex = 0; alphaindex > count; alphaindex--)
                {
					uint16_t analogbuffer = analogbuffers[alphaindex - 1][index];
					analogbuffers[alphaindex - 1][index] = analogbuffers[alphaindex][index];
					analogbuffers[alphaindex][index] = analogbuffer;
				}
			}

			/* get middle */
			analog[index] = analogbuffers[(int) SENSGETCOUNT / 2][index];
			#if ANALOG_CALIBRATION_IN_WHILE
			// printf("get middle\r\n");
			// printf("analogmiddle[%2d] = %5d\r\n", index, analog[index]);
			#endif
			
			/* get max and min */
			#if ANALOG_CALIBRATION_IN_WHILE
			analog_print_analogmode();
			#endif
			analogmax[index] = (analogmax[index] < analog[index]) ? analog[index] : analogmax[index];
			analogmin[index] = (analogmin[index] > analog[index]) ? analog[index] : analogmin[index];
			#if ANALOG_CALIBRATION_IN_WHILE
			printf("analogmin[%2d] = %5d, analogmax[%2d] = %5d\r\n", index, analogmin[index], index, analogmax[index]);
			#endif
		}
	}

    /* get sensor raw value */
	#if ANALOG_CALIBRATION_IN_WHILE
	// printf(" get sensor raw value ... \r\n");
	// printf("sensgettime = %2d\r\n", sensgettime);
	// analog_array_print(analograw);
	#endif
	for(unsigned char index = 0; CALIBRATIONSIZE > index; index++)
    {
		#if ANALOG_CALIBRATION_IN_WHILE
		// printf("analogbuffers[%2d][%2d] = %5d\r\n", sensgettime, index, analograw[index]);
		#endif
		analogbuffers[sensgettime][index] = analograw[index];
	}
	sensgettime++;
}
