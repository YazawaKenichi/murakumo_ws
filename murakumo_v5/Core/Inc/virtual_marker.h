/**
 * @file virtual_marker.h
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-02-18
 * 
 * (C) 2023 YAZAWA Kenichi
 * 
 */

#ifndef __VIRTUAL_MARKER_H__
#define __VIRTUAL_MARKER_H__

#include "sidesensor.h"
#include "course.h"

#define THRESHOLD_YAW_CURVE_OR_STRAIGHT 1.5f

void virtual_marker_init();
void virtual_marker_start();
void virtual_marker_main();
void virtual_marker_stop();
void virtual_marker_set();
SideSensorState virtual_marker_read_markerstate();
SideSensorState virtual_marker_read_markerstate_volatile();
void virtual_marker_d_print();

#endif
