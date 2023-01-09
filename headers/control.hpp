#pragma once
#include "../kinderc.hpp"

// Use this macro to initialize the control class, passing the control type as first parameter. (Es. MyControl)
#define ControlInit(name) name(HTMLElement el) : Control(el) {}; static constexpr const char* TagName = #name;

template<class T>

/// @brief Use this class to create and manage custom HTML Controls. This class inherits HTMLElement.
/// @tparam T The Type of the custom control.
class Control : public HTMLElement {
public:

    /// @brief Function executed when all the controls of the specified type are rendered.
    static void(*OnRender)();

    /// @brief Function executed on the first rendering process.
    static void(*OnFirstRender)();

    /// @brief Allows you to cast a generic HTMLElement to a Control.
    /// @param el A generic HTMLElement object.
    Control(HTMLElement el) : HTMLElement(el) {}

    /// @brief Tells the enviroment that the custom control must be activated.
    static void Use();

    /// @brief The control render function. This will be called when a control should be rendered.
    /// @return An HTML string that will be written inside the control.
    string Render() { return ""; }

    void PostRender() {}
private:
    static void ChangeHandler(void*);

    static bool firstrender;
};