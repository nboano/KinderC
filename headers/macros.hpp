#pragma once
#include "../kinderc.hpp"

// Declares an imported function.
#define imported extern "C"

// Declares a variable with automatic typisation.
#define var auto

#ifndef __INTELLISENSE__

    #define exported __attribute__((visibility("default"))) extern "C"
    #define ev(evname) void set_##evname(EventHandler* e) { setAttribute(#evname, getJSHandler(e)); }; __declspec(property(put = set_##evname)) EventHandler* evname;
    #define ev_HTMLElement(evname) void set_##evname(void(*e)(HTMLElement&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(HTMLElement&);
    #define ev_HTMLElementColl(evname) void set_##evname(void(*e)(HTMLElement&)) {for(int i = 0; i < length; i++) collectionptr[i].evname = e;}; __declspec(property(put = set_##evname)) void(*evname)(HTMLElement&);
    #define ev_XMLHttpRequest(evname) void set_##evname(void(*e)(XMLHttpRequest&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(XMLHttpRequest&);
    #define prop(name) char* get_##name() {return getProperty(#name);}; void set_##name(const char* v) {setProperty(#name, v);}; __declspec(property(get = get_##name, put = set_##name)) char* name;

#else
    // Declares an exported function.
    #define exported extern "C"

    #define ev(evname) EventHandler* evname;

    #define ev_HTMLElement(evname) Property<void(*)(HTMLElement&)> evname;

    #define ev_HTMLElementColl(evname) Property<void(*)(HTMLElement&)> evname;

    #define ev_XMLHttpRequest(evname) Property<void(*)(XMLHttpRequest&)> evname;

    #define prop(name) Property<const char*> name;
#endif