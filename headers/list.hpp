#pragma once
#include "../kinderc.hpp"

#define LIST_DEFAULT_SIZE 16

template<typename T>
/// @brief Represents a dynamic collection of elements that grows dynamically, doubling its size everytime it's required.
class List {
public:

    /// @brief Creates a new List with a given size.
    /// @param size The List initial size. Defaults to 16.
    List(int size = LIST_DEFAULT_SIZE);

    /// @brief Destroys the List.
    ~List();

    /// @brief Adds an element to the List. If there's not enough space, doubles the dimension of the list automatically.
    /// @param element The element to add.
    void Add(T element);

    /// @brief Adds multiple elements to the List. If there's not enough space, doubles the dimension of the list automatically.
    /// @param element The elements to add.
    /// @param ...args The elements to add.
    template<typename... Args>
    void Add(T element, Args... args) {
        Add(element);
        Add(args...);
    }

    /// @brief Gets an element from the list.
    /// @param index The element index.
    /// @return The corresponding element, or (T)0 if it does not exists.
    T operator[](int index);

    /// @brief The number of the inserted elements into the list.
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