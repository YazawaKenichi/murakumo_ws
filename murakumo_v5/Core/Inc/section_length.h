/**
 * @file section_length.
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-04
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#ifndef __SECTION_LENGTH_H__
#define __SECTION_LENGTH_H__

#include "length.h"

#define D_SECTION_LENGTH 1

void section_length_set_sampling_time_ms(unsigned short int);

void section_length_init(unsigned short int samplingtime_ms);
void section_length_start();
void section_length_stop();
void section_length_fin();

void section_length_reset();
void section_length_buffer_reset();

float section_length_read();
float section_length_read_left();
float section_length_read_right();

void section_length_set_buffer();

void section_length_update();

void section_length_d_print();

#endif

/*

//! 使用方法

void timer()
{
    //! 区間開始点から現在点までの区間長を計算する
    section_length_update();
}

float calc_radius()
{
    ...
    //! 区間開始点から現在点までの区間長を取得する
    section_length = section_length_read();
    //! 区間開始点を現在点までの世界長に設定し、値の初期化をする
    section_length_set_buffer();
}

*/
