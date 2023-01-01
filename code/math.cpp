#include "../kinderc.hpp"
#pragma once

int abs(int x) {
    return x < 0 ? -x : x;
}
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

double reduce_angle(double x) {
    while(x >= M_PI * 2) x -= M_PI * 2; 
    return x;
}
double sin(double x) {
    x = reduce_angle(x);
    double res = 0, pow = x, fact = 1;
    for (int i = 0; i < 7; i++) {
        res += pow / fact;
        pow *= -1 * x * x;
        fact *= (2*(i+1))*(2*(i+1)+1);
    }
    return res;
}
double cos(double x) {
    x = reduce_angle(x);
    return sin(x + M_PI / 2);
}
double tan(double x) {
    x = reduce_angle(x);
    return sin(x) / cos(x);
}