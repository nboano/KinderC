#pragma once
#include "../kinderc.hpp"

Application::Title::operator char*() {
    return object("document")["title"];
}
void Application::Title::operator=(string v) {
    object("document")["title"] = (string)"\"" + v + "\"";
}