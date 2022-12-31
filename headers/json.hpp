#pragma once
#include "../kinderc.hpp"

/// @brief This struct contains the key/value pairs of a future JSON.
typedef struct t_JSONBuilder {
    string matrix[32][2];
} JSONBuilder;

/// @brief Use this class to handle JSON strings.
class JSON {
public:

    /// @brief Parses a JSON string into an object.
    /// @param s A valid JSON string.
    /// @return An object pointer.
    /// @exception JSONNotValid
    static object Parse(string s);

    /// @brief Builds a JSON string.
    /// @param bldr The builder, containing all the fields.
    /// @param pretty Specifies if the JSON string must be prettified.
    /// @return A JSON string.
    static string Build(JSONBuilder bldr, bool pretty = false);
};