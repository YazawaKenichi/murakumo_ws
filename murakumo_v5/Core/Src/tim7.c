#include "tim7.h"

float tim7_left, tim7_right;
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
    tracer_init(TIM7_TIME_MS);
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
    printf("direction = %5d\r\n", direction);
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
    uint16_t short_middle;
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

    for(unsigned char i = i_start; i < (i_count + i_start); i++)
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
        if(i < SHORT_MIDDLE_SENSOR)
        {
            short_middle = analogl + analogr;
        }
    }

    if(analogl + analogr >= TIM7_EMERGENCY_THRESHOLD * i_count)
    {
    	// tim7_main_emergency();
    }

    //if(short_middle <= CLOSS_IGNORE_THRESHOLD * SHORT_MIDDLE_SENSOR && sidesensor_read_markerstate() == cross)
    if(short_middle <= CLOSS_IGNORE_THRESHOLD * SHORT_MIDDLE_SENSOR)
    {
        /* 交差判定 */
        analogl = 3 * (analog_sensor_get(12) + analog_sensor_get(14));
        analogr = 3 * (analog_sensor_get(13) + analog_sensor_get(15));
        /* 長い方のゲイン値にする */
        tim7_tracer_set_gain_long();
        led_write_led(0b11, 0b10);
    }
    else
    {
        /* その他判定 */
        /* 短い方のゲイン値にする（戻すって言った方が正しいかも） */
        tim7_tracer_set_gain_short();
        led_write_led(0b11, 0b01);
    }

#if D_TIM7_WHILE
	printf("tim7.c > tim7_main() > ");
	printf("analogl = %5d, analogr = %5d\r\n", analogl, analogr);
#endif

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

float tim7_read_left()
{
    #if D_TIM7_WHILE
    printf("tim7.c >  tim7_read_left() >  tim7_left = %7.2f\r\n", tim7_left);
    #endif
    return tim7_left;
}

float tim7_read_right()
{
    #if D_TIM7_WHILE
    printf("tim7.c > tim7_read_right() > tim7_right = %7.2f\r\n", tim7_right);
    #endif
    return tim7_right;
}

void tim7_d_print()
{
#if D_TIM7
    printf("tim7_left = %f, tim7_right = %f\r\n", tim7_left, tim7_right);
#endif
    analog_d_print();
    tracer_print_values();
}

void tim7_tracer_set_gain_short()
{
    tracer_set_gain_default();
}

void tim7_tracer_set_gain_long()
{
    float kp, ki, kd;
    kp = TIM7_LONG_KP;
    ki = TIM7_LONG_KI;
    kd = TIM7_LONG_KD;
    tracer_set_gain_direct(kp, ki, kd);
}
