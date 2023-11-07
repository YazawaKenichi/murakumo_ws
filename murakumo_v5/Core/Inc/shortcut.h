/**
 * @file shortcut.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-07
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#ifndef __SHORTCUT_H__
#define __SHORTCUT_H__

#include "geometry.h"
#include "locomotion.h"

//! ( データ収集時間間隔 [ s / 個 ] ) = ( コース全長 ) / ( コースデータ数 ) / ( 走行速度 )
//! ( 平滑する長さ [ m ] ) = 2 * ADJACENT * ( コース全長 ) / ( コースデータ数 )
#define ADJACENT 150

#endif
