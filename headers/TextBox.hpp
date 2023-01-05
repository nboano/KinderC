#pragma once
#include "../kinderc.hpp"

/// @brief This Control allows the user to input text or numbers. It's composed by a label (desc attribute) and an input tag.
class TextBox : public Control<TextBox> {
    public:

    /// Pointer to the input tag inside the TextBox.
    #define __INPUTBOX Find("input")

    // Initialises the TextBox control.
    ControlInit(TextBox);

    /// @brief Sets or gets the value of the TextBox.
    Property<const char*> Value {
        [](void* elm) {
            return (const char*)((TextBox*)elm)->__INPUTBOX.getProperty("value");
        },
        [](void* elm, const char* value) {
            ((TextBox*)elm)->__INPUTBOX.setProperty("value", value);
        }, this
    };

    /// @brief Tells if the TextBox must allow only numeric input (number attribute).
    Property<bool> AllowOnlyNumbers {
        [](void* elm) {
            return strcmp(((TextBox*)elm)->__INPUTBOX.getAttribute("type"), "number") == 0;
        },
        [](void* elm, bool value) {
            value ? ((TextBox*)elm)->__INPUTBOX.setAttribute("type", "number") : ((TextBox*)elm)->__INPUTBOX.setAttribute("type", "text");
        }, this
    };

    /// @brief Tells if the TextBox is a required input in a form (required attribute).
    Property<bool> Required {
        [](void* elm) {
            return ((TextBox*)elm)->__INPUTBOX.hasAttribute("required");
        },
        [](void* elm, bool value) {
            value ? ((TextBox*)elm)->__INPUTBOX.setAttribute("required", "") : ((TextBox*)elm)->__INPUTBOX.removeAttribute("required");
        }, this
    };

    /// @brief Sets of get the input pattern of the TextBox, as a regex (pattern attribute).
    Property<const char*> Pattern {
        [](void* elm) {
            return (const char*)((TextBox*)elm)->__INPUTBOX.getAttribute("pattern");
        },
        [](void* elm, const char* value) {
            ((TextBox*)elm)->__INPUTBOX.setAttribute("pattern", value);
        }, this
    };

    /// @brief Sets of gets the minimum number writable if the TextBox number attribute is present.
    Property<int> MinValue {
        [](void* elm) {
            return atoi(((TextBox*)elm)->__INPUTBOX.getAttribute("min"));
        },
        [](void* elm, int value) {
            ((TextBox*)elm)->__INPUTBOX.setAttribute("min", (string)value);
        }, this
    };

    /// @brief Sets of gets the maximum number writable if the TextBox number attribute is present.
    Property<int> MaxValue {
        [](void* elm) {
            return atoi(((TextBox*)elm)->__INPUTBOX.getAttribute("max"));
        },
        [](void* elm, int value) {
            ((TextBox*)elm)->__INPUTBOX.setAttribute("max", (string)value);
        }, this
    };

    /// @brief Method executed to render the control.
    string Render() {
        return (string)"<label>" + getAttribute("desc") + "&nbsp;&nbsp;<input type='text' value=\"" + innerText + "\"/></label>";
    }

    /// @brief Method executed after the render.
    void PostRender() {
        CSS("display", "inline-block");
        CSS("padding", "5px");
        CSS("margin", "10px");
        CSS("border-radius", "5px");
        CSS("font-family", "sans-serif");

        __INPUTBOX.CSS("border-radius", "5px");
        __INPUTBOX.CSS("border", "1px solid grey");

        AllowOnlyNumbers = hasAttribute("number");
        Required = hasAttribute("required");
        if(hasAttribute("pattern"))     Pattern = getAttribute("pattern");
        if(hasAttribute("min"))         MinValue = atoi(getAttribute("min"));
        if(hasAttribute("max"))         MaxValue = atoi(getAttribute("max"));
        if(hasAttribute("color"))       __INPUTBOX.CSS("color", getAttribute("color"));
        if(hasAttribute("bgcolor"))     __INPUTBOX.CSS("background-color", getAttribute("bgcolor"));
    }

    #undef __INPUTBOX
};