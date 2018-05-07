cmake_minimum_required(VERSION 3.8)
project(my_own_allocator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp mvector.h max.h StackAllocator.h XorList.h node.h XorListIterator.h)
add_executable(my_own_allocator ${SOURCE_FILES})