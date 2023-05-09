#include "tim6.h"

#if D_TIM6
float leftmotor, rightmotor;
#endif

void tim6_init()
{
    motor_init();
    HAL_TIM_Base_Stop_IT(&htim6);
}

void tim6_start()
{
#if D_TIM6
    leftmotor = 0;
    rightmotor = 0;
#endif
    //! 速度補正
    fixed_section_start();
    motor_start();
	HAL_TIM_Base_Start_IT(&htim6);	// PID
}

void tim6_stop()
{
    motor_stop();
	HAL_TIM_Base_Stop_IT(&htim6);
    course_stop();
}

void tim6_main()
{
    PlayMode playmode;

    playmode = rotary_read_playmode();

    if(motor_read_enable() && playmode != motor_free)
    {
        #if !(TRACER_TUNING || VELOTRACE_TUNING)
        switch(playmode)
        {
            case tracer_tuning:
                leftmotor   = 0 + tim7_read_left();
                rightmotor  = 0 + tim7_read_right();
                break;
            case velotrace_tuning:
                leftmotor   = tim10_read_left() + 0;
                rightmotor  = tim10_read_right() + 0;
                break;
            default:
                leftmotor   = tim10_read_left() + tim7_read_left();
                rightmotor  = tim10_read_right() + tim7_read_right();
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
    }
    else
    {
        leftmotor = 0;
        rightmotor = 0;
    }
}

void tim6_d_print()
{
    #if D_TIM6
    printf("\r\n");
    printf("tim6.c > tim6_d_print() > motor_enable = %1d, leftmotor = %5.3f, rightmotor = %5.3f\r\n", motor_read_enable(), leftmotor, rightmotor); 
    #endif
}
