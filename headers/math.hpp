#pragma once
#include "../kinderc.hpp"

// The PI.
#define M_PI 3.14159265358979323846264338327950288

/// @brief Returns the absolute value of a given number.
/// @param number The number.
/// @return The absolute value of the number.
int abs(int number);

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

/// @brief Translates an angle into the fundamental interval of (0;2PI).
/// @param angle The angle in radians.
/// @return The equivalent angle into the interval (0;2PI).
double reduce_angle(double angle);

/// @brief Computes the sine of a given angle using the Taylor series.
/// @param angle The angle in radians.
/// @return The sine of the angle.
double sin(double angle);

/// @brief Computes the cosine of a given angle using the Taylor series.
/// @param angle The angle in radians.
/// @return The cosine of the angle.
double cos(double angle);

/// @brief Computes the tangent of a given angle.
/// @param angle The angle in radians.
/// @return The tangent of the angle.
double tan(double angle);

/// @brief Computes the square root of a given number.
/// @param number The input number.
/// @return The approximated square root.
float sqrt(float number);