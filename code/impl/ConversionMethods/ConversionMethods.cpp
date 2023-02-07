#include "ConversionMethods.hpp"
#include "../StdStringsMethods/StdStringsMethods.hpp"

int Implementations::ConversionMethods::NormalizeFloatingPointNumber(double* val) {
    int exponent = 0;
	double value = *val;

	while (value >= 1.0) {
		value /= 10.0;
		++exponent;
	}

	while (value < 0.1) {
		value *= 10.0;
		--exponent;
	}
	*val = value;
	return exponent;
}

int Implementations::ConversionMethods::UnsafeBase10AsciiStringToUnsignedInteger(const char* str) {
    int res = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		res = res * 10 + str[i] - '0';
	return res;
}

int Implementations::ConversionMethods::UnsafeBase16AsciiStringToUnsignedInteger(const char* c) {
    int potenza = 1;
	int numero = 0;
	for (int i = Implementations::StdStringsMethods::GetLength(c) - 1; i >= 0; i--)
	{
		int n;
		if (c[i] >= '0' && c[i] <= '9') n = c[i] - 48;
		else if (c[i] >= 'A' && c[i] <= 'F') n = c[i] - 55;
		else n = c[i] - 87;
		numero += n * potenza;
		potenza *= 16;
	}
	return numero;
}

float Implementations::ConversionMethods::UnsafeBase10AsciiStringToFloatingPoint(const char* arr) {
    float val = 0;
	int afterdot=0;
	float scale=1;
	int neg = 0; 

	if (*arr == '-') {
		arr++;
		neg = 1;
	}
	while (*arr) {
		if (afterdot) {
		scale = scale/10;
		val = val + (*arr-'0')*scale;
		} else {
		if (*arr == '.') 
		afterdot++;
		else
		val = val * 10.0 + (*arr - '0');
		}
		arr++;
	}
	if(neg) return -val;
	else    return  val;
}

char* Implementations::ConversionMethods::UnsafeFloatingPointToAsciiString(double value, char* buffer) {
    int exponent = 0;
	int places = 0;

	if (value == 0.0) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return buffer;
	}
	if (value < 0.0) {
		*buffer++ = '-';
		value = -value;
	}
	exponent = Implementations::ConversionMethods::NormalizeFloatingPointNumber(&value);
	while (exponent > 0) {
		int digit = value * 10;
		*buffer++ = digit + '0';
		value = value * 10 - digit;
		++places;
		--exponent;
	}
	if (places == 0)
		*buffer++ = '0';
	*buffer++ = '.';
	while (exponent < 0 && places < Implementations::ConversionMethods::FloatingPointNumbersWidth) {
		*buffer++ = '0';
		--exponent;
		++places;
	}
	while (places < Implementations::ConversionMethods::FloatingPointNumbersWidth) {
		int digit = value * 10.0;
		*buffer++ = digit + '0';
		value = value * 10.0 - digit;
		++places;
	}
	*buffer = '\0';
    return buffer;
}

char* Implementations::ConversionMethods::UnsafeFloatingPointToAsciiExponentialString(double value, char* buffer) {
    int exponent = 0;
	int places = 0;

	if (value == 0.0) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return buffer;
	}

	if (value < 0.0) {
		*buffer++ = '-';
		value = -value;
	}
	exponent = Implementations::ConversionMethods::NormalizeFloatingPointNumber(&value);
	int digit = value * 10.0;
	*buffer++ = digit + '0';
	value = value * 10.0 - digit;
	--exponent;

	*buffer++ = '.';

	for (int i = 0; i < Implementations::ConversionMethods::FloatingPointNumbersWidth; i++) {
		int digit = value * 10.0;
		*buffer++ = digit + '0';
		value = value * 10.0 - digit;
	}

	*buffer++ = 'e';

	Implementations::ConversionMethods::UnsafeIntegerToAsciiStringGivenBase(exponent, buffer, 10);

    return buffer;
}

char* Implementations::ConversionMethods::UnsafeIntegerToAsciiStringGivenBase(int num, char* str, int base) {
    int i = 0;
	int isNegative = 0;
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}
	if (num < 0 && base == 10)
	{
		isNegative = 1;
		num = -num;
	}
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}
	if (isNegative == 1)
		str[i++] = '-';
	str[i] = '\0';
	Implementations::StdStringsMethods::Reverse(str);
	return str;
}

