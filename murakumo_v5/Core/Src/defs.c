#include "../Inc/defs.h"

uint8_t rotary_read() {
	uint8_t _rotaryvalue = 0;
	_rotaryvalue += (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)) ? 0 : 1;	// Rotary1
	_rotaryvalue += (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)) ? 0 : 1;	// Rotary2
	_rotaryvalue += (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)) ? 0 : 1;	// Rotary4
	_rotaryvalue += (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)) ? 0 : 1;	// Rotary8
	return _rotaryvalue;
}

#if USE_LED
void led_rgb(char r, char g, char b) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, (r) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// LED_R ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, (g) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// LED_G ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, (b) ? GPIO_PIN_RESET : GPIO_PIN_SET);// LED_B ON
}
void set_led(char mask, char value) {
	if (mask & 0b01) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,
				(value & 0b01) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// RIGHT
	}
	if (mask & 0b10) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,
				(value & 0b10) ? GPIO_PIN_RESET : GPIO_PIN_SET);	// LEFT
	}
}
#endif

void playmode_print() {
#if D_PLAYMODE
	printf("playmode = ");
	switch(playmode)
	{
		case calibration:
			printf("calibration\r\n");
			break;
		case search:
			printf("search\r\n");
			break;
		case accel:
			printf("accel\r\n");
			break;
		case pid_tuning:
			printf("pid_tuning\r\n");
			break;
		case zero_trace:
			printf("zero_trace\r\n");
			break;
		case flash_print:
			printf("flash_print\r\n");
		default:
			printf("unknown;;\r\n");
			break;
	}
	#endif
}

