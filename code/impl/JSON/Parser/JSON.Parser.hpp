#pragma once
#include "../../../../headers/json.hpp"
#include "../../../../headers/string.hpp"

namespace Implementations::JSON::Parser
{
    ::JSON::Object DeserializeObject(const char* str);

    ::JSON::Array DeserializeArray(const char* str);

    template<typename T>
    T DeserializeObjectAs(const char* str);

    template<typename T>
    List<T> DeserializeArrayAs(const char* str);

    template<typename T>
    const char* SerializeObjectOfType(T obj, bool pretty, int tabnumber);
} // namespace Implementations::JSON::Parser

namespace Implementations::JSON::Parser::Helpers
{
    const char* GetFieldName(char*& chptr);

    const char* GetFieldValue(char*& chptr);

    void GetSeparator(char*& chptr);

    void TypiseObject(::JSON::Object array);

    void TypiseArray(::JSON::Array array);
} // namespace Implementations::JSON::Parser::Helpers

#include "JSON.Parser.cpp"
#include "Helpers/JSON.Parser.Helpers.cpp"

