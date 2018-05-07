//
// Created by Мхитарян Нарек on 16.04.2018.
//

#ifndef MY_OWN_ALLOCATOR_MAX_H
#define MY_OWN_ALLOCATOR_MAX_H
#pragma once
template <typename T> T max(const T &a, const T &b)
{
    if(a > b)
        return a;
    else
        return b;
}
#endif //MY_OWN_ALLOCATOR_MAX_H
