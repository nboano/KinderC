/*
				   ▄█   ▄█▄  ▄█  ███▄▄▄▄   ████████▄     ▄████████    ▄████████  ▄████████
				  ███ ▄███▀ ███  ███▀▀▀██▄ ███   ▀███   ███    ███   ███    ███ ███    ███
				  ███▐██▀   ███▌ ███   ███ ███    ███   ███    █▀    ███    ███ ███    █▀
				 ▄█████▀    ███▌ ███   ███ ███    ███  ▄███▄▄▄      ▄███▄▄▄▄██▀ ███
				▀▀█████▄    ███▌ ███   ███ ███    ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   ███
				  ███▐██▄   ███  ███   ███ ███    ███   ███    █▄  ▀███████████ ███    █▄
				  ███ ▀███▄ ███  ███   ███ ███   ▄███   ███    ███   ███    ███ ███    ███
				  ███   ▀█▀ █▀    ▀█   █▀  ████████▀    ██████████   ███    ███ ████████▀
				  ▀                                                  ███    ███
										  NICCOLO' BOANO - 2022
*/

#pragma once
#include <stdarg.h>

#pragma region KINDERC MACROS

	// Declares an imported function.
	#define imported extern "C"

	// Declares a variable with automatic typisation.
	#define var auto

	#ifndef __INTELLISENSE__
		#define exported __attribute__((visibility("default"))) extern "C"
		#define ev(evname) void set_##evname(EventHandler* e) { setAttribute(#evname, getJSHandler(e)); }; __declspec(property(put = set_##evname)) EventHandler* evname;
		#define ev_HTMLElement(evname) void set_##evname(void(*e)(HTMLElement&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(HTMLElement&);
		#define ev_XMLHttpRequest(evname) void set_##evname(void(*e)(XMLHttpRequest&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(XMLHttpRequest&);
		#define prop(name) string get_##name() {return getProperty(#name);}; void set_##name(string v) {setProperty(#name, v);}; __declspec(property(get = get_##name, put = set_##name)) string name;
	#else
		// Declares an exported function.
		#define exported extern "C"

		#define ev(evname) EventHandler* evname;

		#define ev_HTMLElement(evname) void(*evname)(HTMLElement&);

		#define ev_XMLHttpRequest(evname) void(*evname)(XMLHttpRequest&);

		#define prop(name) string name;
	#endif

#pragma endregion
#pragma region MAIN

	/// @brief The program entering point.
	/// @return Eventually, a status code.
	int main();

	/// @brief Original main function caller.
	exported int __main() {
		return main();
	}

#pragma endregion
#pragma region JAVASCRIPT CLASS
	/// @brief This class is used to run JavaScript commands.
	class JavaScript {
	public:

		/// @brief Makes the JavaScript interpreter evaluates the code given and returns the result.
		/// @param fmt The code to evaluate, optionally formatted using the sprintf flags.
		/// @param flags [OPTIONAL FORMAT FLAGS]
		/// @return The expression result. If you expect a result type that is not a string, use an explicit cast.
		/// @example int n = (int)JavaScript::Eval("5 + 10");
		/// @example char* s = JavaScript::Eval("location.href");
		static char* Eval(const char* fmt, ...);

		/// @brief Given a string pointer, returns a JS String reference.
		/// @param str String to reference.
		/// @param len String length. If nothing is specified, the system will automatically calculate it.
		/// @return A string that references the original given string.
		static char* GetStringFromPointer(const char* str, int len = -1);
	};

