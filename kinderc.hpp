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
		#define exported {}
		#define ev(evname) __declspec(property(put = set_##evname)) EventHandler* evname;
		#define ev_HTMLElement(evname) void(*evname)(HTMLElement*);
		#define ev_XMLHttpRequest(evname) void(*evname)(XMLHttpRequest&);
		#define prop(name) __declspec(property(get = get_##name, put = set_##name)) char* name;
	#endif

#pragma endregion
#pragma region MAIN

	int main();
	exported int __main() {
		return main();
	}

#pragma endregion
#pragma region JAVASCRIPT CLASS

	class JavaScript {
	public:
		static char* Eval(const char* fmt, ...);
		static char* GetStringFromPointer(const char* str, int len = -1);
	};

#pragma endregion
#pragma region DYNAMIC ALLOCATION METHODS

	extern "C" {
		unsigned long get_memory_size();
		void memory_grow(int q);

		void* memset(void* s, int c, unsigned long len);
		void* memcpy(void* dest, const void* src, unsigned long n);

		unsigned char __heap_base;
		unsigned char __data_end;
	}

	exported void* malloc(unsigned long size);
	exported void free(void* ptr);

	unsigned long memlen(char* pt);

	void* getpos(unsigned long start, unsigned long size);
	unsigned long checkmem(unsigned long start, unsigned long size);
	int isendofmem(char* pt, int n);

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

		#ifndef __INTELLISENSE__
				void* get_response();
				Status get_readyState();
				int get_statusCode();
				int get_loaded();
				int get_total();
				string get_statusText();
		#endif // __INTELLISENSE__

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

	const FetchOptions Fetch_defaults = {
		.Method = "GET",
		.Body = "",
	};

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

#include "dom.cpp"

#pragma region SOURCE REFERRERS

#include "code/dobject.cpp"
#include "code/handlers.cpp"
#include "code/io.cpp"
#include "code/malloc.cpp"

#pragma endregion