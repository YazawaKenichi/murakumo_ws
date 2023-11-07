/**
 * @file explore.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-10-30
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "explore.h"

Sampling temporary;

void explore_init();
{
    flash_init();
    linetrace_init();
}

void explore_start()
{
    temporary.t = 0.001;
    temporary.v = 0;
    temporary.w = 0;
    linetrace_start();
}

void explore_main()
{
    //! 進んだ距離を積算
    temporary.v += encoder_read() * temporary.t;
    //! 曲がった角度を積算
    temporary.w += imu_read_yaw() * temporary.t;
    //! サンプリング距離を超過した時
    if(temporary.v >= SAMPLING_THRESHOLD)
    {
        float v = temporary.v;
        float w = temporary.w;
    }
    linetrace_main();
}

void explore_stop()
{
    linetrace_stop();
}

void explore_fin()
{
    linetrace_fin();
}