#pragma endregion
#pragma region DYNAMIC ALLOCATION METHODS

	/// @brief Retrieves the current memory size.
	/// @return The memory size, in bytes.
	imported unsigned long get_memory_size();

	/// @brief Expands the memory of q units. One unit is 65536 bytes long.
	/// @param q The number of units
	imported void memory_grow(int q);

	/// @brief Sets all the bytes of a memory area to the same value.
	/// @param s Memory area pointer.
	/// @param c Value to set.
	/// @param len Memory area lenght (in bytes).
	/// @return Memory area pointer.
	imported void* memset(void* s, int c, unsigned long len);

	/// @brief Copies all the bytes of a memory area from one place to another.
	/// @param dest The destination memory area.
	/// @param src The source memory area.
	/// @param n The areas byte lenght.
	/// @return The destination memory area.
	imported void* memcpy(void* dest, const void* src, unsigned long n);

	/// @brief Heap pointer. All the pointers created using malloc point to this area.
	imported unsigned char __heap_base;

	/// @brief End of the stack data pointer.
	imported unsigned char __data_end;

	/// @brief Given a size (in bytes), allocates enough space in the heap memory. This function is accessible from JavaScript.
	/// @param size The allocated block size
	/// @return A pointer to the allocated space.
	/// @exception OutOfMemory
	/// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World");
	exported void* malloc(unsigned long size);

	/// @brief Given a pointer returned by a malloc, clears the data associated.
	/// @param ptr The pointer.
	/// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World"); free(myString);
	exported void free(void* ptr);

#pragma endregion
#pragma region MEMORY CLASS

	/// @brief Class that manages the program memory.
	class Memory {
	public:

		/// @brief Alias for malloc(). Given a size (in bytes), allocates enough space in the heap memory. This function is accessible from JavaScript.
		/// @param size The allocated block size
		/// @return A pointer to the allocated space.
		/// @exception OutOfMemory
		/// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World");
		static void* Allocate(unsigned long size);

		/// @brief Alias for free(). Given a pointer returned by a malloc, clears the data associated.
		/// @param ptr The pointer.
		/// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World"); free(myString);
		static void Free(void* ptr);

		/// @brief Expands the memory of a number of units. One unit is 65536 bytes long.
		/// @param blocks The number of units.
		static void Grow(int blocks);

		/// @brief Retrieves the current memory size.
		/// @return The memory size, in bytes.
		static unsigned long GetSize();

	};

#pragma endregion
#pragma region C STRINGS METHODS

	/// @brief Calculates the length of a given string.
	/// @param str The string.
	/// @return The number of characters of the string.
	unsigned long strlen(const char* str);

	/// @brief Appends the content of s2 into s1. Make sure that s1 is long enough.
	/// @param s1 The destination string.
	/// @param s2 The string to concatenate.
	/// @return A pointer to the destination string.
	char* strcat(char* s1, const char* s2);

	/// @brief Reverses a given string.
	/// @param str The string.
	void strrev(char* str);

	/// @brief Compares two strings.
	/// @param X The first string.
	/// @param Y The second string.
	/// @return A negative integer if X < Y.
	/// @return Zero if the two strings are equal.
	/// @return A positive integer if X > Y.
	int strcmp(const char* X, const char* Y);

	/// @brief Copies a source string into a destination. Make sure that the souce is long enough.
	/// @param destination The destination string.
	/// @param source The source string.
	/// @return A pointer to the destination string.
	char* strcpy(char* destination, const char* source);

	/// @brief Concatenates a single character to a string.
	/// @param str The string.
	/// @param c The character to concatenate.
	void strcat_c(char* str, char c);

	/// @brief Upperizes a string.
	/// @param string The string.
	/// @return A pointer to the string.
	char* strupr(char* string);

	/// @brief Lowerizes a string.
	/// @param string The string.
	/// @return A pointer to the string.
	char* strlwr(char* string);

