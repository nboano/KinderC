#pragma once

namespace Implementations::NativeMethods::Interpreter::DirectCalls
{
    extern "C" char* _eval(const char* code, int len, int allocate_response);
} // namespace NativeMethods::Interpreter::DirectCalls

namespace Implementations::NativeMethods::Interpreter
{
    char* EvaluateAndAllocateResponse(const char* Expression);

    void EvaluateIgnoringResponse(const char* Expression);

    char* GetJavaScriptAliasForString(const char* str, int len);
} // namespace NativeMethods::Interpreter

#include "NativeMethods.Interpreter.cpp"

