#include "tim6.h"

#if D_TIM6
double leftmotor, rightmotor;
#endif

void tim6_init()
{
    motor_init();
    // sidesensor_init();
    HAL_TIM_Base_Stop_IT(&htim6);
}

void tim6_start()
{
    printf("motor_start()\r\n");
    #if D_TIM6
    leftmotor = 0;
    rightmotor = 0;
    #endif
    sidesensor_start();
    motor_start();
	HAL_TIM_Base_Start_IT(&htim6);	// PID
}

void tim6_stop()
{
    motor_stop();
	HAL_TIM_Base_Stop_IT(&htim6);
    sidesensor_stop();
}

void tim6_main()
{
    #if !D_TIM6
    double leftmotor, rightmotor;
    #endif

    sidesensor_main();

    if(motor_read_enable())
    {
        #if D_TIM6_WHILE
        printf("tim6.c > tim6_main() > if() > ");
        rotary_print_playmode();
        #endif

        #if !(TRACER_TUNING || VELOTRACE_TUNING)
        switch(rotary_read_playmode())
        {
            case tracer_tuning:
                leftmotor   = 0 + tim7_read_left();
                rightmotor  = 0 + tim7_read_right();
                #if D_TIM6_WHILE
                printf("tim6.c > tim6_main() > if() > switch() case tracer_tuning > ");
                printf("leftmotor = %7.2f, rightmotor = %7.2f\r\n", leftmotor, rightmotor);
                #endif
                break;
            case velotrace_tuning:
                leftmotor   = tim10_read_left() + 0;
                rightmotor  = tim10_read_right() + 0;
                #if D_TIM6_WHILE
                printf("tim6.c > tim6_main() > if() > switch() case velotrace_tuning > ");
                printf("leftmotor = %7.2f, rightmotor = %7.2f\r\n", leftmotor, rightmotor);
                #endif
                break;
            default:
                leftmotor   = tim10_read_left() + tim7_read_left();
                rightmotor  = tim10_read_right() + tim7_read_right();
                #if D_TIM6_WHILE
                printf("tim6.c > tim6_main() > if() > switch() case default > ");
                printf("leftmotor = %7.2f, rightmotor = %7.2f\r\n", leftmotor, rightmotor);
                #endif
                break;
        }
        #else
        #if TRACER_TUNING
        leftmotor  =  tim7_read_left();
        rightmotor = tim7_read_right();
        #endif
        #if VELOTRACE_TUNING
        leftmotor  =  tim10_read_left();
        rightmotor = tim10_read_right();
        #endif
        #if VELOTRACE_TUNING && TRACER_TUNING
        leftmotor  =  tim10_read_left() +  tim7_read_left();
        rightmotor = tim10_read_right() + tim7_read_right();
        #endif
		#endif	/* !(TRACER_TUNING || VELOTRACE_TUNING) */

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
    printf("tim6.c > tim6_main() > ");
    printf("leftmotor = %7.2f, rightmotor = %7.2f\r\n", leftmotor, rightmotor);
    #endif

    if(rotary_read_playmode() == motor_free)
    {
        motor_set(0, 0);
    }
    else
    {
		#if !TEMPORARY
        if(sidesensor_read_markerstate() != stop)
        {
            motor_set(leftmotor, rightmotor);
        }
        else
        {
            switch_reset_enter();
            tim6_stop();
        }
		#endif	/* TEMPLATE */
    }

}

void tim6_d_print()
{
    #if D_TIM6
    printf("tim6.c > tim6_d_print() > leftmotor = %5.3f, rightmotor = %5.3f\r\n", leftmotor, rightmotor); 
    printf("tim6.c > tim6_d_print() > sidesensor_d_print() > ");
    sidesensor_d_print();
    #endif
}
