#pragma once
#include <stdarg.h>

namespace Implementations::StdStringsMethods
{
    unsigned long GetLength(const char* str);

    char* UnsafeConcatenation(char* destination, const char* source);

    void UnsafeSingleCharacterConcatenation(char* destination, char concatenated);

    char* UnsafeCopy(char* destination, const char* source);

    void Reverse(char* str);

    int Compare(const char* first, const char* second);

    char* Upperize(char* str);

    char* Lowerize(char* str);

    int UnsafeVariadicFormat(char* str, const char* fmt, va_list args);
} // namespace Implementations::StdStringsMethods

#include "StdStringsMethods.cpp"
