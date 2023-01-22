#pragma once
#include "../kinderc.hpp"

template<typename T>
List<T>::List(int size) {
    arrptr = (T*)malloc(size * sizeof(T));
    _size = size; 
}

template <typename T>
T List<T>::operator [](int index) {
    return arrptr[index];
}

template <typename T>
void List<T>::Add(T element) {
    if(_count >= _size) doublesize();

    arrptr[_count++] = element;
}

template<typename T>
void List<T>::doublesize() {
    _size *= 2; 
    T* old_array = arrptr;
    arrptr = (T*)malloc(_size * sizeof(T));
    for (int i = 0; i < _count; i++)
    {
        arrptr[i] = old_array[i];
    }
    free(old_array);
}

template<typename T>
List<T>::~List() {
    free(arrptr);
}