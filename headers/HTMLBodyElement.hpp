#pragma once
#include "../kinderc.hpp"

class HTMLBodyElement : public HTMLElement {
public:
    HTMLBodyElement(HTMLDocument doc) : HTMLElement("body", doc) {

    }
    ev(onafterprint);
    ev(onbeforeprint);
    ev(onbeforeunload);
    ev(onerror);
    ev(onhashchange);
    ev(onload);
    ev(onmessage);
    ev(onoffline);
    ev(ononline);
    ev(onpagehide);
    ev(onpageshow);
    ev(onpopstate);
    ev(onresize);
    ev(onstorage);
    ev(onunload);
};