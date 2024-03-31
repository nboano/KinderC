#pragma once
#include "../kinderc.hpp"

/// @brief Returns the current UNIX timestamp. This function is directly imported from the JavaScript enviroment.
/// @return The timestamp in seconds as a double.
imported double time();

/// @brief Returns the current high-precision time since the application started. This function is directly imported from the JavaScript enviroment.
/// @attention The precision of the microtime() function depends on the enviroment.
/// @return The timestamp in milliseconds, as a double.
imported double microtime();

/// @brief Returns the current UTC offset, in hours.
/// @return The current UTC offset, in hours.
int current_utc_offset();

/// @brief Waits for a certain number of milliseconds, and then calls the handler. This function is directly imported from the JavaScript enviroment.
/// @param handler The timeout handler.
/// @param milliseconds The number of milliseconds to wait.
/// @return The timeout identifier.
int setTimeout(void(*handler)(void*), int milliseconds);

/// @brief Calls the handler every N milliseconds. This function is directly imported from the JavaScript enviroment.
/// @param handler The handler.
/// @param milliseconds The number of milliseconds.
/// @return The interval identifier.
int setInterval(void(*handler)(void*), int milliseconds);

/// @brief Deletes a given timeout. This function is directly imported from the JavaScript enviroment.
/// @param timeoutID The timeout identifier.
void clearTimeout(int timeoutID);

/// @brief Deletes a given interval. This function is directly imported from the JavaScript enviroment.
/// @param intervalID The interval identifier.
void clearInterval(int intervalID);

/// @brief Handles dates and times.
/// @warning The class is currently partially completed.
class DateTime {
    private:
        static constexpr int DaysToMonth365[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
        static constexpr int DaysToMonth366[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
        static const long TicksInMillisecond = 10000L;
        static const long TicksInSecond = TicksInMillisecond * 1000L;

        static long long DateToTicks(int year, int month, int day);
        static long long TimeToTicks(int hour, int minute, int second);
    public:

    /// @brief Calculates the Unix Timestamp from a date.
    /// @param year The year.
    /// @param month The month.
    /// @param day The day of the month.
    /// @param hour The hours.
    /// @param minute The minutes.
    /// @param second The seconds.
    /// @param milliseconds The milliseconds.
    /// @return A double representing the UNIX timestamp, in seconds. The decimal part are the milliseconds.
    static double GetTimeStamp(int year, int month, int day, int hour, int minute, int second, int milliseconds);

    /// @brief Parses a DateTime written in the ISO format. Es. 2022-08-28, 2022-08-28T21:45:31, 2022-08-28T21:45:31.123, 2022-08-28T21:45:31+02:00, 2022-08-28T21:45:31.123+02:00
    /// @return The parsed DateTime object.
    static DateTime ParseISO(const char* ISODateTime);

    /// @brief Tells if a certain year is leap or not.
    /// @param year The year.
    /// @return A boolean telling if the year is leap or not.
    static bool IsLeapYear(int year);

    /// @brief Creates a new DateTime object that points to the current time and timezone, both retreived from the system.
    DateTime();

    /// @brief Creates a new DateTime object with a given UNIX timestamp.
    /// @param UnixTimeStamp A UNIX timestamp in seconds.
    DateTime(double UnixTimeStamp);

    int TimeZone = +0;

    double TimeStamp;

    /// @brief The day of the month (1-31).
    unsigned int Day;

    /// @brief The month of the year (1-12).
    unsigned int Month;

    /// @brief The Year.
    unsigned int Year;

    /// @brief The hours.
    unsigned int Hours;

    /// @brief The minutes.
    unsigned int Minutes;

    /// @brief The seconds.
    unsigned int Seconds;

    /// @brief The milliseconds.
    unsigned int Milliseconds;

    
    /// @brief The day of the year (0-366).
    unsigned int DayOfYear;

    /// @brief The Week Day (0-6).
    unsigned int WeekDay;

    /// @brief Formats the current object into a date/time string in the ISO format.
    /// @return A date/time string in the ISO format.
    string ToISOString();

    /// @brief Formats the current object into a date string (dd/MM/yyyy).
    /// @return The date string.
    string ToDateString();

    /// @brief Formats the current object into a time string (hh:mm:ss).
    /// @return The time string.
    string ToTimeString();

    /// @brief Returns a DateTime object with a certain timezone.
    /// @param timeZone The timezone (ex. +2, -1)
    /// @return Another DateTime object with the timezone set.
    DateTime ToTimeZone(int timeZone);

    private:
    void buildfromunixts(double s);
};
