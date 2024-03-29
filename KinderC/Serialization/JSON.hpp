#pragma once
#include "../../kinderc.hpp"
#include "../../headers/list.hpp"


namespace KinderC::Serialization {

    /// @brief Use this class to build and parse JSON strings.
    class JSON {
    public:

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
            public:
        };

        template<typename T>
        class TypisedArray: public List<T> {
            public:
            using List<T>::List;
            TypisedArray(Array arr) {
                for(Value val : arr) {
                    T elm = (T)val;
                    elm.Destroyable = false;
                    this->Add(elm);
                }
            }
        };

        template<>
        class TypisedArray<const char*> : public List<const char*> {
            public:
            using List<const char*>::List;
            TypisedArray(Array arr) {
                for(Value val : arr) {
                    this->Add(val);
                }
            }
        };

        template<>
        class TypisedArray<int> : public List<int> {
            public:
            using List<int>::List;
            TypisedArray(Array arr) {
                for(Value val : arr) {
                    this->Add(val);
                }
            }
        };

        template<>
        class TypisedArray<double> : public List<double> {
            public:
            using List<double>::List;
            TypisedArray(Array arr) {
                for(Value val : arr) {
                    this->Add(val);
                }
            }
        };

        /// @brief A JSON object, which can contain a list of various fields.
        class Object: public List<Field> {
            public:
            Field& operator[](int i) {
                return arrptr[i];
            }
            Value& operator[](const char* key) {
                for (int i = 0; i < Count; i++) {
                    if(strcmp(arrptr[i].Key, key) == 0)
                        return arrptr[i].Value;
                }

                JSON::Value init_val = nullptr;
                // init_val = 0;
                // init_val = "";

                Add({ key, init_val });
                return operator[](key); 
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
            template<typename T>
            Value(TypisedArray<T> tArr);
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


        static Object DeserializeObject(const char* str);

        static Array DeserializeArray(const char* str);

        template<typename T>
        static T DeserializeObjectAs(const char* str);

        template<typename T>
        static List<T> DeserializeArrayAs(const char* str);

        static string SerializeObject(JSON::Object obj, bool pretty = true, int tabnumber = 1);
    };

}
    
#include "Impl/JSON.cpp"

