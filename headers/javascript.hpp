#pragma once
#include "../kinderc.hpp"

/// @brief Call to the JavaScript interpreter.
imported char* _eval(const char* code, int len, int allocate_response);

/// @brief This class is used to run JavaScript commands.
class JavaScript {
public:

    /// @brief Makes the JavaScript interpreter evaluate the code given and returns the result.
    /// @param fmt The code to evaluate, optionally formatted using the sprintf flags.
    /// @param flags [OPTIONAL FORMAT FLAGS]
    /// @return The expression result. If you expect a result type that is not a string, use an explicit cast.
    /// @example int n = (int)JavaScript::Eval("5 + 10");
    /// @example char* s = JavaScript::Eval("location.href");
    static char* Eval(const char* fmt, ...);

    /// @brief Makes the JavaScript interpreter evaluate the code given WITHOUT returning the result.
    /// @param command The code to evaluate.
    static void VoidEval(const char* command);

    /// @brief Given a string pointer, returns a JS String reference.
    /// @param str String to reference.
    /// @param len String length. If nothing is specified, the system will automatically calculate it.
    /// @return A string that references the original given string.
    static char* GetStringFromPointer(const char* str, int len = -1);

    /// @brief Enable the logging of the JavaScript evaluated commands.
    static void LogCommands();
};