void d_print() {
	printf("////////// d_print //////////\r\n");

#if D_PLAYMODE
	playmode_print();
#endif

#if D_ANALOG || D_ANALOGRATE
#if CALIBRATIONSIZE != 16
#if (CALIBRATIONSIZE == 4)
	printf(ESC_DEF);
#endif
#if CALIBRATIONSIZE == 12
	printf(ESC_RED);
#endif
#else
	printf(ESC_DEF);
#endif

#if !D_ANALOGRATE
	// only use normal sensor
	printf("\x1b[23C");	// Cursor move right *24
	printf("%4d, %4d | %4d, %4d\r\n", analog[12], analog[14], analog[15],
			analog[13]);
#else
	printf("\x1b[23C");	// Cursor move right *24
	printf("%4d, %4d | %4d, %4d\r\n", analograte[12], analograte[14], analograte[15],
			analograte[13]);
#endif	// D_ANALOGRATE

#if CALIBRATIONSIZE == 4
	printf(ESC_RED);
#endif
#if (CALIBRATIONSIZE == 12)
	printf(ESC_DEF);
#endif

#if !D_ANALOGRATE
	printf("%4d, %4d, %4d, %4d, %4d, %4d | %4d, %4d, %4d, %4d, %4d, %4d\r\n",
			analog[0], analog[2], analog[4], analog[6], analog[8], analog[10],
			analog[11], analog[9], analog[7], analog[5], analog[3],
			analog[1]);
#else
	printf("%4d, %4d, %4d, %4d, %4d, %4d | %4d, %4d, %4d, %4d, %4d, %4d\r\n",
			analograte[0], analograte[2], analograte[4], analograte[6], analograte[8], analograte[10],
			analograte[11], analograte[9], analograte[7], analograte[5], analograte[3],
			analograte[1]);
#endif	// D_ANALOGRATE
	printf("\r\n");

#endif	// D_ANALOG

#if D_ENCODER
	printf("encoder_l = %d, encoder_r = %d \r\n",
			encoder_l, encoder_r);
/*
	printf("encoder_l = %d, encoder_r = %d \r\ndvl = %d, dvr = %d\r\n",
			encoder_l, encoder_r, dvl, dvr);
	printf("lengthl = %d, lengthr = %d \r\nvelocityl = %d, velocityr = %d\r\n",
			lengthl, lengthr, velocityl, velocityr);
*/
	/*
	printf("TIM1->CNT = %5d, TIM3->CNT = %5d\r\nencoder_l = %5d, encoder_r = %5d\r\n", TIM1->CNT, TIM3->CNT, encoder_l, encoder_r);
	*/

	printf("encoder_lr = %7d, %7d\r\nencoder = %7d\r\ns_encoder = %7d\r\ns_velocity = %7.3f\r\n", encoder_l, encoder_r, encoder, s_encoder, s_velocity);
#endif

#if D_SLOWSTART
	printf("slow = %1d\r\n", slow);
	printf("starting_length = %5f\r\n", starting_length);
#endif

#if D_PWM
//	printf("pwmstepoutput = %5d, pwmsteptime = %5d, pwmstepud = %d\r\n", pwmstepoutput, pwmsteptime, pwmstepud);
#endif

#if D_ROTARY
	printf("rotary_value = %x\r\n", rotary_value);
#endif

#if D_SWITCH
	printf("enter = %d\r\n", enter);
#endif

#if D_FLASH
	printf("rightmarkercount = %1d\r\n", rightmarkercount);
	printf("sampling_length = %5f\r\n", mm_length);
	printf("sampling_time = %5d\r\n", sampling_time);
	printf("course_state_time = %4d\r\n", course_state_time);

#if D_IMU
	printf("mm_length = %5.3f\r\n", mm_length);
	printf("inertial.gyro.z = %5d, my_gyro.z = %7.3f\r\n", inertial.gyro.z, my_gyro.z);
	printf("my_gyro.z / mm_length = %8.5f\r\n", (double) my_gyro.z / (double) mm_length);
#endif

#if !D_COURSE_SAVING
	printf("flash_buffer.radius[%4d] = %8.3f\r\n", course_state_time,
			flash_buffer.radius[course_state_time]);
#endif
#endif

#if D_VELOCITY_CONTROL
	#if !VELOCITY_CONTROL_RELATIVE
		printf("velocity_error = %5.3f, s_velocity_error = %5.3f\r\n",
				velocity_error_l, s_velocity_error_l);
		printf("velocity_next = %5.3f\r\n", velocity_next_l);
		printf("nextspeed = %5.3f\r\n", nextspeed_l);
		printf("leftmotor = %5.3f, rightmotor = %5.3f\r\n", leftmotor, rightmotor);
	#else	// VELOCITY_CONTROL_RELATIVE
		#if !D_VELOCITY_CONTROL_TIMER
		//	printf("LENGTHPERPULSE = %5.3f\r\n", LENGTHPERPULSE);
		/*
			printf("encoder = %3.1f\r\nLENGTHPERPULSE = %f\r\nvelocity = %5.3f\r\nvelocity_error = %5.3f, s_velocity_error = %5.3f\r\nvelocity_next = %5.3f\r\nnextspeed = %5.3f\r\n",
					(encoder_l + encoder_r) / (double)2.0f, LENGTHPERPULSE, velocity, velocity_error, s_velocity_error, velocity_next);
		*/
		#else	// D_VELOCITY_CONTROL_TIMER
			printf("rightmarkercount = %1d\r\n", rightmarkercount);
			printf("stoptime = %11lf\r\n", stoptime);
		#endif	// D_VELOCITY_CONTROL_TIMER
	#endif	// VELOCITY_CONTROL_RELARIVE
#endif	// D_VELOCITY_CONTROL

#if D_MOTOR
	printf("leftmotor = %5.3f, rightmotor = %5.3f\r\n", leftmotor, rightmotor);
#endif

#if D_MATH
#if USE_SIGMOID_TRACE
	for(int i = 0; i < calibrationsize; i++)
	{
		printf("sigmoid = %5.3f\r\n", 1000 * sigmoid(analograte[i], (16 - i)/(double)800, 500));
	}
#endif
#endif

}	// d_print

////////////////////////////// d_print //////////////////////////////

