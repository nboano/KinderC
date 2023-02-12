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

        Field(int T::*p) {FieldPointer.AsInt = p; FieldType = INT;}
        Field(double T::*p) {FieldPointer.AsDouble = p; FieldType = DOUBLE;}
        Field(const char* T::*p) {FieldPointer.AsCharArray = p; FieldType = CHPTR;}

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
    };
} // namespace Reflection

#define FIELDS(T, ...) struct Fields { static Reflection::Field<T>* List; static void Init() { static Reflection::Field<T> __f[] = {__VA_ARGS__}; List = __f; } };