#pragma endregion
#pragma region STRING CLASS

	/// @brief Use this class to manage strings.
	class String {
	public:

		/// @brief Creates a formatted string.
		/// @param fmt The base string. Use %s to indicate a string, %i for an integer, %d for a double, %c for a char...
		/// @param [FLAGS] Optional printf-like parameters.
		/// @return A formatted string.
		static String Format(const char* fmt, ...);

		/// @brief A pointer to the raw string characters. Use it only if you know how.
		char* CharArray;

		/// @brief Creates a string object from a char array, or string literal.
		/// @param s A char array, or a string literal.
		String(const char* s = "");

		/// @brief Destroys a string, deallocating the memory associated.
		~String();

		/// @brief Concatenates a string literal to the string. The string is automatically resized if needed.
		/// @param str A string literal, a char array or a string.
		void Concat(const char* str);

		/// @brief Concatenates a character to the string.
		/// @param c A char.
		void Concat(char c);

		/// @brief Copies the content of a string literal into a string. The string is automatically resized if needed.
		/// @param str A string literal, a char array or a string.
		void Copy(const char* str);

		/// @brief Compares the string to another string literal.
		/// @param str A string literal, a char array or a string.
		/// @return A negative integer if the string is minor.
		/// @return Zero if the two strings are equal.
		/// @return A positive integer if the string is major.
		int CompareTo(const char* str);

		/// @brief Gets the string length. Use the property instead.
		/// @return The string length.
		unsigned long GetLength();

		/// @brief Creates a new upperized string.
		/// @return Upperized string.
		String ToUpper();

		/// @brief Creates a new lowerized string.
		/// @return Lowerized string.
		String ToLower();

		/// @brief Check if two string are equal.
		/// @param str A string literal, a char array or a string.
		/// @return true if the strings are equal,
		/// @return false otherwise.
		bool operator==(const char* str);

		bool operator!=(const char* str);

		/// @brief Copies another string into this one.
		/// @param s A string literal, a char array or a string.
		void operator = (const char* s);
		void operator = (String s);

		/// @brief Converts a string into a char array.
		operator char* ();

		/// @brief Converts a string into an integet.
		operator int();

		/// @brief Converts a string into a literal.
		operator const char* ();

		/// @brief Concatenates two strings.
		/// @param s A string literal.
		/// @return A new string.
		String operator + (const char* s);

		/// @brief Concatenates two strings.
		/// @param s A char array.
		/// @return A new string.
		String operator + (char* s);

		/// @brief Concatenates two strings.
		/// @param s A string.
		/// @return A new string. 
		String operator + (String s);

		/// @brief Appends a string literal, a char array or another string at the end of this string.
		/// @param s A string literal, a char array or a string.
		void operator += (const char* s);

		/// @brief Appends a character to the string.
		/// @param c A char.
		void operator += (char c);

		/// @brief Returns the character of a given index.
		/// @param index The index.
		/// @return The corresponding character.
		char operator[] (int index);

		/// @brief Gets the Length of the string.
		__declspec(property(get = GetLength)) unsigned long Length;
	};

	// Represents a string allocated in the heap memory.
	#define string String

#pragma endregion
#pragma region EXCEPTION HANDLING

class Exception {
	public:

	/// @brief Creates a new Exception object.
	/// @param message The exception message.
	Exception(string message);

	/// @brief Returns the exception message.
	/// @return The exception message.
	string what();

	protected:
	string msg;
};

extern "C" void __cxa_throw(void* ptr, void*, void(*)(void*));

extern "C" void* __cxa_allocate_exception(unsigned long thrown_size);

extern "C" void __cxa_free_exception(void* ptr);

#pragma endregion
#pragma region CONSOLE CLASS

	/// @brief Use this class to write in the browser console.
	class Console {
	public:

		/// @brief Writes in the browser console
		/// @param fmt A string. You can use printf-like flags, too.
		/// @param [FORMAT PARAMS] Optional params.
		static void Write(const char* fmt, ...);

		/// @brief Writes a red error message in the console.
		/// @param error An error message.
		static void Error(const char* error);

		/// @brief Writes an information in the console.
		/// @param info A message.
		static void Info(const char* info);
	private:
		static void cmd(const char* prefix, const char* txt);
	};

	/// @brief Call to the JavaScript interpreter.
	imported char* _eval(const char* code, int len);