double low_pass_filter(double val, double pre_val, double gamma) {
	return (double) (gamma * (double) pre_val
			+ (double) (1 - gamma) * (double) val);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle) {
	// sort
	if (sensgettime >= SENSGETCOUNT) {
		sensgettime = 0;
		for (unsigned char index = 0; index < CALIBRATIONSIZE; index++) {
			for (unsigned char count = 0; count < SENSGETCOUNT; count++) {
				for (unsigned char alphaindex = 0; alphaindex > count;
						alphaindex--) {
					uint16_t analogbuffer = analogbuffers[alphaindex - 1][index];
					analogbuffers[alphaindex - 1][index] =
							analogbuffers[alphaindex][index];
					analogbuffers[alphaindex][index] = analogbuffer;
				}
			}
			analog[index] = analogbuffers[(int) SENSGETCOUNT / 2][index];
			// get maxvalue and minimumvalue
			uint16_t analogbuf;
			analogbuf = analog[index];
			analogmax[index] =
					(analogmax[index] < analogbuf) ?
							analogbuf : analogmax[index];
			analogmin[index] =
					(analogmin[index] > analogbuf) ?
							analogbuf : analogmin[index];
		}
	}
	// sensorget
	for (unsigned char index = 0; CALIBRATIONSIZE > index; index++) {
		analogbuffers[sensgettime][index] = analograw[index];
	}
	sensgettime++;
}

#ifndef __OBSOLETE_MATH
double pow(double a, double b) {
	double r;
	r = 1;
	// printf("pow(%5.3f, %5.3f)\r\n", a, b);
	if(b < 0)
	{
		for(int i = -b; i > 0; i--) // xx b != int xx
		{
			r = (double) r / a;
		}
	}
	else
	{
		for(int i = b; i > 0; i--)
		{
			r = (double) r * a;
		}
	}

	return r;
}

double exp(double a)
{
	// printf("exponential(%5.3f)\r\n", a);
	return pow(E, a);
}
#endif

double sigmoid(double x, double a, double x0) {
	// printf("pow(%5.3f, %5.3f, %5.3f)\r\n", x, a, x0);
	return 1 / (double) (1 + exp(-a * (x - x0)));
}

#if USE_FLASH
void eraseFlash(void) {
	FLASH_EraseInitTypeDef erase;
	erase.TypeErase = FLASH_TYPEERASE_SECTORS;
	erase.Sector = FLASH_SECTOR_11;
	erase.NbSectors = 1;
	erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	uint32_t pageError = 0;

	HAL_FLASHEx_Erase(&erase, &pageError);
}

void writeFlash(uint32_t address, uint8_t *data, uint32_t size)
{
#if USE_WRITE_FLASH
	HAL_FLASH_Unlock();
	eraseFlash();

	for (uint32_t add = address; add < (address + size); add++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, add, *data);
		data++;
	}

	HAL_FLASH_Lock();
#endif
}

void loadFlash(uint32_t address, uint8_t *data, uint32_t size)
{
	memcpy(data, (uint64_t*) address, size);
}
#endif

void sidesens_function()
{
#if USE_SIDESENSOR
	unsigned char subsens, first, second;

	subsens = read_sidesens();

	if (subsens != subsensbuf)
	{
		subsensbuf = subsens;
		marker += subsens << (2 * sidedeltacount);
		if (subsens == 0b00 && sidedeltacount != 0)
		{
			first = (marker & 0b0011);
			second = (marker & 0b1100) >> 2;
			if (second == 0b00)
			{
				if (first == 0b01)
				{
					// right -> stop
					markerstate = 0b01;
					if(rightmarkercount == 1 - 1)
					{
						rightmarkercount++;
						set_led(0b01, 0b01);
					}
					else if (rightmarkercount == 2 - 1)
					{
						// stop_motion
						rightmarkercount++;
						course_state_function();
						slow = 1;
					}
				}
				else if (first == 0b10)
				{
					// left -> curve
					markerstate = 0b10;
#if LEFTMARKER_SAMPLING
					course_state_function();
#endif
				markerstate = 0;
#if USE_ANALOG
					sdirection = 0;
#endif
#if USE_FLASH && USE_VELOCITY_CONTROL
#if USE_VELOCITY_CONTROL
					s_velocity = 0;
#endif
#endif	// USE_FLASH && USE_VELOCITY_CONTROL
				}
				else
				{
					// cross
					markerstate = 0b11;
				}
			}
			else
			{
				// cross
				markerstate = 0b11;
			}
			sidedeltacount = 0;
			marker = 0;
#if !LEFTMARKER_SAMPLING
			markerstate = 0;
#endif
		}
		else
		{
			sidedeltacount++;
		}
	}
#endif	// USE_SIDESENSOR
}

