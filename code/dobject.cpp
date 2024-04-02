#pragma once
#include "impl/NativeMethods/Interpreter/NativeMethods.Interpreter.hpp"

DynamicObject::DynamicObject() {
	int index = (int)DynamicObject("dp")["push"]("{}") - 1;
	string lol = String::Format("dp[%i]", index);
	s.Copy(lol);
}
DynamicObject::DynamicObject(const char* objname) {
	s = objname;
}
DynamicObject::~DynamicObject() {
	s.~String();
}
DynamicObject DynamicObject::operator[] (const char* key) {
	return DynamicObject(s + "[\"" + key + "\"]");
}
DynamicObject DynamicObject::operator[] (int key) {
	return DynamicObject(String::Format("%s[%i]", s.CharArray, key));
}
void DynamicObject::operator= (const char* value) {
	setValue(value);
}
char* DynamicObject::operator() () {
	return Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(s + "()");
}
char* DynamicObject::operator() (const char* p1, const char* p2, const char* p3) {
	return Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(s + "(" + p1 + "," + p2 + "," + p3 + ")");
}
char* DynamicObject::operator() (const char* p1, const char* p2) {
	return Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(s + "(" + p1 + "," + p2 + ")");
}
char* DynamicObject::operator() (const char* p1) {
	return Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(s + "(" + p1 + ")");
}
DynamicObject::operator char* () {
	return (char*)getValue();
}
DynamicObject::operator string() {
	return String(getValue());
}
DynamicObject::operator int() {
	return (int)getValue();
}
DynamicObject::operator bool() {
	return String(getValue()) == "true";
}
char* DynamicObject::getValue() {
	return Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(s);
}
void DynamicObject::setValue(const char* value) {
	string cmd = s + "=" + String(value);
	Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(cmd);
}