#pragma endregion
#pragma region I/O METHODS

	/// @brief Displays an alert message. The code is blocked until the user clicks OK.
	/// @param text The message text.
	void alert(const char* text);

	/// @brief Asks the user for a confirm (Yes / No, OK / Cancel). The code is blocked until the user closes the confirm box.
	/// @param text The message text.
	/// @return true if the user answered yes, false otherwise.
	bool confirm(const char* text);

	/// @brief Asks the user for a text input. The code is blocked until the user closes the input box.
	/// @param text The message text.
	/// @param defaultResponse A default response.
	/// @return The response gave by the user.
	char* prompt(const char* text, const char* defaultResponse = "");

	/// @brief Prints a string to the webpage.
	/// @param text The string to print.
	/// @param len The string length.
	void print(const char* text, int len);

	/// @brief Prints a string to the webpage.
	/// @param text The string to print.
	void puts(const char* text);

	/// @brief Converts a string into an integer (Base 10). NOTE: If the string is not an integer, an undefined behaviour will occur.
	/// @param str The string to convert (Base 10).
	/// @return The integer result.
	int atoi(char* str);

	/// @brief Converts a string into an integer (Base 16). NOTE: If the string is not an integer, an undefined behaviour will occur.
	/// @param c The string to convert (Base 16).
	/// @return The integer result.
	int htoi(const char* c);

	/// @brief Converts an integer into a string of a given base.
	/// @param num The number to convert.
	/// @param str The string buffer. Make sure that is long enough.
	/// @param base The number base.
	/// @return A pointer to the string buffer.
	char* itoa(int num, char* str, int base);

	/// @brief Writes a formatted string into the webpage.
	/// @param fmt The base string. You can use flags like %s, %i, %d, %c...
	/// @param [P] Optional formatter params.
	/// @return The written string length.
	int printf(const char* fmt, ...);

	/// @brief Writes a formatted string into another string.
	/// @param string The string buffer. Make sure that is long enough.
	/// @param fmt The base string. You can use flags like %s, %i, %d, %c...
	/// @param [P] Optional formatter params.
	/// @return The string length.
	int sprintf(char* string, const char* fmt, ...);

	/// @brief Custom sprintf with variable list arguments.
	/// @param string The string buffer.
	/// @param fmt The base string.
	/// @param arg Argument list <stdarg.h>.
	/// @return The string length.
	int _sprintf(char* string, const char* fmt, va_list arg);

#pragma endregion
#pragma region EVENTHANDLER CLASS
	class HTMLElement;
	class HTMLElementCollection;
	class XMLHttpRequest;

	/// @brief Use this class to handle events and so on.
	class Handler {
	public:

		/// @brief Creates an handler given a JS or exported function name.
		/// @param fnname The function name, as a string literal.
		Handler(const char* fnname);

		/// @brief Creates an handler given a generic function pointer.
		/// @param handler The handler.
		Handler(void(*handler)(void*));

		/// @brief Creates an handler for an HTMLElement event.
		/// @param handler The handler.
		Handler(void(*handler)(HTMLElement&));

		/// @brief Creates an handler for an XMLHttpRequest header.
		/// @param handler The handler.
		Handler(void(*handler)(XMLHttpRequest&));

		/// @brief Gets the JavaScript code that calls the handler, passing a pointer.
		/// @param ptr The pointer to pass as parameter.
		/// @param function Specifies if you want a function [ ()=>...() ] or not [ ...() ]
		/// @return A JavaScript code.
		string GetWithPointer(void* ptr, bool function = false);

		/// @brief The handler function name.
		string HandlerFunctionName;
	private:
		int LambdaIndex;
	};

	typedef Handler EventHandler;

