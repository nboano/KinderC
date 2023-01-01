#pragma once
#include "../kinderc.hpp"

#define LIST_DEFAULT_SIZE 16

template<typename T>
class List {
public:
    List(int size = LIST_DEFAULT_SIZE);

    void Add(T element);

    T operator[](int index);

    Property<int> Count {
        [](void* lst) {
            return ((List<T>*)lst)->_count;
        }, this
    };
protected:
    T* arrptr;
    int _count = 0;
    int _size;

    void doublesize();
};