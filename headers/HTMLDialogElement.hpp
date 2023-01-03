#pragma once
#include "../kinderc.hpp"

class HTMLDialogElement : public HTMLElement {
    public:
    HTMLDialogElement(HTMLElement el) : HTMLElement(el) {}

    prop(returnValue);

    void Show();
    void ShowModal();
    void Close();

    ev_HTMLElement(oncancel);
    ev_HTMLElement(onclose);
};

typedef HTMLDialogElement Dialog;