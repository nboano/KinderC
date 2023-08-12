#pragma once
#include "../../../../KinderC/Serialization/KinderC.Serialization.hpp"
#include "../../../../headers/string.hpp"

namespace Implementations::JSON::Parser
{

    KinderC::Serialization::JSON::Object DeserializeObject(const char* str);

    KinderC::Serialization::JSON::Array DeserializeArray(const char* str);

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

    void TypiseObject(KinderC::Serialization::JSON::Object array);

    void TypiseArray(KinderC::Serialization::JSON::Array array);
} // namespace Implementations::JSON::Parser::Helpers

#include "JSON.Parser.cpp"
#include "Helpers/JSON.Parser.Helpers.cpp"

