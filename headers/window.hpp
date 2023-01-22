#pragma once
#include "../kinderc.hpp"

class Window : public object {
public:
    Window() : object("window") {}
    
    /*
    HTMLDocument document;
    Location location;
    History history;
    Navigator navigator;
    */
};

#define window Window()