#pragma endregion
#pragma region DYNAMICOBJECT CLASS

	/// @brief This class handles JavaScript objects.
	class DynamicObject {
	public:

		/// @brief Creates a new, empty object.
		DynamicObject();

		/// @brief Points to an existing object.
		/// @param objname The object name.
		DynamicObject(const char* objname);

		/// @brief Accesses a field of the object.
		/// @param key The field name.
		/// @return Another object pointing to the field.
		DynamicObject operator[] (const char* key);

		/// @brief Accesses an array element.
		/// @param key The element index.
		/// @return Another object pointing to the array element.
		DynamicObject operator[] (int key);

		/// @brief Sets the object value to a string literal.
		/// @param value A string literal, a char array, or a string.
		void operator = (const char* value);

		/// @brief Calls the object as a function.
		/// @return The response. If it's not a string, use an explicit cast.
		char* operator () ();

		/// @brief Calls the object as a function.
		/// @return The response. If it's not a string, use an explicit cast.
		char* operator () (const char* p1, const char* p2, const char* p3);

		/// @brief Calls the object as a function.
		/// @return The response. If it's not a string, use an explicit cast.
		char* operator () (const char* p1, const char* p2);

		/// @brief Calls the object as a function.
		/// @return The response. If it's not a string, use an explicit cast.
		char* operator () (const char* p1);

		/// @brief Converts the object to a char array.
		operator char* ();

		/// @brief Converts the object to a string.
		operator string();

		/// @brief Convert the object to an integer.
		operator int();

		/// @brief Converts the object to a boolean.
		operator bool();
	protected:
		const char* toString = ".toString()";
		string s;
		char* getValue();
		void setValue(const char* value);
		void setProperty(string name, string value) {operator[]((char*)name) = value;}
		string getProperty(string name) {return operator[]((char*)name);}
	};
	
	// Represents a JavaScript object.
	#define object DynamicObject

#pragma endregion
#pragma region JSON CLASS

	/// @brief Use this class to handle JSON strings.
	class JSON {
	public:

		/// @brief Parses a JSON string into an object.
		/// @param s A valid JSON string.
		/// @return An object pointer.
		/// @exception JSONNotValid
		static object Parse(string s);
	};

#pragma endregion
#pragma region URI METHODS

	/// @brief Given a clear URI, encodes it.
	/// @param decodedURI A clear URI.
	/// @return An encoded URI.
	string encodeURIComponent(const char* decodedURI);

	/// @brief Given an encoded URI, decodes it.
	/// @param encodedURI An encoded URI.
	/// @return A clear URI.
	string decodeURIComponent(const char* encodedURI);

#pragma endregion
#pragma region NETREQUEST CLASS

	/// @brief Use this class to handle Network Requests
	class XMLHttpRequest {
	public:

		/// @brief Enumeration that represents the XHR different status.
		enum Status {
			// The request has not yet been opened nor sent. 
			UNSENT,
			// The request has been opened. 
			OPENED, 
			// The response headers are received and visible.
			HEADERS_RECEIVED, 
			// The request is loading body data.
			LOADING, 
			// The request has completed successfully.
			DONE 
		};

		/// @brief Creates a new request.
		XMLHttpRequest();

		XMLHttpRequest(int i);

		/// @brief Destroys a request.
		~XMLHttpRequest();

		/// @brief Opens the communication channel.
		/// @param method A string literal containing the method (GET, POST, ...).
		/// @param url A string literal containing the URL to connect to.
		/// @param async A boolean. If it's true, the request will be async, otherwise it will be sync. In the second case the main thread will be blocked until the request finishes. 
		void open(const char* method, const char* url, const bool async = true);
		
		/// @brief Sends the request.
		void send();

		/// @brief Sends the request with a body (not available in GET).
		/// @param body The body text.
		void send(const char* body);

		/// @brief Sets an header of the request.
		/// @param headername The header key name.
		/// @param headervalue The header value.
		void setRequestHeader(const char* headername, const char* headervalue);

		/// @brief Retreives a response header value.
		/// @param headername The response header name.
		/// @return The value, if available.
		string getResponseHeader(const char* headername);

		/// @brief Parses the response into an object, if possible.
		/// @return An object pointer.
		object JSON();

		/// @brief Gets the response text.
		/// @return A string containing the response text.
		string Text();

		/// @brief Gets the raw response.
		/// @return A generic pointer to the response.
		void* RAW();

		/// @deprecated Use the response property instead.
		void* get_response();
		/// @deprecated Use the readyState property instead.
		Status get_readyState();
		/// @deprecated Use the status property instead.
		int get_statusCode();
		/// @deprecated Use the loaded property instead.
		int get_loaded();
		/// @deprecated Use the total property instead.
		int get_total();
		/// @deprecated Use the statusText property instead.
		string get_statusText();

		// This event is triggered at the end of the request.
		ev_XMLHttpRequest(onload);

		// This event is triggered regularly when the data arrives.
		ev_XMLHttpRequest(onprogress);

		// This event is triggered when the readyState changes.
		ev_XMLHttpRequest(onreadystatechange);

		// This event is triggered in case of a network error
		ev_XMLHttpRequest(onerror);

		/// @brief Raw response pointer.
		__declspec(property(get = get_response)) void* response;

		/// @brief The ready state of the request.
		__declspec(property(get = get_readyState)) Status readyState;

		/// @brief The HTTP status code (es. 200)
		__declspec(property(get = get_statusCode)) int status;

		/// @brief The number of bytes loaded.
		__declspec(property(get = get_loaded)) int loaded;

		/// @brief The total number of bytes incoming.
		__declspec(property(get = get_total)) int total;

		/// @brief The HTTP status text (es. OK)
		__declspec(property(get = get_statusText)) string statusText;

	private:
		int index;
		string getJSHandler(EventHandler* h);
		void setAttribute(const char* name, const char* value);
		string getAttribute(const char* name);
	};

	typedef XMLHttpRequest Request;
	typedef XMLHttpRequest NetRequest;

