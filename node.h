//
// Created by Мхитарян Нарек on 26.04.2018.
//

#ifndef MY_OWN_ALLOCATOR_NODE_H
#define MY_OWN_ALLOCATOR_NODE_H
template <typename T>
class Node
{
public:
    T value;
    Node *mask;
    void update_mask(Node* prev = nullptr, Node *next = nullptr)
    {
        mask = (Node *)(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next));
    }
    explicit Node(const T &val, Node *prev = nullptr, Node *next = nullptr)
    {
        value = val;
        update_mask(prev, next);
    }
    explicit Node(T&& _val, Node* prev = nullptr, Node *next = nullptr)
    {
        value = _val;
        update_mask(prev, next);
    }
    void update_mask_front(Node *next = nullptr)
    {
        mask = (Node *)(reinterpret_cast<uintptr_t>(mask) ^ reinterpret_cast<uintptr_t>(next));
    }
    void update_mask_prev(Node *prev = nullptr)
    {

        mask = (Node *)(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(mask));
    }
    ~Node()
    {

    }
};


#endif //MY_OWN_ALLOCATOR_NODE_H
