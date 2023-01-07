#pragma once
#include "../kinderc.hpp"

class ComboBox : public Control<ComboBox> {
    #define __SELECT Find("select")
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

    /// @brief Renders the control.
    /// @return The HTML content of the control.
    string Render() {
        return (string)"<select>" + innerHTML + "</select>";
    };

    #undef __SELECT
};