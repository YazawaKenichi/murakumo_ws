#include "tim7.h"

uint16_t cnt;
unsigned long long int count;

void tim7_init()
{
    /* init */
    #if D_TIM7
    printf("tim7.c > tim7_init() > ");
    #endif
    HTL_TIM_Base_Stop_IT(&htim7);
}

void tim7_start()
{
    /* start */
    #if D_TIM7
    printf("tim7.c > tim7_start() > ");
    #endif
    cnt = 0;
    count = 0;
    HAL_TIM_Base_Start_IT(&htim7);
}

void tim7_stop()
{
    /* stop */
    #if D_TIM7
    printf("tim7.c > tim7_stop() > ");
    #endif
    HAL_TIM_Base_Start_IT(&htim7);
}

void tim7_main()
{
    /* main */
    cnt++;
    if(cnt >= 1000)
    {
        count += cnt;
        cnt = 0;
    }
}

void tim7_d_print()
{
    /* d_print */
    #if D_TIM7
    printf("tim7.c > tim7_d_print() > count = %5ld\r\n", count);
    #endif
}
