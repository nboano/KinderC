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

Property<void(*)(void*)> Application::OnBlur = Property<void(*)(void*)>([](void(*h)(void*)) {
    string cmd = Handler(h).GetWithPointer(nullptr , true);
    window["onblur"] = cmd;
});

Property<void(*)(void*)> Application::OnFocus = Property<void(*)(void*)>([](void(*h)(void*)) {
    string cmd = Handler(h).GetWithPointer(nullptr , true);
    window["onfocus"] = cmd;
});

Property<void(*)(void*)> Application::OnOnline = Property<void(*)(void*)>([](void(*h)(void*)) {
    string cmd = Handler(h).GetWithPointer(nullptr , true);
    window["ononline"] = cmd;
});

Property<void(*)(void*)> Application::OnOffline = Property<void(*)(void*)>([](void(*h)(void*)) {
    string cmd = Handler(h).GetWithPointer(nullptr , true);
    window["onoffline"] = cmd;
});

void Application::OpenWindow(string url, int width, int height, int left, int top) {
    string windowcmd = "\"popup";
    if(width != 0) windowcmd += (string)",width=" + (string)width;
    if(height != 0) windowcmd += (string)",height=" + (string)height;
    if(left != 0) windowcmd += (string)",left=" + (string)left;
    if(top != 0) windowcmd += (string)",top=" + (string)top;
    windowcmd += "\"";
    window["open"]((string)"\"" + url + "\"", "'_blank'", windowcmd);
}

void Application::Restart() {
    location.reload();
}

void Application::Print() {
    window["print"]();
}

void Application::GoToURL(string URL) {
    location.href = URL;
}

void Application::UseScreens() {
    screen_handle_change();
    document.body.onhashchange = new EventHandler(screen_handle_change);
}

void Application::UseControls() {
    TextBox::Use();
    ComboBox::Use();
}

void Application::IncludeScript(string URL) {
    $("head") << (string)"<script src='" + URL + "'></script>";
}

void Application::IncludeStyleSheet(string URL) {
    $("head") << (string)"<link rel='stylesheet' href='" + URL + "'/>";
}

void Application::EnableResponsiveView() {
    $("head") << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
}

Property<const char*> Enviroment::Platform = Property<const char*>(
    []() {
        return (const char*)navigator.platform;
    }
);

Property<const char*> Enviroment::UserAgent = Property<const char*>(
    []() {
        return (const char*)navigator.userAgent;
    }
);

Property<int> Enviroment::ThreadsNumber = Property<int>(
    []() {
        return (int)navigator["hardwareConcurrency"];
    }
);

Property<bool> Enviroment::IsOnline = Property<bool>(
    []() {
        return (bool)navigator["onLine"]["toString"]();
    }
);

Property<ScreenInformations> Enviroment::Screen = Property<ScreenInformations> (
    []() {
        ScreenInformations s;
        s.Width = (int)window["screen"]["width"];
        s.Height = (int)window["screen"]["height"];
        return s;
    }
);