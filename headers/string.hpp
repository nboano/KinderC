#pragma once
#include "../kinderc.hpp"

/// @brief Calculates the length of a given string.
/// @param str The string.
/// @return The number of characters of the string.
unsigned long strlen(const char* str);

/// @brief Appends the content of s2 into s1. Make sure that s1 is long enough.
/// @param s1 The destination string.
/// @param s2 The string to concatenate.
/// @return A pointer to the destination string.
char* strcat(char* s1, const char* s2);

/// @brief Reverses a given string.
/// @param str The string.
void strrev(char* str);

/// @brief Compares two strings.
/// @param X The first string.
/// @param Y The second string.
/// @return A negative integer if X < Y.
/// @return Zero if the two strings are equal.
/// @return A positive integer if X > Y.
int strcmp(const char* X, const char* Y);

/// @brief Copies a source string into a destination. Make sure that the souce is long enough.
/// @param destination The destination string.
/// @param source The source string.
/// @return A pointer to the destination string.
char* strcpy(char* destination, const char* source);

/// @brief Concatenates a single character to a string.
/// @param str The string.
/// @param c The character to concatenate.
void strcat_c(char* str, char c);

/// @brief Upperizes a string.
/// @param string The string.
/// @return A pointer to the string.
char* strupr(char* string);

/// @brief Lowerizes a string.
/// @param string The string.
/// @return A pointer to the string.
char* strlwr(char* string);

/// @brief 
/// @param string 
/// @param separator 
/// @return 
char* strtok(char* string, char separator);

/// @brief Use this class to manage strings.
class String {
public:

    /// @brief Creates a formatted string.
    /// @param fmt The base string. Use %s to indicate a string, %i for an integer, %d for a double, %c for a char...
    /// @param [FLAGS] Optional printf-like parameters.
    /// @return A formatted string.
    static String Format(const char* fmt, ...);

    /// @brief A pointer to the raw string characters. Use it only if you know how.
    char* CharArray;

    /// @brief Creates a string object from a char array, or string literal.
    /// @param s A char array, or a string literal.
    String(const char* s = "");

    /// @brief Creates a string object from an integer.
    /// @param n An integer that will be converted to a string.
    String(int n);

    /// @brief Destroys a string, deallocating the memory associated.
    ~String();

    /// @brief Concatenates a string literal to the string. The string is automatically resized if needed.
    /// @param str A string literal, a char array or a string.
    void Concat(const char* str);

    /// @brief Concatenates a character to the string.
    /// @param c A char.
    void Concat(char c);

    /// @brief Copies the content of a string literal into a string. The string is automatically resized if needed.
    /// @param str A string literal, a char array or a string.
    void Copy(const char* str);

    /// @brief Compares the string to another string literal.
    /// @param str A string literal, a char array or a string.
    /// @return A negative integer if the string is minor.
    /// @return Zero if the two strings are equal.
    /// @return A positive integer if the string is major.
    int CompareTo(const char* str);

    /// @brief Gets the string length. Use the property instead.
    /// @return The string length.
    unsigned long GetLength();

    /// @brief Creates a new upperized string.
    /// @return Upperized string.
    String ToUpper();

    /// @brief Creates a new lowerized string.
    /// @return Lowerized string.
    String ToLower();

    /// @brief Adds a character to the left of the string until reacher the specified length.
    /// @param length The desired length.
    /// @param ch The character to add. Defaults to a whitespace.
    /// @return A new, padded string.
    String PadLeft(int length, char ch = ' ');

    /// @brief Adds a character to the left of the string until reacher the specified length.
    /// @param length The desired length.
    /// @param ch The character to add. Defaults to a whitespace.
    /// @return A new, padded string.
    String PadRight(int length, char ch = ' ');

    /// @brief Check if a string starts with another string.
    /// @param s The other string.
    /// @return A boolean value (true / false)
    bool StartsWith(String s);

    /// @brief Check if a string ends with another string.
    /// @param s The other string.
    /// @return A boolean value (true / false)
    bool EndsWith(String s);

    /// @brief Splits a string.
    /// @param s The splitting character.
    /// @return An array of strings.
    String* Split(char separator);

    /// @brief Check if two string are equal.
    /// @param str A string literal, a char array or a string.
    /// @return true if the strings are equal,
    /// @return false otherwise.
    bool operator==(const char* str);

    bool operator!=(const char* str);

    /// @brief Copies another string into this one.
    /// @param s A string literal, a char array or a string.
    void operator = (const char* s);
    void operator = (String s);

    /// @brief Converts a string into a char array.
    operator char* ();

    /// @brief Converts a string into an integet.
    operator int();

    /// @brief Converts a string into a literal.
    operator const char* ();

    /// @brief Concatenates two strings.
    /// @param s A string literal.
    /// @return A new string.
    String operator + (const char* s);

    /// @brief Concatenates two strings.
    /// @param s A char array.
    /// @return A new string.
    String operator + (char* s);

    /// @brief Concatenates two strings.
    /// @param s A string.
    /// @return A new string. 
    String operator + (String s);

    /// @brief Appends a string literal, a char array or another string at the end of this string.
    /// @param s A string literal, a char array or a string.
    void operator += (const char* s);

    /// @brief Appends a character to the string.
    /// @param c A char.
    void operator += (char c);

    void operator += (String s);

    /// @brief Returns the character of a given index.
    /// @param index The index.
    /// @return The corresponding character.
    char operator[] (int index);

    /// @brief Gets the Length of the string.
    __declspec(property(get = GetLength)) unsigned long Length;
};

// Represents a string allocated in the heap memory.
#define string String