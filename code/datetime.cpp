#pragma once
#include "../kinderc.hpp"

unsigned long long time() {
    return (unsigned long long)JavaScript::Eval("Date.now()/1000");
}
