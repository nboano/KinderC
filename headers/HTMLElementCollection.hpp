#pragma once
#include "../kinderc.hpp"

class HTMLElementCollection {
    public:

        /// @brief Creates a new HTMLElementCollection of elements that match a valid query.
        /// @param CSS_QUERY A CSS query.
        /// @param doc The document where the system must search.
        HTMLElementCollection(string CSS_QUERY, HTMLDocument doc = document);

        /// @brief Select an element of a given index.
        /// @param index The index.
        /// @return The n-HTMLElement of the collection.
        HTMLElement operator [] (int index);

        /// @brief Destructor of the HTMLElementCollection class.
        ~HTMLElementCollection();

        #ifndef __INTELLISENSE__
        int get_length();
        __declspec(property(get = get_length)) int length;
        #else

        /// @brief It's the length of the collection.
        int length;

        #endif

        /// @brief Sets a property of all the elements of the collection to a certain value.
        /// @param key The property name.
        /// @param value The property value.
        void setProperty(const char* key, const char* value);

        /// @brief Gets a string containing all the properties of the elements concatenated.
        /// @param key The property name.
        /// @return The property value.
        string getProperty(const char* key);

        /// @brief Sets an attribute to all the elements of the collection.
        /// @param key The attribute name.
        /// @param value The attribute value.
        void setAttribute(string key, string value);

        /// @brief Sets a CSS property of all the elements in the collection.
        /// @param key The property name.
        /// @param value The property value.
        void setStyleProperty(string key, string value);

        /// @brief An associative, writeonly array to manage the attributes of the element collection.
        __declspec(property(put = setAttribute)) string attributes[];

        /// @brief An associative, writeonly array to manage the CSS properties of the element.
        __declspec(property(put = setStyleProperty)) string style[];

        /// @brief Adds an event listener to the element in the collection.
        /// @param eventname A string containing the event name (es. "click").
        /// @param handler An handler.
        void addEventListener(const char* eventname, void(*handler)(HTMLElement&));

        #pragma region PROPERTIES

        // Sets or gets the ID attribute of the collection elements.
        prop(id);
        // The HTML code contained into the element.
        prop(innerHTML);
        // The HTML code of the element and its content.
        prop(outerHTML);
        // The text contained into the element.
        prop(innerText);
        // The text contained into the element.
        prop(outerText);
        // The text content.
        prop(textContent);
        // The tag name (XML).
        prop(nodeName);
        // The node type (XML).
        prop(nodeType);
        // The node value (XML).
        prop(nodeValue);
        // The lang attribute.
        prop(lang);
        // The title attribute. If set, provides a tooltip on hover.
        prop(title);
        // The tag name of the element.
        prop(tagName);
        prop(scrollHeight);
        prop(scrollLeft);
        prop(scrollTop);
        prop(scrollWidth);
        prop(dir);
        // The class name of the element.
        prop(className);
        // Sets the access key used to access the element.
        prop(accessKey);

        /// Event fired at click.
        ev_HTMLElementColl(onclick);
        // Event fired at double click.
        ev_HTMLElementColl(ondblclick);
        // Event fired when the mouse button is pressed on the element.
        ev_HTMLElementColl(onmousedown);
        // Event fired when the mouse moves on the element.
        ev_HTMLElementColl(onmousemove);
        // Event fired when the mouse goes out of the element.
        ev_HTMLElementColl(onmouseout);
        // Event fired when the mouse goes over the element.
        ev_HTMLElementColl(onmouseover);
        // Event fired when the mouse is released over the element.
        ev_HTMLElementColl(onmouseup);
        // Event fired when the mouse scrolls on the element.
        ev_HTMLElementColl(onmousewheel);
        // Event fired when the mouse wheel is moved on the element.
        ev_HTMLElementColl(onwheel);

        #pragma endregion
    private:
        #ifdef __INTELLISENSE__
        int get_length();
        #endif

        HTMLElement* collectionptr;
        int len;
};
