#pragma once
#include "../kinderc.hpp"

template <class T>
class Property {
    public:
    Property(T(*get)(), void(*set)(T)) {
        getter = get;
        setter = set;
    }
    Property(T(*get)(), void* sender = nullptr) {
        getter = get;
        
        ptr = sender;
    }
    Property(void(*set)(T), void* sender = nullptr) {
        setter = set;

        ptr = sender;
    }

    Property(T(*get)(void*), void(*set)(void*,T), void* sender) {
        dgetter = get;
        dsetter = set;

        ptr = sender;
    }
    Property(T(*get)(void*), void* sender) {
        dgetter = get;

        ptr = sender;
    }
    Property(void(*set)(void*,T), void* sender) {
        dsetter = set;

        ptr = sender;
    }

    void operator = (T value) {
        if(ptr) dsetter(ptr, value);
        else setter(value);
    }
    operator T() {
        if(ptr) return dgetter(ptr);
        else return getter();
    }
    private:
    void(*setter)(T) = [](T){};
    T(*getter)() = [](){T r; return r;};

    void(*dsetter)(void*, T) = [](void*, T){};
    T(*dgetter)(void*) = [](void*){T r; return r;};

    void* ptr = nullptr;
};