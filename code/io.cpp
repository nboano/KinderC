#pragma once
#include "../io.hpp"

	/// <summary>
	/// Converts a string into an integer.
	/// </summary>
	/// <param name="str">String</param>
	/// <returns>Integer</returns>
	int atoi(char* str)
	{
		int res = 0;
		for (int i = 0; str[i] != '\0'; ++i)
			res = res * 10 + str[i] - '0';
		return res;
	}
	/// <summary>
	/// Converts an integer of a given base into a string.
	/// </summary>
	/// <param name="num">The int to convert</param>
	/// <param name="str">String</param>
	/// <param name="base">Base (2, 10 ecc.)</param>
	/// <returns>String</returns>
	char* itoa(int num, char* str, int base)
	{
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
		strrev(str);
		return str;
	}
	int htoi(const char* c) {
		int potenza = 1;
		int numero = 0;
		for (int i = strlen(c) - 1; i >= 0; i--)
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

	void ftoa_fixed(char* buffer, double value);
	void ftoa_sci(char* buffer, double value);

	int _sprintf(char* string, const char* fmt, va_list arg) {
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
					strcat_c(string, '%');
					length++;
					break;
				case 'c':
					char_temp = va_arg(arg, int);
					strcat_c(string, char_temp);
					length++;
					break;
				case 's':
					string_temp = va_arg(arg, char*);
					strcat(string, string_temp);
					length += strlen(string_temp);
					break;
				case 'd':
				case 'i':
					int_temp = va_arg(arg, int);
					itoa(int_temp, buffer, 10);
					strcat(string, buffer);
					length += strlen(buffer);
					break;
				case 'x':
					int_temp = va_arg(arg, int);
					itoa(int_temp, buffer, 16);
					strcat(string, buffer);
					length += strlen(buffer);
					break;
				case 'b':
					int_temp = va_arg(arg, int);
					itoa(int_temp, buffer, 2);
					strcat(string, buffer);
					length += strlen(buffer);
					break;
				case 'f':
					double_temp = va_arg(arg, double);
					ftoa_fixed(buffer, double_temp);
					strcat(string, buffer);
					length += strlen(buffer);
					break;
				case 'e':
					double_temp = va_arg(arg, double);
					ftoa_sci(buffer, double_temp);
					strcat(string, buffer);
					length += strlen(buffer);
					break;
				}
			}
			else {
				strcat_c(string, ch);
				length++;
			}
		}
		return length;
	}

	int normalize(double* val) {
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

	void ftoa_fixed(char* buffer, double value) {
		int exponent = 0;
		int places = 0;
		static const int width = 4;
		if (value == 0.0) {
			buffer[0] = '0';
			buffer[1] = '\0';
			return;
		}
		if (value < 0.0) {
			*buffer++ = '-';
			value = -value;
		}
		exponent = normalize(&value);
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
		while (exponent < 0 && places < width) {
			*buffer++ = '0';
			--exponent;
			++places;
		}
		while (places < width) {
			int digit = value * 10.0;
			*buffer++ = digit + '0';
			value = value * 10.0 - digit;
			++places;
		}
		*buffer = '\0';
	}

	void ftoa_sci(char* buffer, double value) {
		int exponent = 0;
		int places = 0;
		static const int width = 4;

		if (value == 0.0) {
			buffer[0] = '0';
			buffer[1] = '\0';
			return;
		}

		if (value < 0.0) {
			*buffer++ = '-';
			value = -value;
		}
		exponent = normalize(&value);
		int digit = value * 10.0;
		*buffer++ = digit + '0';
		value = value * 10.0 - digit;
		--exponent;

		*buffer++ = '.';

		for (int i = 0; i < width; i++) {
			int digit = value * 10.0;
			*buffer++ = digit + '0';
			value = value * 10.0 - digit;
		}

		*buffer++ = 'e';
		itoa(exponent, buffer, 10);
	}
	/// <summary>
	/// Writes a formatted string.
	/// </summary>
	/// <param name="string">String to write</param>
	/// <param name="fmt">Format string</param>
	/// <param name="">Format params</param>
	/// <returns>String length</returns>
	int sprintf(char* string, const char* fmt, ...) {
		va_list arg;
		int length;
		va_start(arg, fmt);
		length = _sprintf(string, fmt, arg);
		va_end(arg);
		return length;
	}
	/// <summary>
	/// Prints a formatted string.
	/// </summary>
	/// <param name="fmt">Format string to print</param>
	/// <param name="">Format params</param>
	/// <returns>Printed string length</returns>
	int printf(const char* fmt, ...) {
		char buffer[8192];
		strcpy(buffer, "");
		va_list arg;
		int length;
		va_start(arg, fmt);
		length = _sprintf(buffer, fmt, arg);
		va_end(arg);
		print(buffer, length);
		return length;
	}


char* JavaScript::Eval(const char* fmt, ...) {
	char buffer[8192];
	strcpy(buffer, "");
	va_list arg;
	va_start(arg, fmt);
	_sprintf(buffer, fmt, arg);
	va_end(arg);
	return _eval(buffer, strlen(buffer));
}
char* JavaScript::GetStringFromPointer(const char* str, int len) {
	static char m[64];
	strcpy(m, "");
	sprintf(m, "IO.decode(%i,%i)", (int)str, (len == -1) ? (int)strlen(str) : len);
	return m;
}

void Console::Write(const char* fmt, ...) {
	char buffer[8192];
	strcpy(buffer, "");
	va_list arg;
	int length;
	va_start(arg, fmt);
	_sprintf(buffer, fmt, arg);
	va_end(arg);
	cmd("log", buffer);
}
void Console::Error(const char* error) {
	cmd("error", error);
}
void Console::Info(const char* info) {
	cmd("info", info);
}
void Console::cmd(const char* prefix, const char* txt) {
	char cmd[64] = "";
	sprintf(cmd, "console.%s(%s)", prefix, JavaScript::GetStringFromPointer(txt));
	JavaScript::Eval(cmd);
}

void print(const char* text, int len) {
	JavaScript::Eval("document.body.innerHTML+=%s", JavaScript::GetStringFromPointer(text));
}
/// <summary>
/// Displays a Message Box.
/// </summary>
/// <param name="text">Message Box Text</param>
void alert(const char* text) {
	char cmd[64] = "";
	sprintf(cmd, "alert(%s)", JavaScript::GetStringFromPointer(text));
	JavaScript::Eval(cmd);
}
/// <summary>
/// Writes a string into the WebPage.
/// </summary>
/// <param name="text">String</param>
/// <returns></returns>
void puts(const char* text) {
	print(text, strlen(text));
}
/// <summary>
/// Displays a Message Box where you can choose betweeen YES/NO.
/// </summary>
/// <param name="text">Message Box Text</param>
/// <returns>YES (1) / NO (0)</returns>
bool confirm(const char* text) {
	char cmd[64] = "";
	sprintf(cmd, "confirm(%s)?1:0", JavaScript::GetStringFromPointer(text));
	return ((int)JavaScript::Eval(cmd) == 1);
}
/// <summary>
/// Displays an Input Box where you can write a string.
/// </summary>
/// <param name="text">Input Box Text</param>
/// <param name="defaultResponse">Default Response Value</param>
/// <returns>Written String</returns>
char* prompt(const char* text, const char* defaultResponse) {
	char cmd[64] = "";
	sprintf(cmd, "prompt(%s, %s)", JavaScript::GetStringFromPointer(text), JavaScript::GetStringFromPointer(defaultResponse));
	return JavaScript::Eval(cmd);
}

