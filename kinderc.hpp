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

	#ifndef __INTELLISENSE__
		#define exported __attribute__((visibility("default"))) extern "C"
		#define ev(evname) void set_##evname(EventHandler* e) { setAttribute(#evname, getJSHandler(e)); }; __declspec(property(put = set_##evname)) EventHandler* evname;
		#define ev_HTMLElement(evname) void set_##evname(void(*e)(HTMLElement&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(HTMLElement&);
		#define ev_XMLHttpRequest(evname) void set_##evname(void(*e)(XMLHttpRequest&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(XMLHttpRequest&);
		#define prop(name) char* get_##name() {return getProperty(#name);}; void set_##name(const char* v) {setProperty(#name, v);}; __declspec(property(get = get_##name, put = set_##name)) char* name;
	#else
		// Declares an exported function.
		#define exported extern "C"
		// Macro to add a listener to an event.
		#define ev(evname) void set_##evname(); __declspec(property(put = set_##evname)) EventHandler* evname;
		// Macro to add a listener to an HTMLElement event.
		#define ev_HTMLElement(evname) void(*evname)(HTMLElement&);
		// Macro to add a listener to an XMLHttpRequest event.
		#define ev_XMLHttpRequest(evname) void(*evname)(XMLHttpRequest&);
		// Macro to declare a property with getter and setter.
		#define prop(name) 	void __set(char* val) {}; char* __get() {return 0;}; __declspec(property(get = __get, put = __set)) char* name;
	#endif

#pragma endregion
#pragma region MAIN

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
		/// @code int n = (int)JavaScript::Eval("5 + 10");
		/// @code char* s = JavaScript::Eval("location.href");
		static char* Eval(const char* fmt, ...);

		/// @brief Given a string pointer, returns a JS String reference.
		/// @param str String to reference.
		/// @param len String length. If nothing is specified, the system will automatically calculate it.
		/// @return A string that references the original given string.
		static char* GetStringFromPointer(const char* str, int len = -1);
	};

#pragma endregion
#pragma region DYNAMIC ALLOCATION METHODS

	extern "C" {
		/// <summary>
		/// Gets the current WebAssembly memory size.
		/// </summary>
		/// <returns>The memory size in bytes.</returns>
		unsigned long get_memory_size();
		/// <summary>
		/// Expands the memory of <paramref name="q"/> units.
		/// </summary>
		/// <param name="q">The number of units. One unit is 65536 bytes long.</param>
		void memory_grow(int q);

		void* memset(void* s, int c, unsigned long len);
		void* memcpy(void* dest, const void* src, unsigned long n);

		/// <summary>
		/// Heap pointer.
		/// </summary>
		unsigned char __heap_base;
		/// <summary>
		/// End of stack data pointer.
		/// </summary>
		unsigned char __data_end;
	}

	/// <summary>
	/// Given a <paramref name="size"/>, allocates memory as large as that size and returns a pointer to the allocated memory.
	/// </summary>
	/// <param name="size">The number of bytes to allocate.</param>
	/// <returns>A pointer to the allocated memory.</returns>
	/// <example>
	/// <code>
	/// char* myString = (char*)malloc(25);
	/// strcpy(myString, "Hello World");
	/// </code>
	/// </example>
	exported void* malloc(unsigned long size);
	/// <summary>
	/// Given a heap pointer (<paramref name="ptr"/>), cleans the memory associated.
	/// </summary>
	/// <param name="ptr">The pointer (created using <see cref="malloc(unsigned long)"/>)</param>
	/// <returns></returns>
	exported void free(void* ptr);
#pragma endregion
#pragma region MEMORY CLASS

	class Memory {
	public:
		static void* Allocate(unsigned long size);
		static void Free(void* ptr);
		static void Grow(int blocks);
		static unsigned long GetSize();
	};

#pragma endregion
#pragma region C STRINGS METHODS

	unsigned long strlen(const char* str);
	char* strcat(char* s1, const char* s2);
	void strrev(char* str);
	int strcmp(const char* X, const char* Y);
	char* strcpy(char* destination, const char* source);
	void strcat_c(char* str, char c);
	char* strupr(char* string);
	char* strlwr(char* string);

