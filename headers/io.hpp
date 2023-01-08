#pragma once
#include "../kinderc.hpp"

/// @brief Displays an alert message. The code is blocked until the user clicks OK.
/// @param text The message text.
void alert(const char* text);

/// @brief Asks the user for a confirm (Yes / No, OK / Cancel). The code is blocked until the user closes the confirm box.
/// @param text The message text.
/// @return true if the user answered yes, false otherwise.
bool confirm(const char* text);

/// @brief Asks the user for a text input. The code is blocked until the user closes the input box.
/// @param text The message text.
/// @param defaultResponse A default response.
/// @return The response gave by the user.
char* prompt(const char* text, const char* defaultResponse = "");

/// @brief Prints a string to the webpage.
/// @param text The string to print.
void puts(const char* text);

/// @brief Converts a string into an integer (Base 10). NOTE: If the string is not an integer, an undefined behaviour will occur.
/// @param str The string to convert (Base 10).
/// @return The integer result.
int atoi(const char* str);

/// @brief Converts a string into a floating point number. NOTE: If the string is not an integer, an undefined behaviour will occur.
/// @param str The string to convert (Base 10).
/// @return A floating point number.
float atof(const char* str);

/// @brief Converts a string into an integer (Base 16). NOTE: If the string is not an integer, an undefined behaviour will occur.
/// @param c The string to convert (Base 16).
/// @return The integer result.
int htoi(const char* c);

/// @brief Converts an integer into a string of a given base.
/// @param num The number to convert.
/// @param str The string buffer. Make sure that is long enough.
/// @param base The number base.
/// @return A pointer to the string buffer.
char* itoa(int num, char* str, int base);

/// @brief Writes a formatted string into the webpage.
/// @param fmt The base string. You can use flags like %s, %i, %d, %c...
/// @param [P] Optional formatter params.
/// @return The written string length.
int printf(const char* fmt, ...);

/// @brief Writes a formatted string into another string.
/// @param string The string buffer. Make sure that is long enough.
/// @param fmt The base string. You can use flags like %s, %i, %d, %c...
/// @param [P] Optional formatter params.
/// @return The string length.
int sprintf(char* string, const char* fmt, ...);

/// @brief Custom sprintf with variable list arguments.
/// @param string The string buffer.
/// @param fmt The base string.
/// @param arg Argument list <stdarg.h>.
/// @return The string length.
int _sprintf(char* string, const char* fmt, va_list arg);