#pragma once
#include "kinderc.hpp"
#include "string.hpp"
#include "malloc.hpp"
#include "dobject.hpp"
#include "json.hpp"

string encodeURIComponent(const char* decodedURI);
string decodeURIComponent(const char* encodedURI);

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

#include "code/net.cpp"