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

void DateTime::buildfromunixts(double ts) {
    TimeStamp = ts;
    int s = floor(ts);
    Milliseconds = (ts - s) * 10e2;
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

    int daysFromStart = era * 146097 + (int)doe - 719468;
    WeekDay = (unsigned int)(daysFromStart >= -4 ? (daysFromStart+4) % 7 : (daysFromStart+5) % 7 + 6) - 1;

    DayOfYear = (153*(Month + (Month > 2 ? -3 : 9)) + 2)/5 + Day - 1 + 60;
}

string DateTime::ToISOString() {
    if(TimeZone == 0)
        return string::Format("%i-%s-%sT%s:%s:%s.%s", 
            Year, 
            (char*)String((int)Month).PadLeft(2, '0'), 
            (char*)String((int)Day).PadLeft(2, '0'), 
            (char*)String((int)Hours).PadLeft(2, '0'), 
            (char*)String((int)Minutes).PadLeft(2, '0'), 
            (char*)String((int)Seconds).PadLeft(2, '0'), 
            (char*)String((int)Milliseconds).PadLeft(3, '0')
        );
    return DateTime(TimeStamp + TimeZone * 3600).ToISOString();
}

string DateTime::ToDateString() {
    if(TimeZone == 0)
        return string::Format("%s/%s/%i",  
            (char*)String((int)Day).PadLeft(2, '0'),
            (char*)String((int)Month).PadLeft(2, '0'), 
            Year
        );
    return DateTime(TimeStamp + TimeZone * 3600).ToDateString();
}

string DateTime::ToTimeString() {
    if(TimeZone == 0)
        return string::Format("%s:%s:%s", 
            (char*)String((int)Hours).PadLeft(2, '0'), 
            (char*)String((int)Minutes).PadLeft(2, '0'), 
            (char*)String((int)Seconds).PadLeft(2, '0')
        );
    return DateTime(TimeStamp + TimeZone * 3600).ToTimeString();
}

DateTime DateTime::ToTimeZone(int timeZone) {
    DateTime dt = DateTime(TimeStamp);
    dt.TimeZone = timeZone;
    return dt;
}

DateTime::DateTime(double UnixTimeStamp) {
    buildfromunixts(UnixTimeStamp);
}