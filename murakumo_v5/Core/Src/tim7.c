#include "tim7.h"

double tim7_left, tim7_right;
char tim7_emergency;

#if D_TIM7
unsigned char i_count, i_start;
#endif

void tim7_init()
{
    /* init */
    #if D_TIM7
    printf("tim7.c > tim7_init() > ");
    #endif
    analog_init();
    tracer_init(1);
    HAL_TIM_Base_Stop_IT(&htim7);
}

void tim7_start()
{
    /* start */
    #if D_TIM7
    printf("tim7.c > tim7_start() > ");
    #endif
    tim7_set_emergency(0);
    tim7_left = 0;
    tim7_right = 0;
    analog_set_from_flash(flashbuffer.analogmin, flashbuffer.analogmax);
    if(rotary_read_playmode() == search)
    {
        analog_set_analogmode(analogmode_short);
    }
    else
    {
        analog_set_analogmode(analogmode_all);
    }

    /* 本番直前なので無条件に analogmode_short にする */
    analog_set_analogmode(analogmode_short);

    analog_start();
    tracer_start();
    HAL_TIM_Base_Start_IT(&htim7);
}

void tim7_stop()
{
    /* stop */
    #if D_TIM7
    printf("tim7.c > tim7_stop() > ");
    #endif
    HAL_TIM_Base_Stop_IT(&htim7);
    motor_stop();
    tracer_stop();
    analog_stop();
}

void tim7_main()
{
    /* main */
    int direction;

    direction = tim7_read_direction();

    #if D_TIM7_WHILE
    printf("tim7.c > tim7_main() > ");
    printf("analogl = %5d, analogr = %5d, direction = %5d\r\n", analogl, analogr, direction);
    #endif

    tim7_left   =   tracer_solve(direction);
    tim7_right  = - tim7_left;

    #if D_TIM7_WHILE
    printf("tim7.c > tim7_main() > ");
    printf("tim7_left = %7.2f, tim7_right = %7.2f\r\n", tim7_left, tim7_right);
    #endif
}

/* this method is private */
int tim7_read_direction()
{
    uint16_t analogl, analogr;
	#if !D_TIM7
    unsigned char i_count, i_start;
	#endif

    analogl = 0;
    analogr = 0;

    switch(analog_read_analogmode())
    {
        case analogmode_calibrating:
            break;
        case analogmode_short:
            i_count = 12;
            i_start = 0;
            break;
        case analogmode_long:
            i_count = 4;
            i_start = 12;
            break;
        case analogmode_all:
            i_count = 16;
            i_start = 0;
            break;
        default:
            /* unknown analogmode ... x_x */
            break;
    }

    for(unsigned char i = i_start; i < i_count; i++)
    {
        #if D_TIM7_WHILE
        printf("tim7.c > tim7_main() > for() > ");
        printf("i = %2d", i);
        #endif
        if(i % 2 == 0)
        {
            #if D_TIM7_WHILE
            printf("  odd\r\n");
            #endif
            analogl += analog_sensor_get(i);
        }
        else
        {
            #if D_TIM7_WHILE
            printf(" even\r\n");
            #endif
            analogr += analog_sensor_get(i);
        }
    }

    if(analogl + analogr >= TIM7_EMERGENCY_THRESHOLD * i_count)
    {
    	tim7_main_emergency();
    }

    return analogl - analogr;
}

void tim7_main_emergency()
{
	switch_reset_enter();
}

void tim7_set_emergency(char emergency_)
{
    tim7_emergency = emergency_;
}

char tim7_read_emergency()
{
    return tim7_emergency;
}

double tim7_read_left()
{
    #if D_TIM7_WHILE
    printf("tim7.c >  tim7_read_left() >  tim7_left = %7.2f\r\n", tim7_left);
    #endif
    return tim7_left;
}

double tim7_read_right()
{
    #if D_TIM7_WHILE
    printf("tim7.c > tim7_read_right() > tim7_right = %7.2f\r\n", tim7_right);
    #endif
    return tim7_right;
}

void tim7_d_print()
{
    /* d_print */
    #if D_TIM7
    printf("tim7.c > tim7_d_print() > ");
    printf("i_count = %3d, i_start = %3d\r\n", i_count, i_start);
    analog_d_print();
    #endif
}
