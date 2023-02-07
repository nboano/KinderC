#include "StdStringsMethods.hpp"
#include "../ConversionMethods/ConversionMethods.hpp"

unsigned long Implementations::StdStringsMethods::GetLength(const char* str) {
    const char* s;
	for (s = str; *s; ++s);
	return(s - str);
}

char* Implementations::StdStringsMethods::UnsafeConcatenation(char* s1, const char* s2) {
    char* start = s1;
	while (*start != '\0')
		start++;
	while (*s2 != '\0')
		*start++ = *s2++;
	*start = '\0';
	return s1;
}

void Implementations::StdStringsMethods::UnsafeSingleCharacterConcatenation(char* str, char c) {
	str += Implementations::StdStringsMethods::GetLength(str);
	*str++ = c;
	*str++ = 0;
}

char* Implementations::StdStringsMethods::UnsafeCopy(char* destination, const char* source) {
	char* ptr = destination;
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return ptr;
}

void Implementations::StdStringsMethods::Reverse(char* str) {
    int i;
	int j;
	unsigned char a;
	unsigned long len = Implementations::StdStringsMethods::GetLength((const char*)str);
	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
	}
}

int Implementations::StdStringsMethods::Compare(const char* X, const char* Y) {
    while (*X)
	{
		if (*X != *Y) {
			break;
		}
		X++;
		Y++;
	}
	return *(const unsigned char*)X - *(const unsigned char*)Y;
}

char* Implementations::StdStringsMethods::Upperize(char* string) {
	for (char* p = string; *p != '\0'; p++)
	{
		if (*p >= 'a' && *p <= 'z')
			*p -= 32;
	}
	return string;
}

char* Implementations::StdStringsMethods::Lowerize(char* string) {
	for (char* p = string; *p != '\0'; p++)
	{
		if (*p >= 'A' && *p <= 'Z')
			*p += 32;
	}
	return string;
}

int Implementations::StdStringsMethods::UnsafeVariadicFormat(char* string, const char* fmt, va_list arg) {
	int int_temp;
	char char_temp;
	char* string_temp;
	double double_temp;

	char ch;
	int length = 0;

	char buffer[512];

	while ((ch = *fmt++)) {
		if ('%' == ch) {
			switch ((ch = *fmt++)) {
			case '%':
				Implementations::StdStringsMethods::UnsafeSingleCharacterConcatenation(string, '%');
				length++;
				break;
			case 'c':
				char_temp = va_arg(arg, int);
				Implementations::StdStringsMethods::UnsafeSingleCharacterConcatenation(string, char_temp);
				length++;
				break;
			case 's':
				string_temp = va_arg(arg, char*);
				Implementations::StdStringsMethods::UnsafeConcatenation(string, string_temp);
				length += Implementations::StdStringsMethods::GetLength(string_temp);
				break;
			case 'd':
			case 'i':
				int_temp = va_arg(arg, int);
				Implementations::ConversionMethods::UnsafeIntegerToAsciiStringGivenBase(int_temp, buffer, 10);
				Implementations::StdStringsMethods::UnsafeConcatenation(string, buffer);
				length += Implementations::StdStringsMethods::GetLength(buffer);
				break;
			case 'x':
				int_temp = va_arg(arg, int);
				Implementations::ConversionMethods::UnsafeIntegerToAsciiStringGivenBase(int_temp, buffer, 16);
				Implementations::StdStringsMethods::UnsafeConcatenation(string, buffer);
				length += Implementations::StdStringsMethods::GetLength(buffer);
				break;
			case 'b':
				int_temp = va_arg(arg, int);
				Implementations::ConversionMethods::UnsafeIntegerToAsciiStringGivenBase(int_temp, buffer, 2);
				Implementations::StdStringsMethods::UnsafeConcatenation(string, buffer);
				length += Implementations::StdStringsMethods::GetLength(buffer);
				break;
			case 'f':
				double_temp = va_arg(arg, double);
				Implementations::ConversionMethods::UnsafeFloatingPointToAsciiString(double_temp, buffer);
				Implementations::StdStringsMethods::UnsafeConcatenation(string, buffer);
				length += Implementations::StdStringsMethods::GetLength(buffer);
				break;
			case 'e':
				double_temp = va_arg(arg, double);
				Implementations::ConversionMethods::UnsafeFloatingPointToAsciiExponentialString(double_temp, buffer);
				Implementations::StdStringsMethods::UnsafeConcatenation(string, buffer);
				length += Implementations::StdStringsMethods::GetLength(buffer);
				break;
			}
		}
		else {
			Implementations::StdStringsMethods::UnsafeSingleCharacterConcatenation(string, ch);
			length++;
		}
	}
	return length;
}