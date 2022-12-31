#pragma once
#include "../kinderc.hpp"

/// @brief Struct that contains the informations about the screen.
struct ScreenInformations {

    /// @brief The screen width.
    int Width;

    /// @brief The screen height.
    int Height;
};

/// @brief Class that allows you to get the information about the browser, the network and the device.
class Enviroment {
    public:

    /// @brief The user selected language, for example "it-IT"
    static Property<const char*> Language;

    /// @brief The device platform, for example "Win32"
    static Property<const char*> Platform;

    /// @brief The browser User Agent.
    static Property<const char*> UserAgent;

    /// @brief The number of threads reserved for the applications.
    static Property<int> ThreadsNumber;

    /// @brief Tells you if the device is online or not.
    static Property<bool> IsOnline;

    /// @brief Retrieves informations about the screen.
    static Property<ScreenInformations> Screen;
};