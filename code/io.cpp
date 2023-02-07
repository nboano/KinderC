#pragma once
#include "../kinderc.hpp"
#include "impl/NativeMethods/Interpreter/NativeMethods.Interpreter.hpp"
#include "impl/NativeMethods/IO/NativeMethods.IO.CurrentDocument.hpp"
#include "impl/ConversionMethods/ConversionMethods.hpp"

int atoi(const char* str)
{
	return Implementations::ConversionMethods::UnsafeBase10AsciiStringToUnsignedInteger(str);
}
float atof(const char *arr)
{
	return Implementations::ConversionMethods::UnsafeBase10AsciiStringToFloatingPoint(arr);
}
char* itoa(int num, char* str, int base)
{
	return Implementations::ConversionMethods::UnsafeIntegerToAsciiStringGivenBase(num, str, base);
}
int htoi(const char* c) {
	return Implementations::ConversionMethods::UnsafeBase16AsciiStringToUnsignedInteger(c);
}
void ftoa_fixed(char* buffer, double value) {
	Implementations::ConversionMethods::UnsafeFloatingPointToAsciiString(value, buffer);
}
void ftoa_sci(char* buffer, double value) {
	Implementations::ConversionMethods::UnsafeFloatingPointToAsciiExponentialString(value, buffer);
}
int sprintf(char* string, const char* fmt, ...) {
	va_list arg;
	int length;
	va_start(arg, fmt);
	length = Implementations::StdStringsMethods::UnsafeVariadicFormat(string, fmt, arg);
	va_end(arg);
	return length;
}

int printf(const char* fmt, ...) {
	static char buffer[8192];
	strcpy(buffer, "");
	va_list arg;
	int length;
	va_start(arg, fmt);
	length = Implementations::StdStringsMethods::UnsafeVariadicFormat(buffer, fmt, arg);
	va_end(arg);
	puts(buffer);
	return length;
}

char* JavaScript::Eval(const char* fmt, ...) {
	static char buffer[512];
	strcpy(buffer, "");
	va_list arg;
	va_start(arg, fmt);
	Implementations::StdStringsMethods::UnsafeVariadicFormat(buffer, fmt, arg);
	if(fmt > (const char*)&__heap_base) free((void*)fmt);
	va_end(arg);
	return Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(buffer);
}
void JavaScript::VoidEval(const char* command) {
	Implementations::NativeMethods::Interpreter::EvaluateIgnoringResponse(command);
}
char* JavaScript::GetStringFromPointer(const char* str, int len) {
	return Implementations::NativeMethods::Interpreter::GetJavaScriptAliasForString(str, len);
}
void JavaScript::LogCommands() {
	JavaScript::Eval("__debug=true");
}

void Console::Write(const char* fmt, ...) {
	static char buffer[8192];
	strcpy(buffer, "");
	va_list arg;

	va_start(arg, fmt);
	Implementations::StdStringsMethods::UnsafeVariadicFormat(buffer, fmt, arg);
	va_end(arg);

	JavaScript::Eval("console.log(%s)", JavaScript::GetStringFromPointer(buffer));
}
void Console::Error(const char* error) {
	JavaScript::Eval("console.error(%s)", JavaScript::GetStringFromPointer(error));
}
void Console::Info(const char* info) {
	JavaScript::Eval("console.info(%s)", JavaScript::GetStringFromPointer(info));
}
void alert(const char* text) {
	JavaScript::Eval("alert(%s)", JavaScript::GetStringFromPointer(text));
}
void puts(const char* text) {
	Implementations::NativeMethods::IO::CurrentDocument::Write(text);
}
bool confirm(const char* text) {
	return strcmp(JavaScript::Eval("confirm(%s)", JavaScript::GetStringFromPointer(text)), "true") == 0;
}
char* prompt(const char* text, const char* defaultResponse) {
	char cmd[64];
	strcpy(cmd, "");
	strcat(cmd, "prompt(");
	strcat(cmd, JavaScript::GetStringFromPointer(text));
	strcat(cmd, ",");
	strcat(cmd, JavaScript::GetStringFromPointer(defaultResponse));
	strcat(cmd, ")");
	return JavaScript::Eval(cmd);
}

