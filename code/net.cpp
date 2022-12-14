#pragma once
#include "../kinderc.hpp"

string encodeURIComponent(const char* decodedURI)
{
	string encodedURI = "";
	const char* hex = "0123456789ABCDEF";

	for (int i = 0; i < strlen(decodedURI); i++) {
		if (('a' <= decodedURI[i] && decodedURI[i] <= 'z')
			|| ('A' <= decodedURI[i] && decodedURI[i] <= 'Z')
			|| ('0' <= decodedURI[i] && decodedURI[i] <= '9')) {
			encodedURI += decodedURI[i];
		}
		else {
			encodedURI += '%';
			encodedURI += (char)(hex[decodedURI[i] >> 4]);
			encodedURI += (char)(hex[decodedURI[i] & 15]);
		}
	}
	return encodedURI;
}
string decodeURIComponent(const char* encodedURI) {
	string decodedURI = "";
	for (int i = 0; i < strlen(encodedURI); i++)
	{
		if (encodedURI[i] != '%')
			decodedURI += encodedURI[i];
		else {
			char nhex[2] = "";
			i++;
			strcat_c(nhex, encodedURI[i]);
			i++;
			strcat_c(nhex, encodedURI[i]);
			decodedURI += (char)htoi(nhex);
		}
	}
	return decodedURI;
}
XMLHttpRequest::XMLHttpRequest() {
	object dp("dp");
	index = (int)dp["push"]("new XMLHttpRequest()") - 1;
}
XMLHttpRequest::XMLHttpRequest(int i) {
	index = i;
}
XMLHttpRequest::~XMLHttpRequest() {

}
void XMLHttpRequest::open(const char* method, const char* url, const bool async) {
	object("dp")[index]["open"](String::Format("`%s`", method).ToUpper(), String::Format("`%s`", url), async ? "true" : "false");
}
void XMLHttpRequest::send() {
	object("dp")[index]["send"]();
}
void XMLHttpRequest::send(const char* body) {
	string fmt = String::Format("`%s`", body);
	object("dp")[index]["send"](fmt);
}
void XMLHttpRequest::setRequestHeader(const char* headername, const char* headervalue) {
	object("dp")[index]["setRequestHeader"](string::Format("`%s`", headername), string::Format("`%s`", headervalue));
}
string XMLHttpRequest::getResponseHeader(const char* headername) {
	object dp("dp");
	char bf[strlen(headername) + 2];
	sprintf(bf, "`%s`", headername);
	return string(dp[index]["getResponseHeader"](bf));
}
#ifndef __INTELLISENSE__
void* XMLHttpRequest::get_response() {
	return JavaScript::Eval("dp[%i].responseText", index);
}
XMLHttpRequest::Status XMLHttpRequest::get_readyState() {
	object dp("dp");
	return (Status)(int)dp[index]["readyState"];
}
int XMLHttpRequest::get_statusCode() {
	return object("dp")[index]["status"];
}
int XMLHttpRequest::get_loaded() {
	return object("dp")[index]["loaded"];
}
int XMLHttpRequest::get_total() {
	return object("dp")[index]["total"];
}
string XMLHttpRequest::get_statusText() {
	return object("dp")[index]["statusText"];
}
#endif
string XMLHttpRequest::getAttribute(const char* name) {
	return object("dp")[index][name];
}
object XMLHttpRequest::JSON() {
	return JSON::Parse((char*)response);
}
string XMLHttpRequest::Text() {
	return String((char*)response);
}
void* XMLHttpRequest::RAW() {
	return response;
}
void XMLHttpRequest::setAttribute(const char* name, const char* value) {
	object("dp")[index][name] = value;
}
string XMLHttpRequest::getJSHandler(EventHandler* h) {
	XMLHttpRequest r(index);
	XMLHttpRequest* sender = (XMLHttpRequest*)malloc(sizeof(XMLHttpRequest));
	*sender = r;
	return h->GetWithPointer(sender, true);
}
Fetch::Fetch(string URL, FetchOptions options) {
	r.open(options.Method, URL, true);

	for(int i = 0; i < 16; i++) {
		if(options.Headers[i][0] == "") break;
		r.setRequestHeader(options.Headers[i][0], options.Headers[i][1]);
	}

	r.send(options.Body);
}
Fetch Fetch::then(void(*handler)(Response&)) {
	r.onload = (void(*)(XMLHttpRequest&))handler;
	return *this;
}
Fetch Fetch::error(void(*handler)(Response&)) {
	r.onerror = (void(*)(XMLHttpRequest&))handler;
	return *this;
}
Response Fetch::sync(string URL, FetchOptions options) {
    Response r;
    r.open(options.Method, URL, false);
    for(int i = 0; i < 16; i++) {
        if(options.Headers[i][0] == "") break;
        r.setRequestHeader(options.Headers[i][0], options.Headers[i][1]);
    }
    r.send(options.Body);
    return r;
}  