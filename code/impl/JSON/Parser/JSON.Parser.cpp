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
    ::JSON::Object obj = Implementations::JSON::Parser::DeserializeObject(str);
    return *((T*)&obj);
}

template<typename T> 
List<T> Implementations::JSON::Parser::DeserializeArrayAs(const char* str) {
    ::JSON::Array j_arr = Implementations::JSON::Parser::DeserializeArray(str);

    T arr[1024];

    for (int i = 0; i < j_arr.Count; i++)
    {
        arr[i] = Implementations::JSON::Parser::DeserializeObjectAs<T>(j_arr[i]);
    }
    
    List<T> lst {(int)j_arr.Count};

    for (int i = 0; i < j_arr.Count; i++)
    {
        lst.Add(arr[i]);
    }

    return lst;
}

