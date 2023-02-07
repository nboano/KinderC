#pragma once

namespace Implementations::ConversionMethods
{
    const int FloatingPointNumbersWidth = 12;

    int NormalizeFloatingPointNumber(double* numberptr);

    int UnsafeBase10AsciiStringToUnsignedInteger(const char* str);

    int UnsafeBase16AsciiStringToUnsignedInteger(const char* str);

    float UnsafeBase10AsciiStringToFloatingPoint(const char* str);

    char* UnsafeFloatingPointToAsciiString(double value, char* buffer);

    char* UnsafeFloatingPointToAsciiExponentialString(double value, char* buffer);

    char* UnsafeIntegerToAsciiStringGivenBase(int number, char* buffer, int base);
} // namespace Implementation::ConversionMethods

#include "ConversionMethods.cpp"
