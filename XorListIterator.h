//
// Created by Мхитарян Нарек on 29.04.2018.
//

#ifndef MY_OWN_ALLOCATOR_XORLISTITERATOR_H
#define MY_OWN_ALLOCATOR_XORLISTITERATOR_H

#include <form.h>
#include "node.h"
#include "XorList.h"
template <typename T>
class XorListIterator
{
public:
    XorListIterator& operator++()
    {
        Node<T> *tmp = present;
        present = (Node<T> *)((uintptr_t)(present->mask) ^ (uintptr_t)(previous));
        previous = tmp;
        return *this;
    }
    XorListIterator operator++(int)
    {
        XorListIterator it1 = *this;
        ++(*this);
        return it1;
    }
    XorListIterator& operator--()
    {
        Node<T> *tmp = previous;
        previous = (Node<T> *)((uintptr_t)(present) ^ (uintptr_t)(previous->mask));
        present = tmp;
        return *this;
    }
    XorListIterator operator--(int)
    {
        XorListIterator it1 = *this;
        --(*this);
        return it1;
    }
    bool operator==(const XorListIterator& a)
    {
        if(present == a.present && previous == a.previous)
        {
            return true;
        }
        return false;
    }
    bool operator!=(const XorListIterator& b)
    {
        return !(*this == b);
    }
    XorListIterator(Node<T>* _pr, Node<T>* _pt)
    {
        present = _pt;
        previous = _pr;
    }
    XorListIterator(const XorListIterator& another)
    {
        present = another.present;
        previous = another.previous;
    }
    XorListIterator operator=(const XorListIterator& other)
    {
        present = other.present;
        previous = other.previous;
    }
    T& operator*()
    {
        return present->value;
    }
    Node <T>* get_present()
    {
        return present;
    }
    Node <T>* get_previous()
    {
        return previous;
    }
    Node<T> *present, *previous;
    template <typename W, typename Alloc>
    friend class Xorlist;

};

#endif //MY_OWN_ALLOCATOR_XORLISTITERATOR_H
