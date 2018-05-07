//
// Created by Мхитарян Нарек on 16.04.2018.
//

#ifndef MY_OWN_ALLOCATOR_MVECTOR_H
#define MY_OWN_ALLOCATOR_MVECTOR_H
#pragma once
template <typename T> class mvector
{

public:
    T *array;
    int size = 0, capasity = 0;
    mvector(int __cap = 2)
    {
        array = new T[__cap];
        size = 0;
        capasity = __cap;
    }
    ~mvector()
    {
        delete[] array;
    }
    void push_back(const T &arg)
    {
        if(size == capasity)
        {
            T *array2 = new T[2*capasity];
            T *array3 = array;
            for(int i = 0; i < capasity; ++i)
            {
                array2[i] = array[i];
            }
            array = array2;
            delete[] array3;
            capasity*=2;
            array[size] = arg;
            size+=1;

        }
        else
        {
            array[size] = arg;
            size+=1;
        }
    }



};
#endif //MY_OWN_ALLOCATOR_MVECTOR_H
