#pragma once
#include "../kinderc.hpp"

/// @brief Enum of the possible types of a TextBox.
enum TextBoxType {
    /// @brief Disables autocomplete.
    NOAUTOCOMPLETE,
    
    /// @brief Enables generic autocomplete.
    DEFAULT,

    /// @brief Suggests a person name.
    PERSON_NAME,

    /// @brief Suggests an email.
    EMAIL,

    /// @brief Suggests a username.
    USERNAME,

    /// @brief Suggests a new password.
    NEW_PASSWORD,

    /// @brief Suggests a password.
    PASSWORD,

    /// @brief Suggests a one-time-code (OTC).
    OTC,

    /// @brief Allows the user to enter only a number.
    NUMBER = -1
};

/// @brief This Control allows the user to input text or numbers. It's composed by a label (Description) and an input tag (Value).
class TextBox : public Control<TextBox> {
    private:
    static constexpr const char* types[] = {"off", "on", "name", "email", "username", "new-password", "password", "one-time-code"};

    public:

    /// Pointer to the input tag inside the TextBox.
    #define __INPUTBOX Find("input")
    #define __LABEL Find("label > span")

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

    /// @brief Sets or gets the description of the TextBox (desc attribute).
    Property<const char*> Description {
        [](void* elm) {
            return (const char*)((TextBox*)elm)->__LABEL.innerHTML;
        },
        [](void* elm, const char* value) {
            ((TextBox*)elm)->__LABEL.innerHTML = value;
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

    /// @brief Tells if the element is enabled or not.
    Property<bool> Enabled {
        [](void* elm) {
            return !((TextBox*)elm)->__INPUTBOX.hasAttribute("disabled");
        },
        [](void* elm, bool value) {
            value? ((TextBox*)elm)->__INPUTBOX.removeAttribute("disabled") : ((TextBox*)elm)->__INPUTBOX.setAttribute("disabled", ""); 
        }, this
    };

    /// @brief Sets the type of the TextBox, for example EMAIL, PASSWORD... (see TextBoxType)
    Property<TextBoxType> Type {
        [](void* elm, TextBoxType value) {
            switch (value)
            {
                case EMAIL:
                    ((TextBox*)elm)->__INPUTBOX.setAttribute("type", "email");
                    break;
                case PASSWORD:
                case NEW_PASSWORD:
                    ((TextBox*)elm)->__INPUTBOX.setAttribute("type", "password");
                    break;
                case NUMBER:
                    ((TextBox*)elm)->AllowOnlyNumbers = true;
                    break;
                default:
                    ((TextBox*)elm)->__INPUTBOX.setAttribute("autocomplete", types[value]);
                    break;
            }
        }, this
    };

    /// @brief Method executed to render the control.
    string Render() {
        return (string)"<label><span></span>&nbsp;&nbsp;<input type='text' value=\"" + innerText + "\"/></label>";
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

        if(hasAttribute("desc"))        Description = getAttribute("desc");
        if(hasAttribute("pattern"))     Pattern = getAttribute("pattern");
        if(hasAttribute("min"))         MinValue = atoi(getAttribute("min"));
        if(hasAttribute("max"))         MaxValue = atoi(getAttribute("max"));
        if(hasAttribute("color"))       __INPUTBOX.CSS("color", getAttribute("color"));
        if(hasAttribute("bgcolor"))     __INPUTBOX.CSS("background-color", getAttribute("bgcolor"));
    }

    #undef __INPUTBOX
    #undef __LABEL
};