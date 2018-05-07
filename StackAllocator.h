//
// Created by Мхитарян Нарек on 16.04.2018.
//

#ifndef MY_OWN_ALLOCATOR_STACKALLOCATOR_H
#define MY_OWN_ALLOCATOR_STACKALLOCATOR_H
#pragma once
#include <iostream>
#include "mvector.h"
#include "max.h"
template <typename T> class TrapStackAllocator
{
public:
    typedef T                  value_type;
    typedef size_t             size_type;
    typedef ptrdiff_t          difference_type;
    typedef value_type*        pointer;
    typedef const value_type*  const_pointer;
    typedef value_type*        reference;
    typedef const value_type*  const_reference;
    mvector <value_type *> page ;
    value_type *cur_point;
    size_t availible_space = 0;
    mvector <reference > refs;
    TrapStackAllocator() {
    }
    ~TrapStackAllocator() {
        for(int i = 0; i < page.size; ++i)
        {
            delete page.array[i];
        }

    }
    pointer allocate(size_type _Count)
    {
        if(availible_space >= _Count)
        {
            //std::cout << "JJJJJ";
            cur_point+=_Count;
            availible_space-=_Count;
            return (cur_point - _Count);

        }
        void *q = ::operator new((max(_Count, (size_t)10000) * sizeof (value_type)));
        availible_space = max(_Count, (size_t)10000) - _Count;
        cur_point = (pointer)q+_Count;
        page.push_back((pointer)q);
        //std::cout << page.capasity << std::endl;
        return (pointer)q;

    }

    void deallocate(pointer _Ptr, size_type)
    {

    }

/*private:
    std::vector <std::vector<T *>> page;
    int size = 0;
public:
    using value_type = T;
    T* pointer;
    const T* const_pointer;
    std::size_t size_type;
    StackAllocator() {
        std::vector <T *> q(10000);
        page.push_back(q);
        size++;
    }
    ~StackAllocator() {

    }
    template< class U > struct rebind {
        typedef StackAllocator<U> other;
    };
    T *allocate(std::size_t n)
    {
        /*if(page.array[size - 1].capasity - page.array[size - 1].size >= n)
        {
            page.array[size - 1].size+=n;
            return page.array[size - 1].array[page.array[size - 1].size-n];
        }
        else
        {
            std::vector <T *> q(n);
            //q.size = n;
            page.push_back(q);
            return q[0];
        }
    }
    void deallocate(void *d, size_t n)
    {

    }
    template <typename U>
    void destroy(U* ptr){};
    template<typename U, class... Args>
    void construct(U* ptr, Args&&... args){};*/
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
        true_alloc = std::make_shared<TrapStackAllocator<T>>();
    }
    StackAllocator(const StackAllocator &b)
    {
        true_alloc = b.true_alloc;
    }
    StackAllocator& operator=(const StackAllocator& other)
    {
        true_alloc = other.true_alloc;
    }
    template< class U > struct rebind {
        typedef StackAllocator<U> other;
    };
    pointer allocate(size_type _Count)
    {
        return true_alloc->allocate(_Count);
    }
    void deallocate(T* place, size_t _how_many)
    {

    }
    ~StackAllocator() = default;
private:
    std::shared_ptr<TrapStackAllocator<T>> true_alloc;
};



#endif //MY_OWN_ALLOCATOR_STACKALLOCATOR_H
