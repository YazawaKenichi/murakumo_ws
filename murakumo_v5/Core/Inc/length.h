/**
 * @file length.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-12
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#ifndef __LENGTH_H__
#define __LENGTH_H__

#include "encoder.h"

#define D_LENGTH 0

void length_set_sampling_time_ms(unsigned short int);

void length_init(unsigned short int);
void length_start();
void length_stop();
void length_fin();

void length_reset();

float length_read();
float length_read_left();
float length_read_right();

float velocity_read();
float velocity_read_left();
float velocity_read_right();

void length_update();

void length_d_print();

#endif
