#pragma once
#include "../kinderc.hpp"

Storage::Storage(bool isLocalStorage) {
    ls = isLocalStorage;
}
void Storage::setItem(string key, string value) {
    object(ls ? "localStorage" : "sessionStorage")["setItem"](string::Format("'%s'", key.CharArray), string::Format("'%s'", value.CharArray));
}
string Storage::getItem(string key) {
    return object(ls ? "localStorage" : "sessionStorage")["getItem"](string::Format("'%s'", key.CharArray));
}
void Storage::removeItem(string key) {
    object(ls ? "localStorage" : "sessionStorage")["removeItem"](string::Format("'%s'", key.CharArray));
}
void Storage::clear() {
    object(ls ? "localStorage" : "sessionStorage")["clear"]();
}
int Storage::get_length() {
    return (int)object(ls ? "localStorage" : "sessionStorage")["length"];
}