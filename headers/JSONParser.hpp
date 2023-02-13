#pragma once
#include "../kinderc.hpp"

#include "../code/impl/JSON/Parser/JSON.Parser.hpp"

JSON::Object JSON::DeserializeObject(const char* str) {
    return Implementations::JSON::Parser::DeserializeObject(str);
}

JSON::Array JSON::DeserializeArray(const char* str) {
    return Implementations::JSON::Parser::DeserializeArray(str);
}

template<typename T>
T JSON::DeserializeObjectAs(const char* str) {
    return Implementations::JSON::Parser::DeserializeObjectAs<T>(str);
}

template<typename T>
List<T> JSON::DeserializeArrayAs(const char* str) {
    return Implementations::JSON::Parser::DeserializeArrayAs<T>(str);
}

template<typename T>
const char* JSON::SerializeObjectOfType(T obj, bool pretty, int tabnumber) {
    return Implementations::JSON::Parser::SerializeObjectOfType<T>(obj, pretty, tabnumber);
}