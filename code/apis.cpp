#pragma once
#include "../kinderc.hpp"

Property<bool> Geolocation::IsSupported = Property<bool>(
    []() {
        return (int)JavaScript::Eval("!!navigator.geolocation?1:0") == 1;
    }
);