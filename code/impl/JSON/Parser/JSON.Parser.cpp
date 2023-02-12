#pragma once
#include "JSON.Parser.hpp"

::JSON::Object Implementations::JSON::Parser::DeserializeObject(const char* str) {
    char* aptr = new char[strlen(str) + 1];
    strcpy(aptr, str);

    // Rimozione } alla fine.
    char* tptr = aptr + strlen(str);
    while(*--tptr != '}');
    *tptr = ',';
    *++tptr = '\0';

    char* chptr = aptr;

    // Rimozione { all'inizio.
    while(*chptr++ != '{');
    *(chptr - 1) = ' ';

    ::JSON::Object flist;

    do
    {
        const char* t_key = Implementations::JSON::Parser::Helpers::GetFieldName(chptr);
        char* key = new char[strlen(t_key) + 1];
        strcpy(key, t_key);

        Implementations::JSON::Parser::Helpers::GetSeparator(chptr);

        const char* t_val = Implementations::JSON::Parser::Helpers::GetFieldValue(chptr);
        char* val = new char[strlen(t_val) + 1];
        strcpy(val, t_val);

        flist.Add({key, val});

    } while (*chptr != '\0');
    
    delete[] aptr;

    Implementations::JSON::Parser::Helpers::TypiseObject(flist);

    return flist;
}

::JSON::Array Implementations::JSON::Parser::DeserializeArray(const char* str) {
    char* aptr = new char[strlen(str) + 1];
    strcpy(aptr, str);

    // Rimozione ] alla fine.
    char* tptr = aptr + strlen(str);
    while(*--tptr != ']');
    *tptr = ',';
    *++tptr = '\0';

    char* chptr = aptr;

    // Rimozione [ all'inizio.
    while(*chptr++ != '[');
    *(chptr - 1) = ' ';

    ::JSON::Array flist;

    do
    {
        const char* t_val = Implementations::JSON::Parser::Helpers::GetFieldValue(chptr);
        char* val = new char[strlen(t_val) + 1];
        strcpy(val, t_val);

        flist.Add(val);

    } while (*chptr != '\0');
    
    delete[] aptr;

    Implementations::JSON::Parser::Helpers::TypiseArray(flist);


    return flist;
}

template<typename T>
T Implementations::JSON::Parser::DeserializeObjectAs(const char* str) {
    ::JSON::Object jobj = Implementations::JSON::Parser::DeserializeObject(str);
    T obj;

    T::Fields::Init();

    for (int i = 0; i < jobj.Count; i++)
    {
        (T::Fields::List)[i].AssignTo(obj, jobj[i].Value);
    }
    
    return obj;
}

