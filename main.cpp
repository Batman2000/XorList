#include <iostream>
#include "XorList.h"
#include <list>
#include <vector>
#include <algorithm>
#include <ctime>
#include "mvector.h"
#include "StackAllocator.h"
#include "node.h"


class try_allock
{
public:
    int a, b;
    template<class A>
    void* operator new(size_t s, A& allocator) {
        return allocator.allocate(s);
    }

};

void test_of_speed()
{
    StackAllocator <int> ohh;
    XorList <int, StackAllocator<int>> d(ohh);
    clock_t start = clock();

    for (int i = 0; i < 1000000; ++i) {
        d.push_front(i);
    }
    clock_t finish = clock();

    std::cout << (double)(finish - start)/CLOCKS_PER_SEC << std::endl;
    XorList <int, std::allocator<int>> q;
    clock_t start1 = clock();

    for (int i = 0; i < 1000000; ++i) {
        q.push_back(i);
    }
    clock_t finish1 = clock();

    std::cout << (double)(finish1 - start1)/CLOCKS_PER_SEC << std::endl;
}

template <typename T>
void out(T &a)
{
    auto it = a.begin();
    while(it != a.end()) {
        std::cout << (*it) << ' ';
        it++;
    }
    std::cout << std::endl;
}



int main() {
    StackAllocator<int> ohoho;
    XorList <int, StackAllocator<int>> a(1, 1);
    XorList <int, StackAllocator<int>> b;
    b = std::move(a);
    out(b);
    a.push_front(6);
    a.push_front(8);
    int w = 9;
    a.push_back(w);
    Node <int> *x;
    for(int i = 0; i < 100; ++i)
    {
        a.push_front(i);
        auto it = a.end();
    }
    XorListIterator <int> it1 = a.begin();
    it1++;
    a.erase(it1);
    XorListIterator <int> it = a.begin();
    while(it != a.end()) {
        std::cout << (*it) << ' ';
        it++;
    }
    std::cout << '\n';
    XorList<int, StackAllocator<int>> k;
    test_of_speed();
    return 0;
}