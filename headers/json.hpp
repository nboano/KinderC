#pragma once
#include "../kinderc.hpp"
#include "../headers/list.hpp"

/// @brief Use this class to build and parse JSON strings.
class JSON {
public:

    /// @brief Parses a JSON string into an object.
    /// @param s A valid JSON string.
    /// @return An object pointer.
    /// @exception JSONNotValid
    static object Parse(string s);

    struct Value;
    typedef List<Value> Array;

    struct Value {
    private:
        enum DataType {
            NULL_T,

            STRING,
            INT,
            DOUBLE,
            BOOL,

            ARRAY,

            OBJECT,
        } type;

        const char* value_string;
        int value_int;
        double value_double;
        bool value_bool;

        Value* value_array;
        int array_count;

        JSON* value_object;

    public:

        const char* GetJSONValue(bool pretty = true, int tabnumber = 1) {
            switch (type)
            {
                case STRING:
                    return String::Format("\"%s\"", value_string);
                case INT:
                    return String::Format("%i", value_int);
                case DOUBLE:
                    return String::Format("%f", value_double);
                case BOOL:
                    return value_bool ? "true" : "false";
                case ARRAY:
                {
                    String s = "[";
                    for (int i = 0; i < array_count; i++)
                    {
                        s += value_array[i].GetJSONValue(value_array[i].type == OBJECT ? false : pretty, tabnumber + 1);
                        if(i != array_count - 1) s += pretty? ", " : ",";
                    }
                    s += "]";
                    return s;
                }
                case OBJECT:
                    return value_object->Serialize(pretty, tabnumber + 1);
                default:
                    return "null";
            }
        }

        operator int() {
            return value_int;
        }
        operator const char*() {
            return value_string;
        }
        operator char*() {
            return (char*)value_string;
        }
        operator string() {
            return (string)value_string;
        }
        operator double() {
            return value_double;
        }
        operator Array() {
            Array a { array_count };
            for (int i = 0; i < array_count; i++)
            {
                a[i] = value_array[i];
            }
            return a;
        }
        operator JSON() {
            return *value_object;
        }

        Value(decltype(__nullptr) nul) {type = NULL_T;}
        Value(int n) {value_int = n; type = INT;}
        Value(unsigned int n) {value_int = n; type = INT;}
        Value(const char* s) {value_string = s; type = STRING;}
        Value(char* s) {value_string = s; type = STRING;}
        Value(string s) {value_string = s; type = STRING;}
        Value(double n) {value_double = n; type = DOUBLE;}
        Value(bool b) {value_bool = b; type = BOOL;}
        Value(Array lst) {
            array_count = lst.Count;
            value_array = lst.ToArray();
            type = ARRAY;
        }
        Value(JSON* obj) {
            value_object = obj;
            type = OBJECT;
        }
    };

    struct Field {
        Field(const char* key, Value value) : Key(key), Value(value) {}

        const char* Key;
        Value Value;
    };

    List<Field> lst;

    Value operator[](const char* key) {
        for (int i = 0; i < lst.Count; i++)
            if(strcmp(lst[i].Key, key) == 0)
                return lst[i].Value;
        return nullptr;        
    }

    void AddField(Field f) {
        lst.Add(f);
    }

    JSON(Field f) {
        AddField(f);
    }

    JSON() {
        
    }

    template<typename... Args>
    JSON(Field f, Args... args) {
        AddField(Field(f));
        AddField(args...);
    }

    template<typename... Args>
    void AddField(Field f, Args... args) {
        AddField(Field(f));
        AddField(args...);
    }

    string Serialize(bool pretty = true, int tabnumber = 1) {
        string s = "{";
        if(pretty) s += "\n";
        for (int i = 0; i < lst.Count; i++)
        {
            if(pretty) s += String::Format("%s\"%s\" : %s%s", (char*)String("").PadRight(tabnumber, '\t'), lst[i].Key, lst[i].Value.GetJSONValue(pretty, tabnumber), i != lst.Count - 1 ? ",\n" : "");
            else s += String::Format("\"%s\":%s%s", lst[i].Key, lst[i].Value.GetJSONValue(pretty, tabnumber), i != lst.Count - 1 ? "," : "");
        }
        if(pretty)  {
            s += "\n";
            s += String("").PadRight(tabnumber - 1, '\t');
        }
        s += "}";
        return s;
    }
};