#pragma once
#include "../kinderc.hpp"

class Exception {
	public:

	/// @brief Creates a new Exception object.
	/// @param message The exception message.
	Exception(string message);

	/// @brief Returns the exception message.
	/// @return The exception message.
	string what();

	protected:
	string msg;
};

extern "C" void __cxa_throw(void* ptr, void*, void(*)(void*));

extern "C" void* __cxa_allocate_exception(unsigned long thrown_size);

extern "C" void __cxa_free_exception(void* ptr);