#pragma once

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
	return JavaScript::Eval(s + "()");
}
char* DynamicObject::operator() (const char* p1, const char* p2, const char* p3) {
	return JavaScript::Eval(s + "(" + p1 + "," + p2 + "," + p3 + ")");
}
char* DynamicObject::operator() (const char* p1, const char* p2) {
	return JavaScript::Eval(s + "(" + p1 + "," + p2 + ")");
}
char* DynamicObject::operator() (const char* p1) {
	return JavaScript::Eval(s + "(" + p1 + ")");
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
	return JavaScript::Eval(s);
}
void DynamicObject::setValue(const char* value) {
	string cmd = s + "=" + String(value);
	JavaScript::Eval(cmd);
}