void encoder_set_function() {
#if USE_ENCODER
	// 1ms
	encoder_l = TIM1->CNT - ENCODER_MIDDLE;
	encoder_r = -(TIM3->CNT - ENCODER_MIDDLE);

	TIM1->CNT = ENCODER_MIDDLE;
	TIM3->CNT = ENCODER_MIDDLE;

	encoder = (double) (encoder_l + encoder_r) / 2;
	velocity = (double) encoder * LENGTHPERPULSE;
#endif	// USE_ENCODER
}

void slow_start_function() {
#if USE_SLOWSTART
	if (slow) {
		starting_length += velocity;
		if (starting_length < THRESHOLD_STARTING_LENGTH) {
			velocity_target = 100;
			kp = 10;
			kd = 15;
			ki = 0;
		} else {
			velocity_target = base_velocity_target;
			kp = base_p;
			ki = base_i;
			kd = base_d;
			slow = 0;
		}
	}
#endif	// USE_MOTOR && USE_SLOWSTART
}

void velocity_control_function() {
#if USE_VELOCITY_CONTROL
	if (playmode != zero_trace) {
		velocity_error = velocity_target - velocity;
		s_velocity_error = s_velocity_error + velocity_error;

		velocity_next = (double) VKP * velocity_error
				+ (double) VKI * s_velocity_error;
		commonspeed = (double) velocity_next * (double) PWMMAX
				/ (double) VELOCITY_MAX;
	} else {
		commonspeed = 0;
	}
#endif	// USE_VELOCITY_CONTROL
}

void velocity_control_switch_function()
{
#if USE_FLASH
#if !D_COURSE_SAVING
    if(flash_buffer.radius[course_state_time] < THRESHOLDRADIUS)
    {
        // deceleration
        velocity_target = low_velo.velocity_target[rv];
        kp = low_velo.kp[rv];
        kd = low_velo.kd[rv];
        ki = low_velo.ki[rv];
    }
    else
    {
        // acceleration
        velocity_target = high_velo.velocity_target[rv];
        kp = high_velo.kp[rv];
        kd = high_velo.kd[rv];
        ki = high_velo.ki[rv];
    }
#endif
#endif
}

void course_state_function()
{
	if(playmode == search)
	{
		if(course_state_time + 1 >= COURSE_STATE_SIZE)	// sizeof(flash_buffer.radius) / sizeof(flash_buffer.radius[0]))
		{
			led_rgb(1, 1, 0);	// Yellow
			motorenable = 0;
		}
		else
		{
#if USE_COURSE_STATE_TIME
			course_state_time++;
#endif
			flash_buffer.course_state_time_max = course_state_time;
			my_gyro.z = theta * RADPERDEG;
	//		my_gyro.z *= RADPERDEG;
	#if !D_COURSE_SAVING
	#if !USE_LR_DIFFERENCE
			flash_buffer.radius[course_state_time] = (double) my_gyro.z / (double) mm_length;
	#else	// USE_LR_DIFFERENCE
			flash_buffer.radius[course_state_time] = (double) TREAD * (double) ((left_length) + (right_length)) / (double) ((left_length) - (right_length)) / (double) 2;
	#endif	// USE_LR_DIFFERENCE
	#else	// D_COURSE_SAVING
	#if !USE_LR_DIFFERENCE
			flash_buffer.igz[course_state_time] = my_gyro.z;
			flash_buffer.len[course_state_time] = mm_length;
	#endif	// !USE_LR_DIFFERENCE
	#endif	// D_COURSE_SAVING
	#if USE_LR_DIFFERENCE
			left_length = 0;
			right_length = 0;
	#endif
			mm_length = 0;
			my_gyro.z = 0;
		}
	}
	if(playmode == accel)
	{
		velocity_control_switch_function();
		if(course_state_time + 1 >= COURSE_STATE_SIZE)	// sizeof(flash_buffer.radius) / sizeof(flash_buffer.radius[0]))
		{
			led_rgb(1, 1, 0);	// Yellow
			motorenable = 0;
		}
		else
		{
#if USE_COURSE_STATE_TIME
			course_state_time++;
#endif
		}
	}
}

