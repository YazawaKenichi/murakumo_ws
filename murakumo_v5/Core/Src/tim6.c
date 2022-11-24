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
    #if !VELOTRACE_IN_TIM10
    velotrace_init(1);
    #endif
    tracer_init(1);
    HAL_TIM_Base_Stop_IT(&htim6);
}

void tim6_start()
{
    /* analogmin/max = FlashBuffer.analogmin/max */
    analog_set_from_flash(flashbuffer.analogmin, flashbuffer.analogmax);
    /* sensgettime = 0, HAL_ADC_Start_DMA() */
    printf("analog_start()\r\n");
    analog_start();
    #if !VELOTRACE_IN_TIM10
    /* samplingtime = 0, s_error = 0, before_error = 0, if search ( p/i/d = [0], target = [0] ) */
    printf("velotrace_start()\r\n");
    velotrace_start();
    #endif
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
    motor_stop();
    tracer_stop();
    #if !VELOTRACE_IN_TIM10
    velotrace_stop();
    #endif
    analog_stop();
}

void tim6_main()
{
    #if !D_TIM6
    uint16_t analogl, analogr;
    int direction;
    double leftmotor, rightmotor;
    #endif
    // #if !VELOTRACE_TUNING
    analogl = 0;
    analogr = 0;

	#if TEMPORARY
    leftmotor   = velotrace_solve(tim10_read_velocity()) + 0;
    rightmotor  = velotrace_solve(tim10_read_velocity()) - 0;
    motor_set(leftmotor, rightmotor);
	#endif

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

    #if D_TIM6_WHILE
    printf("analogl = %5d, analogr = %5d\r\n", analogl, analogr);
    #endif

    #if TIM6_EMERGENCY_STOP
    if(analogl + analogr >= 980 * analog_read_calibrationsize())
    {
        #if !VELOTRACE_IN_TIM10
        velotrace_set_target(0);
        #endif
        motor_enable(0);
    }
    #endif

    // ( direction > 0 ) is ( analogl > analogr ) i.e. left is black, right is white.
    // When ( direction > 0 ) , must turn right.
    direction = (analogl - analogr);	// difference

    #if D_TIM6_WHILE
    printf("direction = %5d\r\n", direction);
    printf("motor_read_enable() = %1d\r\n", motor_read_enable());
    #endif

    // #endif  /* !VELOTRACE_TUNING */

    if(motor_read_enable())
    {
        #if D_TIM6_WHILE
        rotary_print_playmode();
        #endif

        #if !D_TIM6_IGNORE
        switch(rotary_read_playmode())
        {
            case tracer_tuning:
                leftmotor   = 0 + tracer_solve(direction);
                rightmotor  = 0 - tracer_solve(direction);
                break;
            case velotrace_tuning:
                #if !VELOTRACE_IN_TIM10
                leftmotor   = velotrace_solve(tim10_read_velocity()) + 0;
                rightmotor  = velotrace_solve(tim10_read_velocity()) - 0;
                #else
                leftmotor   = tim10_velotrace_solve();
                rightmotor  = tim10_velotrace_solve();
                #endif
                break;
            default:
                #if !VELOTRACE_IN_TIM10
                leftmotor   = velotrace_solve(tim10_read_velocity()) + tracer_solve(direction);
                rightmotor  = velotrace_solve(tim10_read_velocity()) - tracer_solve(direction);
                #else
                leftmotor   = tim10_velotrace_solve() + tracer_solve(direction);
                rightmotor  = tim10_velotrace_solve() - tracer_solve(direction);
                #endif
                break;
        }

        #else

        #if TRACER_TUNING
        leftmotor   = 0 + tracer_solve(direction);
        rightmotor  = 0 - tracer_solve(direction);
        #endif
        #if !VELOTRACE_IN_TIM10
        #if VELOTRACE_TUNING
        leftmotor   = velotrace_solve(tim10_read_velocity()) + 0;
        rightmotor  = velotrace_solve(tim10_read_velocity()) - 0;
        #endif
        #if !TRACER_TUNING && !VELOTRACE_TUNING
        leftmotor   = velotrace_solve(tim10_read_velocity()) + tracer_solve(direction);
        rightmotor  = velotrace_solve(tim10_read_velocity()) - tracer_solve(direction);
        #endif
        #endif /* !VELOTRACE_IN_TIM10 */

        leftmotor   = tim10_velotrace_solve();// + tracer_solve(direction);
        rightmotor  = tim10_velotrace_solve();// - tracer_solve(direction);

        #endif /* D_TIM6_IGNORE */

        #if D_TIM6_WHILE
        // printf("tracer_solve(direction) = %7.2f velotrace_solve(tim10_read_velocity()) = %7.2f\r\n", tracer_solve(direction), velotrace_solve(tim10_read_velocity()));
        #endif
    }
    else
    {
        leftmotor = 0;
        rightmotor = 0;
    }

    #if D_TIM6_WHILE
    printf("leftmotor = %7.2f, rightmotor = %7.2f\r\n", leftmotor, rightmotor);
    #endif

    if(rotary_read_playmode() == motor_free)
    {
        motor_set(0, 0);
    }
    else
    {
		#if !TEMPORARY
        motor_set(leftmotor, rightmotor);
		#endif	/* TEMPLATE */
    }
}

void tim6_d_print()
{
    #if D_TIM6
    printf("tim6.c > tim6_d_print() > analogl = %5d, analogr = %5d, direction = %5d\r\n", analogl, analogr, direction);
    #if !VELOTRACE_IN_TIM10
    printf("tim6.c > tim6_d_print() > tracer_solve(direction) = %7.2f velotrace_solve(tim10_read_velocity()) = %7.2f\r\n", tracer_solve(direction), velotrace_solve(tim10_read_velocity()));
    #endif
    printf("tim6.c > tim6_d_print() > leftmotor = %5.3f, rightmotor = %5.3f\r\n", leftmotor, rightmotor); 
    #endif
}