#pragma endregion
#pragma region STRING CLASS

	class String {
	public:
		static String Format(const char* fmt, ...);

		char* CharArray;

		String(const char* s = "");
		~String();

		void Concat(const char* str);
		void Concat(char c);
		void Copy(const char* str);
		int CompareTo(const char* str);

		String ToUpper();
		String ToLower();

		bool operator == (const char* str);
		void operator = (const char* s);
		operator char* ();
		operator int();
		operator const char* ();
		String operator + (const char* s);
		String operator + (char* s);
		String operator + (String s);
		void operator += (const char* s);
		void operator += (char c);
		char operator[] (int index);
	};

	typedef String string;

#pragma endregion
#pragma region CONSOLE CLASS

	class Console {
	public:
		static void Write(const char* fmt, ...);
		static void Error(const char* error);
		static void Info(const char* info);
	private:
		static void cmd(const char* prefix, const char* txt);
	};

	extern "C" 	char* _eval(const char* code, int len);

#pragma endregion
#pragma region I/O METHODS

	void alert(const char* text);
	bool confirm(const char* text);
	char* prompt(const char* text, const char* defaultResponse = "");
	void print(const char* text, int len);
	void puts(const char* text);
	int atoi(char* str);
	int htoi(const char* c);
	int normalize(double* val);
	char* itoa(int num, char* str, int base);
	void ftoa_fixed(char* buffer, double value);
	void ftoa_sci(char* buffer, double value);
	int printf(const char* fmt, ...);
	int sprintf(char* string, const char* fmt, ...);
	int _sprintf(char* string, const char* fmt, va_list arg);

#pragma endregion
#pragma region EVENTHANDLER CLASS
	class HTMLElement;
	class XMLHttpRequest;

	class Handler {
	public:
		Handler(const char* fnname);
		Handler(void(*handler)(void*));
		Handler(void(*handler)(HTMLElement&));
		Handler(void(*handler)(XMLHttpRequest&));
		string GetWithPointer(void* ptr, bool function = false);
		string HandlerFunctionName;
	private:
		int LambdaIndex;
	};
	typedef Handler EventHandler;

#pragma endregion
#pragma region DYNAMICOBJECT CLASS

	class DynamicObject {
	public:
		DynamicObject();
		DynamicObject(const char* objname, bool forceToString = true);

		DynamicObject operator[] (const char* key);
		DynamicObject operator[] (int key);
		void operator = (const char* value);

		char* operator () ();
		char* operator () (const char* p1, const char* p2, const char* p3);
		char* operator () (const char* p1, const char* p2);
		char* operator () (const char* p1);

		operator char* ();
		operator string();
		operator int();
		operator bool();
	private:
		const char* toString = ".toString()";
		string s;
		char* getValue();
		void setValue(const char* value);
	};
	typedef DynamicObject object;

#pragma endregion
#pragma region JSON CLASS

	class JSON {
	public:
		static DynamicObject Parse(string s);
	};

#pragma endregion
#pragma region URI METHODS

	string encodeURIComponent(const char* decodedURI);
	string decodeURIComponent(const char* encodedURI);

