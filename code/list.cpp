#pragma once
#include "../kinderc.hpp"

template<typename T>
List<T>::List(int size) {
    arrptr = (T*)malloc(size * sizeof(T));
    _size = size; 
}

template <typename T>
T& List<T>::operator [](int index) {
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
    if(Destroyable)
        free(arrptr);
}

template<typename T>
T* List<T>::ToArray() {
    T* ptr = (T*)malloc(_count*sizeof(T));
    for (int i = 0; i < _count; i++)
    {
        ptr[i] = arrptr[i];
    }
    return ptr;
}


template<typename T>
void qsort(T vett[], int left, int right, int(*comparefn)(T, T))
{
    int i = left, j = right;
    T pivot = vett[(left + right) / 2];
    while (i <= j)
    {
        while (comparefn(vett[i], pivot) < 0)
            i++;
        while (comparefn(vett[j], pivot) > 0)
            j--;
        if (i <= j)
        {
            T el = vett[i];
            vett[i] = vett[j];
            vett[j] = el;

            i++;
            j--;
        }
    }
    if (left < j)
        qsort(vett, left, j, comparefn);
    if (i < right)
        qsort(vett, i, right, comparefn);
}

template<typename T>
void List<T>::Sort(int(*CompareFn)(T, T)) {
    qsort<T>(arrptr, 0, _count, CompareFn);
}