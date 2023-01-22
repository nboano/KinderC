#pragma once
#include "../kinderc.hpp"

class History : public object {
public:
    History() : object("history") {}

    #ifndef __INTELLISENSE__
    int get_length() { return (int)operator[]("length");}
    __declspec(property(get=get_length)) int length;
    #else
    int length;
    #endif

    void back() {operator[]("back")();}
    void forward() {operator[]("forward")();}
private:
    #ifdef __INTELLISENSE__
    int get_length();
    #endif
};

#define history History()