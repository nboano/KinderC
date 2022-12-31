#pragma once
#include "../kinderc.hpp"

/// @brief This class handles JavaScript objects.
class DynamicObject {
public:

    /// @brief Creates a new, empty object.
    DynamicObject();

    /// @brief Points to an existing object.
    /// @param objname The object name.
    DynamicObject(const char* objname);

    /// Deletes the pointer to the object.
    ~DynamicObject();

    /// @brief Accesses a field of the object.
    /// @param key The field name.
    /// @return Another object pointing to the field.
    DynamicObject operator[] (const char* key);

    /// @brief Accesses an array element.
    /// @param key The element index.
    /// @return Another object pointing to the array element.
    DynamicObject operator[] (int key);

    /// @brief Sets the object value to a string literal.
    /// @param value A string literal, a char array, or a string.
    void operator = (const char* value);

    /// @brief Calls the object as a function.
    /// @return The response. If it's not a string, use an explicit cast.
    char* operator () ();

    /// @brief Calls the object as a function.
    /// @return The response. If it's not a string, use an explicit cast.
    char* operator () (const char* p1, const char* p2, const char* p3);

    /// @brief Calls the object as a function.
    /// @return The response. If it's not a string, use an explicit cast.
    char* operator () (const char* p1, const char* p2);

    /// @brief Calls the object as a function.
    /// @return The response. If it's not a string, use an explicit cast.
    char* operator () (const char* p1);

    /// @brief Converts the object to a char array.
    operator char* ();

    /// @brief Converts the object to a string.
    operator string();

    /// @brief Convert the object to an integer.
    operator int();

    /// @brief Converts the object to a boolean.
    operator bool();
protected:
    const char* toString = ".toString()";
    string s;
    char* getValue();
    void setValue(const char* value);
    void setProperty(string name, string value) { operator[]((char*)name) = string::Format("`%s`", (char*)value);}
    string getProperty(string name) {return operator[]((char*)name);}
};

// Represents a JavaScript object.
#define object DynamicObject