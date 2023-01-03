#pragma once
#include "../kinderc.hpp"

class HTMLMediaElement : public HTMLElement {
public:
    HTMLMediaElement(HTMLElement el) : HTMLElement(el) {}

    prop(src);

    ev(onabort);
    ev(oncanplay);
    ev(oncanplaythrough);
    ev(oncuechange);
    ev(ondurationchange);
    ev(onemptied);
    ev(onended);
    ev(onerror);
    ev(onloadeddata);
    ev(onloadedmetadata);
    ev(onloadstart);
    ev(onpause);
    ev(onplay);
    ev(onplaying);
    ev(onprogress);
    ev(onratechange);
    ev(onseeked);
    ev(onseeking);
    ev(onstalled);
    ev(onsuspend);
    ev(ontimeupdate);
    ev(onvolumechange);
    ev(onwaiting);

    void pause();
    void play();
    void load();
};