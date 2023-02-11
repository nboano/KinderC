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
    for (int i = 0; i < flist.Count; i++)
    {
        switch (flist[i].Value.GetType())
        {
        case JSON::Value::DataType::STRING:
            printf("[%s] => <code>(string)</code> <b>%s</b><br>", flist[i].Key, (const char*)flist[i].Value);
            break;
        case JSON::Value::DataType::INT:
            printf("[%s] => <code>(int)</code> <b>%i</b><br>", flist[i].Key, (int)flist[i].Value);
            break;
        case JSON::Value::DataType::DOUBLE:
            printf("[%s] => <code>(double)</code> <b>%f</b><br>", flist[i].Key, (double)flist[i].Value);
            break;
        case JSON::Value::DataType::OBJECT:
            printf("[%s] => <code>(object)</code><br>", flist[i].Key);
            break;
        case JSON::Value::DataType::ARRAY:
            printf("[%s] => <code>(array)</code> <br>", flist[i].Key);
            break;
        case JSON::Value::DataType::NULL_T:
            printf("[%s] => <code>(null)</code>  <br>", flist[i].Key);
        default:
            break;
        }
    }
    puts("<br>");
}

void __var_dump(JSON::Array flist, const char* vname, const char* fname, int line) {

    printf("<br><code>JSON::Array</code> <b>%s</b> at %s:%i<br><br>", vname, fname, line);
    for (int i = 0; i < flist.Count; i++)
    {
        switch (flist[i].GetType())
        {
        case JSON::Value::DataType::STRING:
            printf("[%i] => <code>(string)</code> <b>%s</b><br>", i, (const char*)flist[i]);
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