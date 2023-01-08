#pragma once
#include "../kinderc.hpp"

class ComboBox : public Control<ComboBox> {
    #define __SELECT Find("select")
    #define __LABEL Find("label > span")
public:
    ControlInit(ComboBox);

    /// @brief Sets the data contained in the ComboBox as a list of string literals.
    Property<List<const char*>> Data {
        [](void* elm, List<const char*> value) {
            HTMLElement select = ((ComboBox*)elm)->__SELECT;
            select.innerHTML = "";
            for (int i = 0; i < value.Count; i++)
            {
                select.Append(string::Format("<option>%s</option>", value[i]));
            }
        }, this
    };

    /// @brief Sets or gets the description of the element (desc attribute).
    Property<const char*> Description {
        [](void* elm) {
            return (const char*)((ComboBox*)elm)->__LABEL.innerHTML;
        },
        [](void* elm, const char* value) {
            ((ComboBox*)elm)->__LABEL.innerHTML = value;
        }, this
    };

    /// @brief Sets or gets the value of the element.
    Property<const char*> Value {
        [](void* elm) {
            return (const char*)((ComboBox*)elm)->__SELECT.getProperty("value");
        },
        [](void* elm, const char* value) {
            ((ComboBox*)elm)->__SELECT.setProperty("value", value);
        }, this
    };

    /// @brief Sets or gets the selected index of the element.
    Property<int> SelectedIndex {
        [](void* elm) {
            return (int)((ComboBox*)elm)->__SELECT.getProperty("selectedIndex");
        },
        [](void* elm, int value) {
            ((ComboBox*)elm)->__SELECT.setProperty("selectedIndex", (string)value);
        }, this
    };

    /// @brief Renders the control.
    /// @return The HTML content of the control.
    string Render() {
        return (string)"<label><span></span>&nbsp;&nbsp;<select>" + innerHTML + "</select></label>";
    };

    void PostRender() {
        if(hasAttribute("desc")) Description = getAttribute("desc");
        if(hasAttribute("value")) Value = getAttribute("value");
    }

    #undef __SELECT
    #undef __LABEL
};