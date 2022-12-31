#pragma once
#include "../kinderc.hpp"

class HTMLInputElement : public HTMLElement {
public:
    HTMLInputElement(HTMLElement el) : HTMLElement(el.query) {}

    prop(type);
    prop(disabled);
    prop(value);
    prop(name);
    prop(pattern);

    ev_HTMLElement(onchange);
    ev_HTMLElement(oninput);
    ev_HTMLElement(oninvalid);
    ev_HTMLElement(onsearch);
    ev_HTMLElement(onselectionchange);
};

typedef HTMLInputElement TextBox;
typedef HTMLInputElement RadioButton;
typedef HTMLInputElement CheckBox;