#pragma once
#include "../kinderc.hpp"

/// @brief Use this class to write in the browser console.
class Console {
public:

    /// @brief Writes in the browser console
    /// @param fmt A string. You can use printf-like flags, too.
    /// @param [FORMAT PARAMS] Optional params.
    static void Write(const char* fmt, ...);

    /// @brief Writes a red error message in the console.
    /// @param error An error message.
    static void Error(const char* error);

    /// @brief Writes an information in the console.
    /// @param info A message.
    static void Info(const char* info);
};