#include "NativeMethods.Interpreter.hpp"
#include "../../StdStringsMethods/StdStringsMethods.hpp"
#include "../../../string.cpp"

char* Implementations::NativeMethods::Interpreter::EvaluateAndAllocateResponse(const char* Expression) {
    return NativeMethods::Interpreter::DirectCalls::_eval(Expression, Implementations::StdStringsMethods::GetLength(Expression), 1);
}

void Implementations::NativeMethods::Interpreter::EvaluateIgnoringResponse(const char* Expression) {
    NativeMethods::Interpreter::DirectCalls::_eval(Expression, Implementations::StdStringsMethods::GetLength(Expression), 0);
}

char* Implementations::NativeMethods::Interpreter::GetJavaScriptAliasForString(const char* str, int len) {
    if(len < 0) len = Implementations::StdStringsMethods::GetLength(str);
    static char m[64];
	Implementations::StdStringsMethods::UnsafeCopy(m, "");
	sprintf(m, "IO.decode(%i,%i)", (int)str, len);
	return m;
}
