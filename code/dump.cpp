#pragma once
#include "../kinderc.hpp"

/// @brief Dumps a variable of every type.
#define var_dump(variable) __var_dump(variable, #variable, __FILE__, __LINE__)

void __var_dump(int n, const char* vname, const char* fname, int line) {
    printf("<br><code>int</code> <b>%s</b> at %s:%i<br><br>", vname, fname, line);
    printf("%i", n);
    puts("<br>");
}

void __var_dump(double n, const char* vname, const char* fname, int line) {
    printf("<br><code>double</code> <b>%s</b> at %s:%i<br><br>", vname, fname, line);
    printf("%f", n);
    puts("<br>");
}

void __var_dump(const char* s, const char* vname, const char* fname, int line) {
    printf("<br><code>const char*</code> <b>%s</b> at %s:%i<br><br>", vname, fname, line);
    printf("%s", s);
    puts("<br>");
}

void __var_dump(string s, const char* vname, const char* fname, int line) {
    printf("<br><code>string</code> <b>%s</b> at %s:%i<br><br>", vname, fname, line);
    printf("%s", (char*)s);
    puts("<br>");
}

void __var_dump(JSON::Object flist, const char* vname, const char* fname, int line) {
    printf("<br><code>JSON::Object</code> <b>%s</b> at %s:%i<br><br>", vname, fname, line);

    int size = 0;
    int l;

    for (int i = 0; i < flist.Count; i++)
    {
        switch (flist[i].Value.GetType())
        {
        case JSON::Value::DataType::STRING:
            l = strlen(flist[i].Value);
            printf("[%s] => <code>(const char*)[%i]</code> <b>%s</b><br>", flist[i].Key, l, (const char*)flist[i].Value);
            break;
        case JSON::Value::DataType::INT:
            l = sizeof(int);
            printf("[%s] => <code>(int)[%i]</code> <b>%i</b><br>", flist[i].Key, l, (int)flist[i].Value);
            break;
        case JSON::Value::DataType::DOUBLE:
            l = sizeof(double);
            printf("[%s] => <code>(double)[%i]</code> <b>%f</b><br>", flist[i].Key, l, (double)flist[i].Value);
            break;
        case JSON::Value::DataType::OBJECT:
            l = sizeof(JSON::Object);
            printf("[%s] => <code>(object)[%i]</code><br>", l, flist[i].Key);
            break;
        case JSON::Value::DataType::ARRAY:
            l = sizeof(JSON::Array);
            printf("[%s] => <code>(array)[%i]</code> <br>", l, flist[i].Key);
            break;
        case JSON::Value::DataType::NULL_T:
            l = sizeof(nullptr);
            printf("[%s] => <code>(null)[%i]</code>  <br>", l, flist[i].Key);
        default:
            break;
        }
        size += l;
    }
    printf("<br><b>%i</b> fields. <b>%i</b> B.<br>", (int)flist.Count, size);
}

void __var_dump(JSON::Array flist, const char* vname, const char* fname, int line) {

    printf("<br><code>JSON::Array</code> <b>%s</b> at %s:%i<br><br>", vname, fname, line);
    for (int i = 0; i < flist.Count; i++)
    {
        switch (flist[i].GetType())
        {
        case JSON::Value::DataType::STRING:
            printf("[%i] => <code>(const char*)</code> <b>%s</b><br>", i, (const char*)flist[i]);
            break;
        case JSON::Value::DataType::INT:
            printf("[%i] => <code>(int)</code> <b>%i</b><br>", i, (int)flist[i]);
            break;
        case JSON::Value::DataType::DOUBLE:
            printf("[%i] => <code>(double)</code> <b>%f</b><br>", i, (double)flist[i]);
            break;
        case JSON::Value::DataType::OBJECT:
            printf("[%i] => <code>(object)</code><br>", i);
            break;
        case JSON::Value::DataType::ARRAY:
            printf("[%i] => <code>(array)</code><br>", i);
            break;
        case JSON::Value::DataType::NULL_T:
            printf("[%i] => <code>(null)</code><br>", i);
        default:
            break;
        }
    }
    puts("<br>");
}