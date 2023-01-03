#pragma once
#include "../kinderc.hpp"

class HTMLButtonElement : public HTMLElement {
public:
    HTMLButtonElement(HTMLElement el) : HTMLElement(el) {}

    void click();

    prop(type);
    prop(disabled);
};

typedef HTMLButtonElement Button;