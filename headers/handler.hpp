#pragma once
#include "../kinderc.hpp"

class HTMLElement;
class HTMLElementCollection;
class XMLHttpRequest;
class Response;

/// @brief Use this class to handle events and so on.
class Handler {
public:

    /// @brief Creates an handler given a JS or exported function name.
    /// @param fnname The function name, as a string literal.
    Handler(const char* fnname);

    /// @brief Creates an handler given a generic function pointer.
    /// @param handler The handler.
    Handler(void(*handler)(void*));

    /// @brief Creates an handler for an HTMLElement event.
    /// @param handler The handler.
    Handler(void(*handler)(HTMLElement&));

    /// @brief Creates an handler for an XMLHttpRequest event.
    /// @param handler The handler.
    Handler(void(*handler)(XMLHttpRequest&));

    /// @brief Creates an handler for a fetch event.
    /// @param handler The handler.
    Handler(void(*handler)(Response&));

    /// @brief Gets the JavaScript code that calls the handler, passing a pointer.
    /// @param ptr The pointer to pass as parameter.
    /// @param function Specifies if you want a function [ ()=>...() ] or not [ ...() ]
    /// @return A JavaScript code.
    string GetWithPointer(void* ptr, bool function = false);

    /// @brief The handler function name.
    string HandlerFunctionName;

    /// @brief The index in the array of lambdas.
    int LambdaIndex;
};

typedef Handler EventHandler;