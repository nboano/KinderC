#pragma once
#include "malloc.hpp"
#include "io.hpp"

unsigned long strlen(const char* str);
char* strcat(char* s1, const char* s2);
void strrev(char* str);
int strcmp(const char* X, const char* Y);
char* strcpy(char* destination, const char* source);
void strcat_c(char* str, char c);
char* strupr(char* string);
char* strlwr(char* string);

int atoi(char* str);

class String {
public:
	static String Format(const char* fmt, ...);

	char* CharArray;

	String(const char* s = "");
	~String();

	void Concat(const char* str);
	void Concat(char c);
	void Copy(const char* str);
	int CompareTo(const char* str);

	String ToUpper();
	String ToLower();

	bool operator == (const char* str);
	void operator = (const char* s);
	operator char* ();
	operator int ();
	operator const char* ();
	String operator + (const char* s);
	String operator + (char* s);
	String operator + (String s);
	void operator += (const char* s);
	void operator += (char c);
	char operator[] (int index);
};

typedef String string;
#include "code/string.cpp"