#pragma once
#include "../kinderc.hpp"

class HTMLBodyElement;

/// @brief This class represents an HTML document.
class HTMLDocument {
public:

    /// @brief Creates a pointer to a document object.
    /// @param n The document object name.
    HTMLDocument(const char* n);

    /// @brief Creates a pointer to the current document.
    HTMLDocument();

    /// @brief Appends an HTMLElement to the document.
    /// @param element The element to append.
    void Append(HTMLElement* element);

    /// @brief Appends a text to the document.
    /// @param text A string literal containing a text.
    void Append(const char* text);

    /// @brief Appends an HTMLElement to the document.
    /// @param element The element to append.
    void operator << (HTMLElement* element) {
        Append(element);
    }

    /// @brief Appends a text to the document.
    /// @param text A string literal containing a text.
    void operator << (const char* text) {
        Append(text);
    }

    /// @brief Performs a node selection using a CSS query.
    /// @param CSS_QUERY The CSS query.
    /// @return The first node associated.
    HTMLElement querySelector(const char* CSS_QUERY);

    /// @brief Performs a multiple node selection using a CSS query.
    /// @param CSS_QUERY The CSS query.
    /// @return A collection containing all the nodes associated.
    HTMLElementCollection querySelectorAll(const char* CSS_QUERY);

    /// @brief Select a node by the ID.
    /// @param ID The ID to look for.
    /// @return The node with that id, if present.
    HTMLElement getElementById(const char* ID);
    
    #ifndef __INTELLISENSE__
    /// @deprecated Use the Name property instead.
    const char* getname() { if ((int)name != -1) return (const char*)name; else return "document"; }

    /// @deprecated Use the body property instead.
    HTMLBodyElement getbody();

    /// @brief The document name.
    __declspec(property(get = getname)) const char* Name;

    /// @brief The document body element.
    __declspec(property(get = getbody)) HTMLBodyElement body;
    #else

    /// @brief The document name.
    const char* Name;

    /// @brief The document body element.
    HTMLBodyElement body;

    #endif
private:
    char* name;

    #ifdef __INTELLISENSE__
    const char* getname();
    HTMLBodyElement getbody();
    #endif
};

/// @brief The current document.
HTMLDocument document;

/// @brief Given a CSS query, returns the first HTMLElement that matches it.
/// @param CSS_QUERY A valid CSS query.
/// @return A corresponding HTMLElement.
HTMLElement $(const char* CSS_QUERY);

/// @brief Given a CSS query, returns a collection of elements that match it.
/// @param CSS_QUERY A valid CSS query.
/// @return An element collection.
HTMLElementCollection $$(const char* CSS_QUERY);