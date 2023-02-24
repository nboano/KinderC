#pragma once
#include "../kinderc.hpp"

#ifndef __INTELLISENSE__
#define FIELD(T, fname) T get_##fname() {return (*this)[#fname];} void set_##fname(T value) {(*this)[#fname] = value;} __declspec(property(get = get_##fname, put = set_##fname)) T fname;
#else
#define FIELD(T, fname) T fname;
#endif

/// @brief Declares a reflective struct or class.
#define reflective : public JSON::Object



//#define REFL(T) private: JSON::Object Fields; public: T(JSON::Object obj) {Fields = obj;} operator JSON::Object() {return Fields;}