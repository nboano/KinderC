#pragma once

#ifndef __INTELLISENSE__
#define exported __attribute__((visibility("default"))) extern "C"
#else 
#define exported {}
#endif
#define GET_VARIABLE_NAME(Variable) (#Variable)

int main();
exported int __main() {
	return main();
}

#include <stdarg.h>

class JavaScript {
public:
	static char* Eval(const char* fmt, ...);
	static char* GetStringFromPointer(const char* str, int len = -1);
};

#include "io.hpp"

//#define EventHandler(fn) EventHandler(#fn)
class HTMLElement;
class XMLHttpRequest;
class Handler;

#ifndef __INTELLISENSE__
#define ev(evname) void set_##evname(EventHandler* e) { setAttribute(#evname, getJSHandler(e)); }; __declspec(property(put = set_##evname)) EventHandler* evname;

#define ev_HTMLElement(evname) void set_##evname(void(*e)(HTMLElement&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(HTMLElement&);
#define ev_XMLHttpRequest(evname) void set_##evname(void(*e)(XMLHttpRequest&)) { setAttribute(#evname, getJSHandler(new EventHandler(e))); }; __declspec(property(put = set_##evname)) void(*evname)(XMLHttpRequest&);

#define prop(name) char* get_##name() {return getProperty(#name);}; void set_##name(const char* v) {setProperty(#name, v);}; __declspec(property(get = get_##name, put = set_##name)) char* name;
#else
#define ev(evname) __declspec(property(put = set_##evname)) EventHandler* evname;

#define ev_HTMLElement(evname) void(*evname)(HTMLElement*);
#define ev_XMLHttpRequest(evname) void(*evname)(XMLHttpRequest&);

#define prop(name) __declspec(property(get = get_##name, put = set_##name)) char* name;
#endif

#define LAMBDA_MAX_LEN 128
static void(*__lambda_list[LAMBDA_MAX_LEN])(void*);

int __lambda_add(void(*lb)(void*)) {
	static int ctr = -1;
	ctr++;
	if (ctr == LAMBDA_MAX_LEN) ctr = 0;
	__lambda_list[ctr] = lb;
	return ctr;
}

exported void __lambda_call(int index, void* param = 0) {
	__lambda_list[index](param);
}

class Handler {
public:
	Handler(const char* fnname) {
		HandlerFunctionName = fnname;
		LambdaIndex = -1;
	}
	Handler(void(*handler)(void*)) {
		LambdaIndex = __lambda_add(handler);
	}
	Handler(void(*handler)(HTMLElement&)) {
		LambdaIndex = __lambda_add((void(*)(void*))handler);
	}
	Handler(void(*handler)(XMLHttpRequest&)) {
		LambdaIndex = __lambda_add((void(*)(void*))handler);
	}
	string GetWithPointer(void* ptr, bool function = false) {
		if (LambdaIndex < 0)
			return String::Format(function ? "()=>%s(%i)" : "%s(%i)", HandlerFunctionName.CharArray, (int)ptr);
		else return String::Format(function ? "()=>__lambda_call(%i,%i)" : "__lambda_call(%i,%i)", LambdaIndex, ptr);
	}
	string HandlerFunctionName;
private:
	int LambdaIndex;
};
typedef Handler EventHandler;

#include "net.hpp"
#include "dom.cpp"