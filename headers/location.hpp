#pragma once
#include "../kinderc.hpp"

class Location : public object {
public:
    Location() : object("location") {}

    prop(hash);
    prop(host);
    prop(hostname);
    prop(href);
    prop(origin);
    prop(pathname);
    prop(port);
    prop(protocol);
    prop(search);

    void reload() {operator[]("reload")();}
};

#define location Location()