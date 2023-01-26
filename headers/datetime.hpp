#pragma once
#include "../kinderc.hpp"

/// @brief Returns the current UNIX timestamp.
/// @return The timestamp in seconds as a double.
imported double time();

/// @brief Returns the current high-precision time since the application started.
/// @return The timestamp in milliseconds, as a double.
imported double microtime();

/// @brief Waits for a certain number of milliseconds, and then calls the handler.
/// @param handler The timeout handler.
/// @param milliseconds The number of milliseconds to wait.
/// @return The timeout identifier.
int setTimeout(void(*handler)(void*), int milliseconds);

/// @brief Calls the handler every N milliseconds.
/// @param handler The handler.
/// @param milliseconds The number of milliseconds.
/// @return The interval identifier.
int setInterval(void(*handler)(void*), int milliseconds);

/// @brief Deletes a given timeout.
/// @param timeoutID The timeout identifier.
void clearTimeout(int timeoutID);

/// @brief Deletes a given interval.
/// @param intervalID The interval identifier.
void clearInterval(int intervalID);

/// @brief Handles dates and times.
class DateTime {
    public:

    /// @brief Creates a new DateTime object.
    /// @param UnixTimeStamp A UNIX timestamp in seconds. Defaults to the current time.
    DateTime(double UnixTimeStamp = time());

    float TimeZone = 0.0;

    double TimeStamp;

    unsigned int Day;
    unsigned int Month;
    unsigned int Year;

    unsigned int Hours;
    unsigned int Minutes;
    unsigned int Seconds;

    unsigned int Milliseconds;

    string ToISOString();

    private:
    void buildfromunixts(double s);
};
