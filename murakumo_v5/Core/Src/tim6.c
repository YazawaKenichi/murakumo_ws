#include "tim6.h"

#if D_TIM6
uint16_t analogl, analogr;
int direction;
double leftmotor, rightmotor;
#endif

void tim6_init()
{
    motor_init();
    analog_init();
    velotrace_init(1);
    tracer_init(1);
}

void tim6_start()
{
    /* analogmin/max = FlashBuffer.analogmin/max */
    analog_set_from_flash(flashbuffer.analogmin, flashbuffer.analogmax);
    HAL_Delay(3000);
    /* sensgettime = 0, HAL_ADC_Start_DMA() */
    printf("analog_start()\r\n");
    analog_start();
    /* samplingtime = 0, s_error = 0, before_error = 0, if search ( p/i/d = [0], target = [0] ) */
    printf("velotrace_start()\r\n");
    velotrace_start();
    /* samplingtime = 0, s_error = 0, before_error = 0 */
    printf("tracer_start()\r\n");
    tracer_start();

    printf("motor_start()\r\n");
    #if D_TIM6
    analogl = 0;
    analogr = 0;
    direction = 0;
    leftmotor = 0;
    rightmotor = 0;
    #endif
    motor_start();
	HAL_TIM_Base_Start_IT(&htim6);	// PID
}

void tim6_stop()
{
	HAL_TIM_Base_Stop_IT(&htim6);
    analog_stop();
    motor_stop();
}

void tim6_main()
{
    #if !D_TIM6
    uint16_t analogl, analogr;
    int direction;
    double leftmotor, rightmotor;
    #endif
    analogl = 0;
    analogr = 0;

    for(unsigned char i = 0; i < analog_read_calibrationsize(); i++)
    {
        if(i % 2 == 0)
        {
            analogl += analog_sensor_get(i);
        }
        else
        {
            analogr += analog_sensor_get(i);
        }
    }

    if(analogl + analogr >= 980 * analog_read_calibrationsize())
    {
        velotrace_set_target(0);
        motor_enable(0);
    }

    // ( direction > 0 ) is ( analogl > analogr ) i.e. left is black, right is white.
    // When ( direction > 0 ) , must turn right.
    direction = (analogl - analogr);	// difference

    if(analogl + analogr <= 700 * analog_read_calibrationsize())
    {
        direction = 0;
    }

    if(motor_read_enable())
    {
        switch(rotary_read_playmode())
        {
            case tracer_tuning:
                leftmotor   = 0 + tracer_solve(direction);
                rightmotor  = 0 - tracer_solve(direction);
                break;
            case velotrace_tuning:
                leftmotor   = velotrace_solve(tim10_read_velocity()) + 0;
                rightmotor  = velotrace_solve(tim10_read_velocity()) - 0;
                break;
            default:
                leftmotor   = velotrace_solve(tim10_read_velocity()) + tracer_solve(direction);
                rightmotor  = velotrace_solve(tim10_read_velocity()) - tracer_solve(direction);
                break;
        }
    }
    else
    {
        leftmotor = 0;
        rightmotor = 0;
    }

    if(rotary_read_playmode() == motor_free)
    {
        motor_set(0, 0);
    }
    else
    {
        motor_set(leftmotor, rightmotor);
    }
}

void tim6_d_print()
{
    #if D_TIM6
    printf("tim6.c > tim6_d_print() > analogl = %5d, analogr = %5d, direction = %5d, tracer_solve(direction) = %7.3f, leftmotor = %5.3f, rightmotor = %5.3f\r\n", analogl, analogr, direction, tracer_solve(direction), leftmotor, rightmotor);
    #endif
}
