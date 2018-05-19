//
// Created by Мхитарян Нарек on 16.04.2018.
//

#ifndef MY_OWN_ALLOCATOR_STACKALLOCATOR_H
#define MY_OWN_ALLOCATOR_STACKALLOCATOR_H
#pragma once
#include <iostream>
#include <memory>
#include "mvector.h"
#include "max.h"
class TrapStackAllocator
{
public:

    mvector <void *> page ;
    void* cur_point;
    size_t availible_space = 0;
    TrapStackAllocator() {
    }
    TrapStackAllocator(TrapStackAllocator &a)
    {
    }
    ~TrapStackAllocator() {
        for(int i = 0; i < page.size; ++i)
        {
            delete page.array[i];
        }

    }
    void* allocate(size_t v,size_t _Count)
    {
        std::align(v, _Count, cur_point, availible_space);
        if(availible_space >= _Count)
        {
            //std::cout << "JJJJJ";
            cur_point = static_cast<void *>(static_cast<char*>(cur_point) + (int)_Count);
            availible_space-=_Count;
            return static_cast<void *>(static_cast<char *>(cur_point) - _Count);

        }
        void *q = ::operator new((max(_Count, (size_t)10000)));
        availible_space = max(_Count, (size_t)10000) - _Count;
        cur_point = static_cast<void *>(static_cast<char *>(q)+_Count);
        page.push_back(q);
        //std::cout << page.capasity << std::endl;
        return q;

    }

    void deallocate(void * _Ptr, size_t s)
    {

    }

};

template <typename T> class StackAllocator
{
public:
    typedef T                  value_type;
    typedef size_t             size_type;
    typedef ptrdiff_t          difference_type;
    typedef value_type*        pointer;
    typedef const value_type*  const_pointer;
    typedef value_type*        reference;
    typedef const value_type*  const_reference;
    StackAllocator()
    {
        true_alloc = std::make_shared<TrapStackAllocator>();
    }
    StackAllocator(const StackAllocator &b)
    {
        true_alloc = b.true_alloc;
    }
    template <typename U>
    StackAllocator(StackAllocator<U> &b)
    {
        true_alloc = b.true_alloc;
    }
    StackAllocator& operator=(const StackAllocator& other)
    {
        true_alloc = other.true_alloc;
        return *this;
    }
    template< class U > struct rebind {
        typedef StackAllocator<U> other;
    };
    T* allocate( size_t some) {
        return static_cast<T*>(true_alloc->allocate(alignof(T), some*sizeof(T)));
    }
    void deallocate(T* place, size_t _how_many)
    {

    }
    ~StackAllocator() = default;
    std::shared_ptr<TrapStackAllocator> true_alloc;
};

#endif //MY_OWN_ALLOCATOR_STACKALLOCATOR_H