#pragma endregion
#pragma region FETCH

	/// @brief This struct incapsulates all the possible fetch options.
	typedef struct s_FetchOptions {

		/// @brief The request method (GET, POST, ...)
		string Method;

		/// @brief The request body (not available in GET)
		string Body;

		string Headers[16][2];

	} FetchOptions;

	/// @brief Default fetch options (GET request with empty body)
	const FetchOptions Fetch_defaults = {"GET" , ""};

	/// @brief Use the fetch API to perform async network requests.
	class Fetch {
	public:

		/// @brief Makes a network request.
		/// @param _url The request URL.
		/// @param _options The request options. Defaults to GET with empty body.
		Fetch(string _url, FetchOptions _options = Fetch_defaults);

		/// @brief Specifies an handler for when the request has completed.
		/// @param handler The handler.
		Fetch then(void(*)(Request&));

		/// @brief Specifies an handler for when a network error occurs
		/// @param handler The handler.
		Fetch error(void(*)(Request&));

	private:
		Request r;
	};

	typedef Fetch fetch;

#pragma endregion
#pragma region RAPID CSS SELECTORS ($, $$)

	/// @brief Given a CSS query, returns the first HTMLElement that matches it.
	/// @param CSS_QUERY A valid CSS query.
	/// @return A corresponding HTMLElement.
	HTMLElement $(const char* CSS_QUERY);

	/// @brief Given a CSS query, returns a collection of elements that match it.
	/// @param CSS_QUERY A valid CSS query.
	/// @return An element collection.
	HTMLElementCollection $$(const char* CSS_QUERY);

#pragma endregion
#pragma region HTMLDOCUMENT CLASS

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

#pragma endregion
#pragma region HTMLELEMENT CLASS

	/// @brief Use this class to manage DOM elements.
	class HTMLElement
	{
	public:

		/// @brief Given a CSS query, performs a search and makes the object point to the first mathing element.
		/// @param CSS_QUERY A CSS query, as a string literal.
		/// @param doc The document where the element is contained. Defaults to the current document.
		HTMLElement(const char* CSS_QUERY, HTMLDocument doc = document);

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

		/// @brief Sets a CSS property of the element.
		/// @param key The property name.
		/// @param value The property value.
		void setStyleProperty(const char* key, const char* value);

		/// @brief Gets a CSS property of the element.
		/// @param key The property name.
		/// @return The property value.
		char* getStyleProperty(const char* key);

		/// @brief Adds an event listener to the element.
		/// @param eventname A string containing the event name (es. "click").
		/// @param handler An handler.
		void addEventListener(const char* eventname, void(*handler)(HTMLElement&));

	#pragma region PROPERTIES 

			/// @brief An associative array to manage the attributes of the element.
			__declspec(property(get = getAttribute, put = setAttribute)) char* attributes[];

			/// @brief An associative array to manage the CSS properties of the element.
			__declspec(property(get = getStyleProperty, put = setStyleProperty)) char* style[];

			/// @brief Says if the element pointer must be destroyed or not when out of scope.
			bool Destroyable = true;

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

			prop(contenteditable);

			/// Event fired at click.
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
	#pragma endregion
			char* query;
	protected:
		char* runFunction(const char* fname, const char* p1, const char* p2 = "null");
		const char* getJSHandler(EventHandler* handler, bool function = false);
		bool inBody;
		char* docname;
	};

