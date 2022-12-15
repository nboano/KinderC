#pragma once
#include "../kinderc.hpp"

Property<const char*> Application::Title = Property<const char*>(
    []() {
        return (const char*)object("document")["title"];
    },
    [](const char* value) {
        object("document")["title"] = (string)"\"" + value + "\"";
    }
);

Property<const char*> Application::UserLanguage = Property<const char*>(
    []() {
        return (const char*)navigator.language;
    }
);