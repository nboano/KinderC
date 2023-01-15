#pragma once
#include "../kinderc.hpp"

/// @brief Use this class to manage DOM elements.
class HTMLElement
{
public:

	/// @brief Given a CSS query, performs a search and makes the object point to the first mathing element.
	/// @param CSS_QUERY A CSS query, as a string literal.
	/// @param doc The document where the element is contained. Defaults to the current document.
	HTMLElement(const char* CSS_QUERY, HTMLDocument doc = document);

	/// @brief Given a CSS query and a number, performs a search and makes the object point to the n matching element.
	/// @param CSS_QUERY A CSS query, as a string literal.
	/// @param CollectionIndex The index of the element to take in the collection.
	/// @param doc The document where the element is contained. Defaults to the current document.
	HTMLElement(const char* CSS_QUERY, int CollectionIndex, HTMLDocument doc = document);

	/// @brief Creates a new element.
	/// @param TAGNAME The new element tag name.
	/// @param ID The new element ID.
	/// @param doc The location where the new element will be created. Defaults to the current document.
	HTMLElement(const char* TAGNAME, const char* ID, HTMLDocument doc = document);

	/// @brief Destroys the pointer to the element
	~HTMLElement();

	/// @brief Appends an HTMLElement to the element.
	/// @param element The element to append.
	void Append(HTMLElement* element);

	/// @brief Appends a text to the element.
	/// @param text A string literal containing a text.
	void Append(const char* text);

	/// @brief Appends an HTMLElement to the element.
	/// @param element The element to append.
	void operator << (HTMLElement* element) {
		Append(element);
	}

	/// @brief Appends a text to the element.
	/// @param text A string literal containing a text.
	void operator << (const char* text) {
		Append(text);
	}

	/// @brief Sets a property of the element.
	/// @param key The property name.
	/// @param value The property value.
	void setProperty(const char* key, const char* value);

	/// @brief Gets a property of the element.
	/// @param key The property name.
	/// @return The property value.
	char* getProperty(const char* key);

	/// @brief Sets an attribute of the element.
	/// @param key The attribute name.
	/// @param value The attribute value.
	void setAttribute(const char* key, const char* value);

	/// @brief Gets an attribute of the element.
	/// @param key The attribute name.
	/// @return The attribute value.
	char* getAttribute(const char* key);

	bool hasAttribute(const char* key);

	/// @brief Removes an attribute from an element.
	/// @param key The attribute name.
	void removeAttribute(const char* key);

	/// @brief Sets a CSS property of the element.
	/// @param key The property name.
	/// @param value The property value.
	void setStyleProperty(const char* key, const char* value);

	/// @brief Gets a CSS property of the element.
	/// @param key The property name.
	/// @return The property value.
	char* getStyleProperty(const char* key);

	/// @brief Returns the first matching descendant of a given CSS query.
	/// @param CSS_QUERY A given CSS query.
	/// @return The first matching descendant of the element.
	HTMLElement Find(const char* CSS_QUERY);

	/// @brief Returns a collection containing all the descendants that match the query.
	/// @param CSS_QUERY The query.	
	/// @return A collection.
	HTMLElementCollection FindAll(const char* CSS_QUERY);

	/// @brief Sets a CSS property of the element.
	/// @param property_name The property name.
	/// @param value The property value.
	void CSS(const char* property_name, const char* value) {
		setStyleProperty(property_name, value);
	}

	/// @brief Gets a CSS property of the element.
	/// @param property_name The property name.
	/// @return The property value.
	char* CSS(const char* property_name) {
		return getStyleProperty(property_name);
	}

	/// @brief Adds an event listener to the element.
	/// @param eventname A string containing the event name (es. "click").
	/// @param handler An handler.
	void addEventListener(const char* eventname, void(*handler)(HTMLElement&)); 

	/// @brief An associative array to manage the attributes of the element.
	__declspec(property(get = getAttribute, put = setAttribute)) char* attributes[];

	/// @brief An associative array to manage the CSS properties of the element.
	__declspec(property(get = getStyleProperty, put = setStyleProperty)) char* style[];

	/// @brief Says if the element pointer must be destroyed or not when out of scope.
	bool Destroyable = true;

	/// @brief A property that tells if the HTMLElement exists.
	Property<bool> Exists {
		[](void* el) {
			return (int)JavaScript::Eval("%s.querySelector(`%s`)==null?0:1", ((HTMLElement*)el)->docname, ((HTMLElement*)el)->query) != 0;
		}, this
	};

	// The id of the element.
	prop(id);
	// The HTML code contained into the element.
	prop(innerHTML);
	// The HTML code of the element and its content.
	prop(outerHTML);
	// The text contained into the element.
	prop(innerText);
	// The text contained into the element.
	prop(outerText);
	// The text content of the element.
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

	prop(contentEditable);

	// Event fired at click.
	ev_HTMLElement(onclick);
	// Event fired at double click.
	ev_HTMLElement(ondblclick);
	// Event fired when the mouse button is pressed on the element.
	ev_HTMLElement(onmousedown);
	// Event fired when the mouse moves on the element.
	ev_HTMLElement(onmousemove);
	// Event fired when the mouse goes out of the element.
	ev_HTMLElement(onmouseout);
	// Event fired when the mouse goes over the element.
	ev_HTMLElement(onmouseover);
	// Event fired when the mouse is released over the element.
	ev_HTMLElement(onmouseup);
	// Event fired when the mouse scrolls on the element.
	ev_HTMLElement(onmousewheel);
	// Event fired when the mouse wheel is moved on the element.
	ev_HTMLElement(onwheel);
	// Event fired when a key is pressed on the element.
	ev_HTMLElement(onkeydown);
	// Event fired when a key is pressed on the element (DEPRECATED).
	ev_HTMLElement(onkeypress);
	// Event fired when a key is released on the element.
	ev_HTMLElement(onkeyup);

	char* query;
protected:
	char* runFunction(const char* fname, const char* p1, const char* p2 = "null");
	const char* getJSHandler(EventHandler* handler, bool function = false);
	bool inBody;
	char* docname;
	int cindex = 0;
};