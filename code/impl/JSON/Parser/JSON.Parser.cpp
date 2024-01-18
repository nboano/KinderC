#pragma once
#include "JSON.Parser.hpp"

KinderC::Serialization::JSON::Object Implementations::JSON::Parser::DeserializeObject(const char* str) {

    if(strcmp(str, "{}") == 0) return KinderC::Serialization::JSON::Object();

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

    KinderC::Serialization::JSON::Object flist;
    flist.Destroyable = false;

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

KinderC::Serialization::JSON::Array Implementations::JSON::Parser::DeserializeArray(const char* str) {

    if(strcmp(str, "[]") == 0) return KinderC::Serialization::JSON::Array();

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

    KinderC::Serialization::JSON::Array flist;

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
    KinderC::Serialization::JSON::Object obj = Implementations::JSON::Parser::DeserializeObject(str);
    
    T el;
    for(KinderC::Serialization::JSON::Field f : obj) el[f.Key] = f.Value;

    obj.~Object();
    return el;

    //return *((T*)&obj);
}

template<typename T> 
List<T> Implementations::JSON::Parser::DeserializeArrayAs(const char* str) {
    List<T> lst;
    KinderC::Serialization::JSON::Array arr = Implementations::JSON::Parser::DeserializeArray(str);

    for (int i = 0; i < arr.Count; i++)
    {
        T o = Implementations::JSON::Parser::DeserializeObjectAs<T>(arr[i]);
        o.Destroyable = false;
        lst.Add(o);
    }
    
    return lst;
}

