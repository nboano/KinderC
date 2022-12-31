#pragma once
#include "../kinderc.hpp"

/// @brief The program entering point.
/// @return Eventually, a status code.
int main();

/// @brief Original main function caller.
exported int __main() {
    return main();
}