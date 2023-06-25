#pragma once
#include "../kinderc.hpp"

/// @brief Returns the current UNIX timestamp. This function is directly imported from the JavaScript enviroment.
/// @return The timestamp in seconds as a double.
imported double time();

/// @brief Returns the current high-precision time since the application started. This function is directly imported from the JavaScript enviroment.
/// @attention The precision of the microtime() function depends on the enviroment.
/// @return The timestamp in milliseconds, as a double.
imported double microtime();

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
    public:

    /// @brief Creates a new DateTime object.
    /// @param UnixTimeStamp A UNIX timestamp in seconds. Defaults to the current time, retreived using the time() function.
    DateTime(double UnixTimeStamp = time());

    float TimeZone = 0.0;

    double TimeStamp;

    /// @brief The day of the month.
    unsigned int Day;

    /// @brief The month of the year.
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

    /// @brief Formats the current object into a date/time string in the ISO format.
    /// @return A date/time string in the ISO format.
    string ToISOString();

    private:
    void buildfromunixts(double s);
};
