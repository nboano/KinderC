#pragma once
#include "io.hpp"

class DynamicObject {
public:
	DynamicObject();
	DynamicObject(const char* objname, bool forceToString = true);

	DynamicObject operator[] (const char* key);
	DynamicObject operator[] (int key);
	void operator = (const char* value);

	char* operator () ();
	char* operator () (const char* p1, const char* p2, const char* p3);
	char* operator () (const char* p1, const char* p2);
	char* operator () (const char* p1);

	operator char* ();
	operator string();
	operator int();
	operator bool();
private:
	const char* toString = ".toString()";
	string s;
	char* getValue();
	void setValue(const char* value);
};
typedef DynamicObject object;

#include "code/dobject.cpp"