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
int current_utc_offset() {
    return (-(int)JavaScript::Eval("new Date().getTimezoneOffset()"))/60;
}

void DateTime::buildfromunixts(double ts, int tz) {
    TimeStamp = ts;
    TimeZone = tz;
    ts += tz * 3600;
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
    WeekDay = (unsigned int)(((floor(ts / 86400) + 4)-1) % 7);

    DayOfYear = (153*(Month + (Month > 2 ? -3 : 9)) + 2)/5 + Day - 1 + 60;
}

string DateTime::ToISOString() {
    return string::Format("%i-%s-%sT%s:%s:%s.%s%c%s:00", 
        Year, 
        (char*)String((int)Month).PadLeft(2, '0'), 
        (char*)String((int)Day).PadLeft(2, '0'), 
        (char*)String((int)Hours).PadLeft(2, '0'), 
        (char*)String((int)Minutes).PadLeft(2, '0'), 
        (char*)String((int)Seconds).PadLeft(2, '0'), 
        (char*)String((int)Milliseconds).PadLeft(3, '0'),
        (char)(TimeZone >= 0 ? '+' : '-'),
        (char*)String((int)(TimeZone >= 0 ? TimeZone : -TimeZone)).PadLeft(2, '0')
    );
}

string DateTime::ToISODateString() {
    return string::Format("%i-%s-%s",
        Year,
        (char*)String((int)Month).PadLeft(2, '0'), 
        (char*)String((int)Day).PadLeft(2, '0')
    );
}

string DateTime::ToDateString() {
    return string::Format("%s/%s/%i",  
        (char*)String((int)Day).PadLeft(2, '0'),
        (char*)String((int)Month).PadLeft(2, '0'), 
        Year
    );
}

string DateTime::ToTimeString() {
    return string::Format("%s:%s:%s", 
        (char*)String((int)Hours).PadLeft(2, '0'), 
        (char*)String((int)Minutes).PadLeft(2, '0'), 
        (char*)String((int)Seconds).PadLeft(2, '0')
    );
}

DateTime DateTime::ToTimeZone(int timeZone) {
    DateTime dt = DateTime(0);
    dt.buildfromunixts(TimeStamp, timeZone);
    return dt;
}

bool DateTime::IsLeapYear(int year) {
    if ((year % 4) != 0)
        return false;
    if ((year % 100) == 0)
        return ((year % 400) == 0);
    return true;
}

long long DateTime::DateToTicks(int year, int month, int day) {
    if (((year >= 1) && (year <= 9999)) && ((month >= 1) && (month <= 12)))
    {
        int* daysToMonth = IsLeapYear(year) ? (int*)DaysToMonth366 : (int*)DaysToMonth365;
        if ((day >= 1) && (day <= (daysToMonth[month] - daysToMonth[month - 1])))
        {
            int previousYear = year - 1;
            int daysInPreviousYears = ((((previousYear * 365) + (previousYear / 4)) - (previousYear / 100)) + (previousYear / 400));

            int totalDays = ((daysInPreviousYears + daysToMonth[month - 1]) + day) - 1;
            return (totalDays * 0xc92a69c000L);
        }
    }
    return 0;
}

long long DateTime::TimeToTicks(int hour, int minute, int second)
{
    long long totalSeconds = ((hour * 3600L) + (minute * 60L)) + second;
    return (totalSeconds * TicksInSecond);
}

double DateTime::GetTimeStamp(int year, int month, int day, int hour, int minute, int second, int milliseconds) {
    long long ticks = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    return ((ticks/10000 - 62135596800000)/1000)+milliseconds*0.001;
}

DateTime DateTime::ParseISO(const char* ISODateTime) {
    int len = strlen(ISODateTime);
    if(len < 10) return DateTime(0);

    // Solo data: 2022-08-28

    int year, month, day, hour = 0, min = 0, sec = 0, msec = 0, tzone = 0;
    char year_bf[5], month_bf[3], day_bf[3];

    memset(year_bf, 0, 5);
    memset(month_bf, 0, 3);
    memset(day_bf, 0, 3);

    memcpy(year_bf, ISODateTime, 4);
    year = atoi(year_bf);
    memcpy(month_bf, ISODateTime + 5, 2);
    month = atoi(month_bf);
    memcpy(day_bf, ISODateTime + 8, 2);
    day = atoi(day_bf);

    // Data e ora: 2022-08-28T21:45:31
    if(len >= 19) {
        char hour_bf[3], min_bf[3], sec_bf[3];

        memset(hour_bf, 0, 3);
        memset(min_bf, 0, 3);
        memset(sec_bf, 0, 3);

        memcpy(hour_bf, ISODateTime + 11, 2);
        hour = atoi(hour_bf);
        memcpy(min_bf, ISODateTime + 14, 2);
        min = atoi(min_bf);
        memcpy(sec_bf, ISODateTime + 17, 2);
        sec = atoi(sec_bf);
    }
    // Data e ora con millisec: 2022-08-28T21:45:31.123 / 2022-08-28T21:45:31.123Z
    if(len == 23 || len == 24) {
        char msec_bf[4];
        memset(msec_bf, 0, 4);
        memcpy(msec_bf, ISODateTime + 20, 3);
        msec = atoi(msec_bf);
    }
    // Data e ora con timezone: 2022-08-28T21:45:31+02:00
    if(len == 25) {
        char tzone_bf[4];
        memset(tzone_bf, 0, 4);
        memcpy(tzone_bf, ISODateTime + 19, 3);
        bool neg = tzone_bf[0] == '-';
        tzone_bf[0] = '0';
        tzone = atoi(tzone_bf);
        if(neg) tzone = -tzone;
    }
    // Data e ora con msec e tzone: 2022-08-28T21:45:31.123+02:00
    if(len == 29) {
        char msec_bf[4];
        memset(msec_bf, 0, 4);
        memcpy(msec_bf, ISODateTime + 20, 3);
        msec = atoi(msec_bf);

        char tzone_bf[4];
        memset(tzone_bf, 0, 4);
        memcpy(tzone_bf, ISODateTime + 23, 3);
        bool neg = tzone_bf[0] == '-';
        tzone_bf[0] = '0';
        tzone = atoi(tzone_bf);
        if(neg) tzone = -tzone;
    }
    return DateTime(GetTimeStamp(year, month, day, hour, min, sec, msec)-(tzone*3600)).ToTimeZone(tzone);
}

DateTime::DateTime(double UnixTimeStamp) {
    buildfromunixts(UnixTimeStamp, 0);
}
DateTime::DateTime() {
    buildfromunixts(time(), current_utc_offset());
}

DateTime DateTime::AddSeconds(int seconds) {
    DateTime dt = DateTime(0);
    dt.buildfromunixts(TimeStamp + seconds, TimeZone);
    return dt;
}

DateTime DateTime::AddMinutes(int minutes) {
    return AddSeconds(60*minutes);
}

DateTime DateTime::AddHours(int hours) {
    return AddMinutes(60*hours);
}

DateTime DateTime::AddDays(int days) {
    return AddHours(24*days);
}