//
// Created by Мхитарян Нарек on 16.04.2018.
//

#ifndef MY_OWN_ALLOCATOR_XORLIST_H
#define MY_OWN_ALLOCATOR_XORLIST_H
#pragma once

#include <iostream>
#include "node.h"
#include "XorListIterator.h"

template <typename T, typename Allocator>
class XorList
{
    typedef size_t size_type;
    template <typename U>
    void push_back_private(U&& _val)
    {
        size_s++;
        Node <T> *place= alloc_1.allocate(1);
        Node <T> *new_tail = new(place) Node <T>(std::forward<U>(_val), tail);
        if(tail == nullptr)
        {
            head = new_tail;
            tail = new_tail;
            return;
        }
        tail->update_mask_front(new_tail);
        tail = new_tail;
    }

public:
    size_type size_s;
    Node <T> *head, *tail;
    XorListIterator<T> begin()
    {
        XorListIterator <T> ans(nullptr, head);
        return ans;
    }
    XorListIterator<T> end()
    {
        XorListIterator <T> ans(tail, nullptr);
        return ans;
    }
    using Using_Allocator = typename Allocator::template rebind<Node<T>>::other;
    Using_Allocator alloc_1;
    size_type size() noexcept
    {
        return size_s;
    }
    explicit XorList(const Allocator & alloc = Allocator()) : alloc_1(XorList<T, Allocator>::Using_Allocator())
    {
        size_s = 0;
        head = nullptr;
        tail = nullptr;
    }
    XorList(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
    {
        alloc_1 = alloc;
        for(int i = 0; i < count; ++i)
        {
            this->push_back(T());
        }

    }
    XorList(const XorList& expr)
    {
        alloc_1 = expr.alloc_1;
        head = expr.head;
        tail = expr.tail;
        size_s = expr.size_s;
    }
    XorList(XorList&& expr)
    {
        head = expr.head;
        tail = expr.tail;
        size_s = expr.size_s;
        alloc_1 = expr.alloc_1;
        expr.size_s = 0;
        expr.head = nullptr;
        expr.tail = nullptr;
    }
    ~XorList()
    {
        while(size_s > 0)
        {
            this->pop_front();
        }
    }
    XorList& operator=(const XorList& expr)
    {
        alloc_1 = expr.alloc_1;
        XorListIterator<T> it = expr.begin();
        while(it != expr.end())
        {
            push_back(*it);
        }
    }
    XorList& operator=(XorList&& param) noexcept
    {
        head = param.head;
        tail = param.tail;
        size_s = param.size_s;
        alloc_1 = param.alloc_1;
        param.size_s = 0;
        param.head = nullptr;
        param.tail = nullptr;
    }
    void push_back(const T& _val)
    {
        push_back_private(_val);

    }
    void push_back(T&& _val)
    {
        push_back_private(std::move(_val));

    }
    void push_front(const T& _val)
    {
        size_s++;
        Node <T> *place= alloc_1.allocate(1);
        Node <T> *new_head = new(place) Node <T>(_val, nullptr, head);
        if(head == nullptr)
        {
            head = new_head;
            tail = new_head;
            return;
        }
        head->update_mask_prev(new_head);
        head = new_head;
        
    }
    void push_front(T&& _val)
    {
        size_s++;
        Node <T> *place= alloc_1.allocate(1);
        Node <T> *new_head = new(place) Node <T>(_val, nullptr, head);
        if(head == nullptr)
        {
            head = new_head;
            tail = new_head;
            return;
        }
        head->update_mask_prev(new_head);
        head = new_head;
        
    }
    void pop_back()
    {
        size_s--;
        if(size_s == 0)
        {
            return;
        }
        if(size_s == 1)
        {
            alloc_1.deallocate(tail, 1);
            head = nullptr;
            tail = nullptr;
            return;
        }
        XorListIterator<T> it = end();
        --it;
        tail = it.previous;
        tail->update_mask_front(it.present);
        alloc_1.deallocate(it.present, 1);


    }
    void pop_front()
    {
        size_s--;
        if(size_s == 0)
        {
            return;
        }
        if(size_s == 1)
        {
            alloc_1.deallocate(head,1);
            head = nullptr;
            tail = nullptr;
            return;
        }
        XorListIterator<T> it = begin();
        it++;
        head = it.present;
        head->update_mask_prev(it.previous);
        alloc_1.deallocate(it.previous, 1);

    }
    void insert_before(XorListIterator<T> it, const T& _val)
    {
        if(it == begin())
        {
            push_front(_val);
            return;
        }
        Node <T> *place = alloc_1.allocate(1);
        Node <T> *new_Node = new(place) Node <T>(_val, it.previous, it.present);
        it.previous->update_mask_front(it.present);
        it.present->update_mask_prev(it.previous);
        it.previous->update_mask_front(new_Node);
        it.present->update_mask_prev(new_Node);
        size_s++;
    }
    void insert_before(XorListIterator<T> it, T&& _val)
    {
        if(it == begin())
        {
            this->push_front(std::move(_val));
            return;
        }
        Node <T> *place = alloc_1.allocate(1);
        Node <T> *new_Node = new(place) Node <T>(std::move(_val), it.previous, it.present);
        it.previous->update_mask_front(it.present);
        it.present->update_mask_prev(it.previous);
        it.previous->update_mask_front(new_Node);
        it.present->update_mask_prev(new_Node);
        size_s++;
    }
    void insert_after(XorListIterator<T> it, const T& _val)
    {
        if(it.present == tail)
        {
            this->push_back(_val);
            return;
        }
        it++;
        this->insert_before(it, _val);
    }
    void insert_after(XorListIterator<T> it, T&& _val)
    {
        if(it.present == tail)
        {
            this->push_back(std::move(_val));
            return;
        }
        it++;
        this->insert_before(it, std::move(_val));
    }
    void erase(XorListIterator<T> it)
    {
        if(it.present == tail)
        {
            this->pop_back();
            return;
        }
        if(it == begin())
        {
            this->pop_front();
            return;
        }
        Node <T> *prevprev = it.previous;
        it++;
        prevprev->update_mask_prev(it.previous);
        prevprev->update_mask_front(it.present);
        it.present->update_mask_prev(it.previous);
        it.present->update_mask_prev(prevprev);
        alloc_1.deallocate(it.previous, 1);
        size_s--;
    }
};

#endif //MY_OWN_ALLOCATOR_XORLIST_H
