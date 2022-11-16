#pragma once
#include "malloc.hpp"
#include "string.hpp"

class Console {
public:
	static void Write(const char* fmt, ...);
	static void Error(const char* error);
	static void Info(const char* info);
private:
	static void cmd(const char* prefix, const char* txt);
};

extern "C" 	char* _eval(const char* code, int len);

void print(const char* text, int len);
void puts(const char* text);

int atoi(char* str);
int htoi(const char* c);
int normalize(double* val);
char* itoa(int num, char* str, int base);
void ftoa_fixed(char* buffer, double value);
void ftoa_sci(char* buffer, double value);

int printf(const char* fmt, ...);
int sprintf(char* string, const char* fmt, ...);
int _sprintf(char* string, const char* fmt, va_list arg);

#include "code/io.cpp"