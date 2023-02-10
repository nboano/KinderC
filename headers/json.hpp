#pragma once
#include "../kinderc.hpp"
#include "list.hpp"

/// @brief Use this class to build and parse JSON strings.
class JSON {
public:

    class Parser;

    /// @brief Parses a JSON string into an object.
    /// @param s A valid JSON string.
    /// @return An object pointer.
    /// @exception JSONNotValid
    static object Parse(string s);

    /// @brief Serializes the current object into a JSON string.
    /// @param pretty Sets this to true if you want the string to be prettified (with tabulations, spaces ecc.). Defaults to true.
    /// @param tabnumber Sets the default number of tabulations. Defaults to 1.
    /// @return A JSON string representing the object.
    string Serialize(bool pretty = true, int tabnumber = 1);

    struct Value;

    struct Field;

    /// @brief A JSON non-typised array. It can contain a variable number of elements of different type.
    /// @example JSON::Array a = {1, "sd", "a", false};
    class Array: public List<Value> {

    };

    class Object: public List<Field> {
        public:
        Field operator[](int i) {
            return arrptr[i];
        }
        Value operator[](const char* key) {
            for (int i = 0; i < Count; i++) {
                if(strcmp(arrptr[i].Key, key) == 0)
                    return arrptr[i].Value;
            }
            return nullptr;    
        };
    };

    /// @brief Represents a JSON value of a specified type.
    struct Value {

        /// @brief Enumerator that lists all the JSON type available.
        enum DataType {

            /// @brief JSON null data type.
            NULL_T,

            /// @brief JSON string data type.
            STRING,

            /// @brief JSON integer data type (Number).
            INT,

            /// @brief JSON floating-point data type (Number).
            DOUBLE,

            /// @brief JSON boolean data type.
            BOOL,

            /// @brief JSON array data type.
            ARRAY,

            /// @brief JSON object data type.
            OBJECT,
        };
        
    private:
        DataType type;

        const char* value_string;
        int value_int;
        double value_double;
        bool value_bool;

        Value* value_array;
        int array_count;

        JSON* value_object;

    public:

        DataType GetType() { return type; };

        const char* GetJSONValue(bool pretty = true, int tabnumber = 1);

        operator int();
        operator const char*();
        operator char*();
        operator string();
        operator double();
        operator Array();
        operator JSON();
        operator Object();

        Value(decltype(__nullptr) nul);
        Value(int n);
        Value(unsigned int n);
        Value(const char* s);
        Value(char* s);
        Value(string s);
        Value(double n);
        Value(bool b);
        Value(Array lst);
        Value(JSON* obj);
        Value(Object flist);
    };

    /// @brief Represents a JSON field (Key/Value pair) of a certain type.
    struct Field {
        Field(const char* key, Value value) : Key(key), Value(value) {}

        const char* Key;
        Value Value;
    };

    /// @brief List of fields of the object.
    Object Fields;

    /// @brief Retrieves a certain field value from the JSON object, if available.
    /// @param key The key.
    /// @return The field. If the key does not exists, nullptr is returned.
    Value operator[](const char* key);

    /// @brief Constructs a new JSON from a field.
    /// @param f A JSON Field.
    JSON(Field f);

    JSON();

    template<typename... Args>

    /// @brief Constructs a new JSON from multiple fields. 
    JSON(Field f, Args... args);
};

#include "JSONParser.hpp"