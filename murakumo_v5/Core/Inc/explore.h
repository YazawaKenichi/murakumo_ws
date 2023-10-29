/**
 * @file explore.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-10-27
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#ifndef __EXPLORE_H__
#define __EXPLORE_H__

#include "analog.h"
#include "encoder.h"
#include "tracer.h"
#include "velotrace.h"
#include "motor.h"

void explore_init();
void explore_start();
void explore_main();
void explore_stop();
void explore_fin();

/**
 * @brief アナログ値 左 - 右 した値を取得
 * 
 * @return int 
 */
int explore_read_direction();

/**
 * @brief ショートセンサのライントレースゲイン値を設定
 * 
 */
void explore_tracer_set_gain_short();
/**
 * @brief ロングセンサのライントレースゲイン値を設定
 * 
 */
void explore_tracer_set_gain_long();

#endif
