#pragma once
#include "../kinderc.hpp"

int setTimeout(void(*handler)(void*), int milliseconds) {
    Handler h = Handler(handler);
    return (int)JavaScript::Eval("setTimeout(%s,%i)", (char*)h.GetWithPointer(nullptr, true), milliseconds);
}
int setInterval(void(*handler)(void*), int milliseconds) {
    Handler h = Handler(handler);
    return (int)JavaScript::Eval("setInterval(%s,%i)", (char*)h.GetWithPointer(nullptr, true), milliseconds);
}
void clearTimeout(int timeoutID) {
    JavaScript::Eval("clearTimeout(%i)", timeoutID);
}
void clearInterval(int intervalID) {
    JavaScript::Eval("clearInterval(%i)", intervalID);
}

DateTime::DateTime(unsigned long s) {
    int z = s / 86400 + 719468;
    int era = (z >= 0 ? z : z - 146096) / 146097;
    unsigned int doe = (z - era * 146097);
    unsigned int yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;
    Year = (yoe) + era * 400;
    unsigned int doy = doe - (365*yoe + yoe/4 - yoe/100);
    unsigned int mp = (5*doy + 2)/153;
    Day = doy - (153*mp+2)/5 + 1;
    Month = mp + (mp < 10 ? 3 : -9);
    Year += (Month <= 2);

    long extraTime = s % (24 * 60 * 60);
    Hours = extraTime / 3600;
    Minutes = (extraTime % 3600) / 60;
    Seconds = (extraTime % 3600) % 60;
}