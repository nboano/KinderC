#pragma once
#include "../kinderc.hpp"

/// @brief Rounds a double number to the lowest integer value.
/// @param number The number.
/// @return The rounded number.
int floor(double number);

/// @brief Rounds a double number to the highest integer value.
/// @param number The number.
/// @return The rounded number.
int ceil(double number);

/// @brief Rounds a double number.
/// @param number The number.
/// @return The rounded number.
int round(double number);

/// @brief Initialises the rand() function using a given seed.
/// @param seed The seed, for example floor(time()).
void srand(unsigned int seed);

/// @brief Generates a random number between 0 and RAND_MAX.
/// @return A random number.
unsigned int rand();

/// @brief Generates a random number between min and max.
/// @param min The minimum number.
/// @param max The maximum number (always excluded).
/// @return A random number.
unsigned int rand(int min, int max);