#pragma endregion
#pragma region HTMLELEMENTCOLLECTION CLASS

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

			#pragma endregion
		private:
			#ifdef __INTELLISENSE__
			int get_length();
			#endif

			HTMLElement* collectionptr;
			int len;
	};

#pragma endregion
#pragma region HTML CONTROLS

	class HTMLButtonElement : public HTMLElement {
	public:
		HTMLButtonElement(HTMLElement el) : HTMLElement(el.query) {}

		void click();

		prop(type);
		prop(disabled);
	};

	class HTMLInputElement : public HTMLElement {
	public:
		HTMLInputElement(HTMLElement el) : HTMLElement(el.query) {}

		prop(type);
		prop(disabled);
		prop(value);
		prop(name);

		ev_HTMLElement(onchange);
		ev_HTMLElement(oninput);
		ev_HTMLElement(oninvalid);
		ev_HTMLElement(onsearch);
		ev_HTMLElement(onselectionchange);
	};


	typedef HTMLButtonElement Button;

	typedef HTMLInputElement TextBox;
	typedef HTMLInputElement RadioButton;
	typedef HTMLInputElement CheckBox;
	typedef HTMLInputElement FilePicker;

#pragma endregion
#pragma region HTML DIALOG

	class HTMLDialogElement : public HTMLElement {
		public:
		HTMLDialogElement(HTMLElement el) : HTMLElement(el.query) {}

		prop(returnValue);

		void Show();
		void ShowModal();
		void Close();

		ev_HTMLElement(oncancel);
		ev_HTMLElement(onclose);
	};

	typedef HTMLDialogElement Dialog;

#pragma endregion
#pragma region HTML MEDIA ELEMENTS

	class HTMLMediaElement : public HTMLElement {
	public:
		HTMLMediaElement(HTMLElement el) : HTMLElement(el.query) {}

		prop(src);

		ev(onabort);
		ev(oncanplay);
		ev(oncanplaythrough);
		ev(oncuechange);
		ev(ondurationchange);
		ev(onemptied);
		ev(onended);
		ev(onerror);
		ev(onloadeddata);
		ev(onloadedmetadata);
		ev(onloadstart);
		ev(onpause);
		ev(onplay);
		ev(onplaying);
		ev(onprogress);
		ev(onratechange);
		ev(onseeked);
		ev(onseeking);
		ev(onstalled);
		ev(onsuspend);
		ev(ontimeupdate);
		ev(onvolumechange);
		ev(onwaiting);

		void pause();
		void play();
		void load();
	};

#pragma endregion
#pragma region HTML BODY

	class HTMLBodyElement : public HTMLElement {
	public:
		HTMLBodyElement(HTMLDocument doc) : HTMLElement("body", doc) {

		}
		ev(onafterprint);
		ev(onbeforeprint);
		ev(onbeforeunload);
		ev(onerror);
		ev(onhashchange);
		ev(onload);
		ev(onmessage);
		ev(onoffline);
		ev(ononline);
		ev(onpagehide);
		ev(onpageshow);
		ev(onpopstate);
		ev(onresize);
		ev(onstorage);
		ev(onunload);
	};