void radius_calc()
{
#if USE_IMU
	/*
	if (!slow && rightmarkercount && rv == 0x01)	// SAMPLING_LENGTH /
	{
		sampling_time++;
		IMU_read();
		my_gyro.z += inertial.gyro.z;
		m_velocity += velocity;
		if (sampling_time >= SAMPLING_TIME)
		{
			flash_buffer.radius[course_state_time] = my_gyro.z / m_velocity;
			if (course_state_time == 0)
			{
				flash_buffer.radius[course_state_time] = THRESHOLDRADIUS;
			}
			if (rightmarkercount == 2)
			{
				flash_buffer.radius[course_state_time] = THRESHOLDRADIUS;
				if (motorenable == 0)
				{
					flash_buffer.course_state_time_max = course_state_time;
				}
			}
			course_state_time++;
			m_velocity = 0;
			my_gyro.z = 0;
			sampling_time = 0;
		}
	}
	*/
#endif	// USE_IMU
}

void led_brink()
{
#if USE_LED
	uint16_t TIMTIM = 1000;

	if (timtim1 % TIMTIM == 0)	// 1 ms / roop
	{
		set_led(0b10, 0b10);
	}
	if (timtim1 % TIMTIM == (int) (TIMTIM / 2))
	{
		set_led(0b10, 0b00);
	}
	timtim1 = timtim1 + 1;
	if (timtim1 >= 60000)
	{
		timtim1 = 0;
	}
#endif
}

void pid_gain_initialize()
{
	for(int i = 0; i < 16; i++)
	{
		low_velo.velocity_target[i] = VELOCITY_TARGET_LOW;
		high_velo.velocity_target[i] = VELOCITY_TARGET_HIGH;
	}
	low_velo.kp[0] = KP_LOW;
	low_velo.ki[0] = KI_LOW;
	low_velo.kd[0] = KD_LOW;
	high_velo.kp[0] = KP_HIGH;
	high_velo.ki[0] = KI_HIGH;
	high_velo.kd[0] = KD_HIGH;
	for(int i = 1; i < 16; i++)
	{
		low_velo.kp[i] = KP_LOW + (i - 1) * KP_LOW_TOLERANCE;
		low_velo.ki[i] = KI_LOW + (i - 1) * KI_LOW_TOLERANCE;
		low_velo.kd[i] = KD_LOW + (i - 1) * KD_LOW_TOLERANCE;
		high_velo.kp[i] = KP_HIGH + (i - 1) * KP_HIGH_TOLERANCE;
		high_velo.ki[i] = KI_HIGH + (i - 1) * KI_HIGH_TOLERANCE;
		high_velo.kd[i] = KD_HIGH + (i - 1) * KD_HIGH_TOLERANCE;
	}
}

void pid_initialize()
{
	velocity_target = low_velo.velocity_target[rv];
	kp = low_velo.kp[rv];
	kd = low_velo.kd[rv];
	ki = low_velo.ki[rv];
	if(playmode == accel)
	{
		velocity_target = high_velo.velocity_target[rv];
		kp = high_velo.kp[rv];
		kd = high_velo.kd[rv];
		ki = high_velo.ki[rv];
	}
#if USE_SLOWSTART
	slow = 1;
	starting_length = 0;
	base_velocity_target = velocity_target;
	base_p = kp;
	base_i = ki;
	base_d = kd;
#endif  // USE_SLOWSTART
}
