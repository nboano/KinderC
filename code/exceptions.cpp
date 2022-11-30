#pragma once
#include "../kinderc.hpp"

Exception::Exception(string message) {
	msg = message;
}
string Exception::what() {
	return msg;
}

extern "C" void __cxa_throw(void* ptr, void*, void(*)(void*)) {
	Console::Error(string::Format("KINDERC - Runtime Exception\n\n%s", ((Exception*)ptr)->what().CharArray));
}
extern "C" void* __cxa_allocate_exception(unsigned long thrown_size) {
	return malloc(thrown_size);
}
extern "C" void __cxa_free_exception(void* ptr) {
	free(ptr);
}