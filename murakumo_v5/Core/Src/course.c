/**
 * 
 * @file course.c
 * 
 * SPDX-FileCopyrightText: 2023 YAZAWA Kenichi <s21c1036hn@gmail.com>
 * SPDX-License-Identifier: MIT-LICENSE
 * 
 */

#include "course.h"

uint16_t course_state_index;

void course_reset_state_index()
{
    course_state_index = 0;
}

void course_increment_state_index()
{
    course_state_index++;
    if(course_state_index >= COURSE_STATE_SIZE - 1)
    {
        course_state_index = COURSE_STATE_SIZE - 1;
    }
}
