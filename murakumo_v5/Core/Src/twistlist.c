/**
 * @file twistlist.c
 * @author YAZAWA Kenichi (s21c1036hn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-05-12
 * 
 * Copyright 2023 YAZAWA Kenichi
 * 
 */

#include "twistlist.h"

Twist twistlist[COURSE_STATE_SIZE];

void generate_twistlist()
{
    for(index = 0; index < COURSE_STATE_SIZE; index++)
    {
        //! 単位 [ m / s ]
        float v = 1;
        //! 単位 [ rad / s ]
        float w = 0;
        Twist q;
        q.linear.x = v;
        q.linear.y = 0;
        q.linear.z = 0;
        q.angular.x = 0;
        q.angular.y = 0;
        q.angular.z = w;
        twistlist[index] = q;
    }
}

Twist get_twistlist(uint16_t index)
{
    return twistlist[index];
}

