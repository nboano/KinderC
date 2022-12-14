#pragma once
#include "../kinderc.hpp"

Application::Title::get char*() {
    return object("document")["title"];
}
void Application::Title::set(string v) {
    object("document")["title"] = (string)"\"" + v + "\"";
}