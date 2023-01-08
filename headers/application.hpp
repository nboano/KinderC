#pragma once
#include "../kinderc.hpp"

void handle_screen_change(void*);

void use_screens();

/// @brief Use this class to manage the Web Application.
class Application {
    public:

    /// @brief The title of the application, usually displayed in the top bar.
    static Property<const char*> Title;

    /// @brief Opens a new window with the specified parameters.
    /// @param url The new window URL. 
    /// @param width The new window width, in px (ignored on mobile).
    /// @param height The new window height, in px (ignored on mobile).
    /// @param left The new window distance from the screen left, in px (ignored on mobile).
    /// @param top The new window distance from the screen top, in px (ignored on mobile).
    static void OpenWindow(string url = "about:blank", int width = 0, int height = 0, int left = 0, int top = 0);

    /// @brief Restarts the application, reloading the page.
    static void Restart();

    /// @brief Opens the default print window.
    static void Print();

    /// @brief Moves the user to a specified URL.
    /// @param URL The URL.
    static void GoToURL(string URL);

    /// @brief Enables the auto management of the <screen> tags.
    static void UseScreens();

    /// @brief Enables the responsive style for the application. 
    static void EnableResponsiveView();

    /// @brief Includes a JavaScript file from a given URL.
    /// @param URL The URL (absolute or relative).
    static void IncludeScript(string URL);

    /// @brief Includes a CSS Stylesheet from a given URL.
    /// @param URL The URL (absolute or relative).
    static void IncludeStyleSheet(string URL);

    /// @brief Enables KinderC controls such as TextBox, ComboBox etc. inside the application.
    static void UseControls();

    /// @brief Sets an handler for when the user leaves the application.
    static Property<void(*)(void*)> OnBlur;

    /// @brief Sets an handler for when the user returns to the application.
    static Property<void(*)(void*)> OnFocus;

    /// @brief Sets an handler for when the network status changes to ONLINE.
    static Property<void(*)(void*)> OnOnline;

    /// @brief Sets an handler for when the network status changes to OFFLINE.
    static Property<void(*)(void*)> OnOffline;
};