#pragma endregion
#pragma region BOM OBJECTS

	class Location : public object {
	public:
		Location() : object("location") {}

		prop(hash);
		prop(host);
		prop(hostname);
		prop(href);
		prop(origin);
		prop(pathname);
		prop(port);
		prop(protocol);
		prop(search);

		void reload() {operator[]("reload")();}
	};

	class History : public object {
	public:
		History() : object("history") {}

		#ifndef __INTELLISENSE__
		int get_length() { return (int)operator[]("length");}
		__declspec(property(get=get_length)) int length;
		#else
		int length;
		#endif

		void back() {operator[]("back")();}
		void forward() {operator[]("forward");}
	private:
		#ifdef __INTELLISENSE__
		int get_length();
		#endif
	};

	class Navigator : public object {
	public:
		Navigator() : object("navigator") {}
		prop(appCodeName);
		prop(appName);
		prop(appVersion);
		prop(language);
		prop(platform);
		prop(product);
		prop(productSub);
		prop(userAgent);
		prop(vendor);
		prop(vendorSub);
	};

	class Window : public object {
	public:
		Window() : object("window") {}
		
		HTMLDocument document;
		Location location;
		History history;
		Navigator navigator;
	};

	Window window;
	Location location;
	History history;
	Navigator navigator;

#pragma endregion
#pragma region LOCALSTORAGE, SESSIONSTORAGE

	/// @brief Handles the localStorage and the sessionStorage objects.
	class Storage {
		public:
			Storage(bool isLocalStorage);

			/// @brief Sets an item into the storage.
			/// @param key The item key.
			/// @param value The item value.
			void setItem(string key, string value);

			/// @brief Retrieves an item from the storage.
			/// @param key The item key.
			/// @return The item value.
			string getItem(string key);

			/// @brief Removes an item from the storage.
			/// @param key The item key.
			void removeItem(string key);

			/// @brief Clears the storage.
			void clear();

			#ifndef __INTELLISENSE__
			int get_length();
			__declspec(property(get = get_length)) int length;
			#else
			/// @brief Gets the number of elements into the storage.
			int length;
			#endif
		private:
			#ifdef __INTELLISENSE__
			int get_length();
			#endif
			bool ls;
	};

	/// @brief Local Storage API, to store key/value pairs.
	Storage localStorage(true);

	/// @brief Session Storage API, to store key/value pairs.
	Storage sessionStorage(false);

#pragma endregion
#pragma region DATE & TIME

	/// @brief Returns the current UNIX timestamp.
	/// @return The timestamp in seconds.
	unsigned long long time();

	/// @brief Waits for a certain number of milliseconds, and then calls the handler.
	/// @param handler The timeout handler.
	/// @param milliseconds The number of milliseconds to wait.
	/// @return The timeout identifier.
	int setTimeout(void(*handler)(void*), int milliseconds);

	/// @brief Calls the handler every N milliseconds.
	/// @param handler The handler.
	/// @param milliseconds The number of milliseconds.
	/// @return The interval identifier.
	int setInterval(void(*handler)(void*), int milliseconds);

	/// @brief Deletes a given timeout.
	/// @param timeoutID The timeout identifier.
	void clearTimeout(int timeoutID);

	/// @brief Deletes a given interval.
	/// @param intervalID The interval identifier.
	void clearInterval(int intervalID);

#pragma endregion
#pragma region PROPERTIES MACROS

#ifndef __INTELLISENSE__
#define property(PROPERTY_NAME, TYPE, GETSET) GETSET __declspec(property(get = get_##PROPERTY_NAME, put = set_##PROPERTY_NAME)) TYPE PROPERTY_NAME;
#else
#define property(PROPERTY_NAME, TYPE, GETSET) TYPE PROPERTY_NAME;
#define value value
#endif
#define get(PROPERTY_NAME, TYPE) TYPE get_##PROPERTY_NAME()
#define set(PROPERTY_NAME, TYPE) void set_##PROPERTY_NAME(TYPE value)

#pragma endregion
#pragma region SOURCE REFERRERS

#include "code/string.cpp"
#include "code/dobject.cpp"
#include "code/json.cpp"
#include "code/handlers.cpp"
#include "code/io.cpp"
#include "code/malloc.cpp"
#include "code/net.cpp"
#include "code/dom.cpp"
#include "code/storage.cpp"
#include "code/datetime.cpp"
#include "code/exceptions.cpp"

#pragma endregion