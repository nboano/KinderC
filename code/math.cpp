#include "../kinderc.hpp"
#pragma once

int floor(double num)
{
    if(num < 0)
        return (int)num - 1;
    else
        return (int)num;
}
int ceil(double num) {
    return floor(num) + 1;
}
int round(double num) {
    return (num >= 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}