#pragma endregion
#pragma region NETREQUEST CLASS

	class XMLHttpRequest {
	public:
		enum Status { UNSENT, OPENED, HEADERS_RECEIVED, LOADING, DONE };

		XMLHttpRequest();
		XMLHttpRequest(int i);
		~XMLHttpRequest();

		void open(const char* method, const char* url, const bool async = true);
		void send();
		void send(const char* body);
		void setRequestHeader(const char* headername, const char* headervalue);
		string getResponseHeader(const char* headername);

		object JSON();
		string Text();
		void* RAW();

		//#ifndef __INTELLISENSE__
				void* get_response();
				Status get_readyState();
				int get_statusCode();
				int get_loaded();
				int get_total();
				string get_statusText();
		//#endif // __INTELLISENSE__

		ev_XMLHttpRequest(onload);
		ev_XMLHttpRequest(onprogress);
		ev_XMLHttpRequest(onreadystatechange);
		ev_XMLHttpRequest(onerror);

		__declspec(property(get = get_response)) void* response;
		__declspec(property(get = get_readyState)) Status readyState;
		__declspec(property(get = get_statusCode)) int status;
		__declspec(property(get = get_loaded)) int loaded;
		__declspec(property(get = get_total)) int total;
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

	typedef struct s_FetchOptions {
		string Method;
		string Body;
	} FetchOptions;

	const FetchOptions Fetch_defaults = {"GET" , ""};

	class Fetch {
	public:
		Fetch(string _url, FetchOptions _options = Fetch_defaults);
		Fetch then(void(*)(Request&));
		Fetch error(void(*)(Request&));
	private:
		Request r;
	};

	typedef Fetch fetch;

#pragma endregion
#pragma region RAPID CSS SELECTORS ($, $$)

	HTMLElement $(const char* CSS_QUERY);

#pragma endregion
#pragma region HTMLDOCUMENT CLASS
	class HTMLBodyElement;

	class HTMLDocument {
	public:
		HTMLDocument(const char* n);
		HTMLDocument();
		void Append(HTMLElement* element);
		void Append(const char* text);
		void operator << (const HTMLElement* res) {
			Append((HTMLElement*)res);
		}
		void operator << (const char* res) {
			Append(res);
		}
		HTMLElement querySelector(const char* CSS_QUERY);
		HTMLElement getElementById(const char* ID);

		//#ifndef __INTELLISENSE__
				const char* getname() { if ((int)name != -1) return (const char*)name; else return "document"; }
		//#endif

		HTMLBodyElement getbody();
		__declspec(property(get = getname)) const char* Name;
		__declspec(property(get = getbody)) HTMLBodyElement body;
	private:
		char* name;
	};

	HTMLDocument document;

#pragma endregion
#pragma region HTMLELEMENT CLASS

	class HTMLElement
	{
	public:
		HTMLElement(const char* CSS_QUERY, HTMLDocument doc = document);
		HTMLElement(const char* TAGNAME, const char* ID, HTMLDocument doc = document);
		~HTMLElement();
		void Append(const char* text);
		void Append(HTMLElement* element);

		void operator << (const HTMLElement* res) {
			Append((HTMLElement*)res);
		}
		void operator << (const char* res) {
			Append(res);
		}

		void setProperty(const char* key, const char* value);
		char* getProperty(const char* key);
		void setAttribute(const char* key, const char* value);
		char* getAttribute(const char* key);
		void setStyleProperty(const char* key, const char* value);
		char* getStyleProperty(const char* key);
		void addEventListener(const char* eventname, EventHandler* handler);
	#pragma region PROPERTIES 
			__declspec(property(get = getAttribute, put = setAttribute)) char* attributes[];
			__declspec(property(get = getStyleProperty, put = setStyleProperty)) char* style[];
			bool Destroyable = true;
			/// <summary>
			/// Sets or returns the value of the id attribute of an element
			/// </summary>
			/// <returns></returns>
			prop(id);
			prop(innerHTML);
			prop(outerHTML);
			prop(innerText);
			prop(outerText);
			prop(textContent);
			prop(nodeName);
			prop(nodeType);
			prop(nodeValue);
			prop(lang);
			prop(title);
			prop(tagName);
			prop(scrollHeight);
			prop(scrollLeft);
			prop(scrollTop);
			prop(scrollWidth);
			prop(dir);
			prop(className);
			prop(accessKey);

			ev_HTMLElement(onclick);
			ev_HTMLElement(ondblclick);
			ev_HTMLElement(onmousedown);
			ev_HTMLElement(onmousemove);
			ev_HTMLElement(onmouseout);
			ev_HTMLElement(onmouseover);
			ev_HTMLElement(onmouseup);
			ev_HTMLElement(onmousewheel);
			ev_HTMLElement(onwheel);
	#pragma endregion
	protected:
		char* runFunction(const char* fname, const char* p1, const char* p2 = "null");
		const char* getJSHandler(EventHandler* handler, bool function = false);
		char* query;
		bool inBody;
		char* docname;
	};

#pragma endregion
#pragma region HTML MEDIA ELEMENT

	class HTMLMediaElement : public HTMLElement {
	public:
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

#pragma region SOURCE REFERRERS

#include "code/string.cpp"
#include "code/dobject.cpp"
#include "code/json.cpp"
#include "code/handlers.cpp"
#include "code/io.cpp"
#include "code/malloc.cpp"
#include "code/net.cpp"
#include "code/dom.cpp"

#pragma endregion