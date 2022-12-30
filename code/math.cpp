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

static unsigned long int random_next = 1;
unsigned int rand() {
    random_next = random_next * 1103515245 + 12345;
    return (unsigned int)(random_next / 65536) % 32768;
}
unsigned int rand(int min, int max) {
    return rand() % (max - min) + min;
}
void srand(unsigned int seed) {
    random_next = seed;
}