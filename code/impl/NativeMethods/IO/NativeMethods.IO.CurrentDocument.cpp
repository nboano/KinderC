#include "NativeMethods.IO.CurrentDocument.hpp"
#include "../Interpreter/NativeMethods.Interpreter.hpp"
#include "../../StdStringsMethods/StdStringsMethods.hpp"

void Implementations::NativeMethods::IO::CurrentDocument::Write(const char* str) {
    char bf[64] = "";
    Implementations::StdStringsMethods::UnsafeCopy(bf, "document.body.innerHTML+=");
    Implementations::StdStringsMethods::UnsafeConcatenation(bf, Implementations::NativeMethods::Interpreter::GetJavaScriptAliasForString(str, -1));
    Implementations::NativeMethods::Interpreter::EvaluateIgnoringResponse(bf);
}