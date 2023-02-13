#pragma once
#include "../kinderc.hpp"

namespace Reflection
{
    /// @brief Defines a field of a generic structure (class, struct...).
    /// @tparam T The structure type.
    template<typename T>
    struct Field {

        union Container
        {
            int T::*AsInt;
            double T::*AsDouble;
            const char* T::*AsCharArray;
        } FieldPointer;

        enum Type : char {
            INT,
            DOUBLE,
            CHPTR,
        } FieldType;

        Field(int T::*p, const char* name) {FieldPointer.AsInt = p; FieldType = INT; Name = name;}
        Field(double T::*p, const char* name) {FieldPointer.AsDouble = p; FieldType = DOUBLE; Name = name;}
        Field(const char* T::*p, const char* name) {FieldPointer.AsCharArray = p; FieldType = CHPTR; Name = name;}

        const char* Name;

        void AssignTo(T& structure, JSON::Value value) {
            switch (FieldType)
            {
            case INT:
                structure.*(FieldPointer.AsInt) = (int)value;
                break;
            case DOUBLE:
                structure.*(FieldPointer.AsDouble) = (double)value;
                break;
            case CHPTR:
                structure.*(FieldPointer.AsCharArray) = (const char*)value;
                break;
            }
        }

        JSON::Value GetValueFrom(T structure) {
            switch (FieldType)
            {
            case INT:
                return structure.*(FieldPointer.AsInt);
            case DOUBLE:
                return structure.*(FieldPointer.AsDouble);
            case CHPTR:
                return structure.*(FieldPointer.AsCharArray);
            }
        }
    };
} // namespace Reflection

#define FIELDS(T, ...) struct Fields { static Reflection::Field<T>* List; static int Count; static void Init() { static Reflection::Field<T> __f[] = {__VA_ARGS__}; List = __f; Count = sizeof(__f) / sizeof(__f[0]); } };
#define FIELD(T, FIELDNAME) {&T::FIELDNAME, #FIELDNAME }