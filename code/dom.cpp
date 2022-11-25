#pragma once
#include "../kinderc.hpp"

HTMLDocument::HTMLDocument(const char* n) {
	name = (char*)malloc(strlen(n));
	strcpy(name, n);
}
HTMLDocument::HTMLDocument() {
	name = (char*)-1;
}

HTMLElement::HTMLElement(const char* CSS_QUERY, HTMLDocument doc) {
	docname = (char*)malloc(strlen(doc.Name));
	strcpy(docname, doc.Name);
	query = (char*)malloc(strlen(CSS_QUERY));
	strcpy(query, CSS_QUERY);
	inBody = true;
}
HTMLElement::HTMLElement(const char* TAGNAME, const char* ID, HTMLDocument doc) {
	docname = (char*)malloc(strlen(doc.Name));
	strcpy(docname, doc.Name);
	inBody = false;
	query = (char*)malloc(strlen(ID) + 2);
	strcpy(query, "");
	sprintf(query, "#%s", ID);
	char s[128] = "";
	sprintf(s, "window['%s']=document.createElement('%s');window['%s'].id='%s'", query, TAGNAME, query, ID);
	JavaScript::Eval(s);
}
HTMLElement::~HTMLElement() {
	if (Destroyable) {
		free(query);
		free(docname);
	}
}
void HTMLElement::Append(const char* text) {
	char* s = (char*)malloc(strlen(innerHTML) + strlen(text));
	strcpy(s, innerHTML);
	strcat(s, text);
	innerHTML = s;
	free(s);
}
void HTMLElement::Append(HTMLElement* element) {
	char b[64] = "";
	sprintf(b, "window['%s']", element->query);
	runFunction("appendChild", b);
	//char c[64] = "delete ";
	//strcat(c, b);
	//JavaScript::Eval(c);
	element->inBody = true;
}
void HTMLElement::setProperty(const char* key, const char* value) {
	char s[64] = "";
	if (inBody) sprintf(s, "%s.querySelector('%s').%s=%s", docname, query, key, JavaScript::GetStringFromPointer(value));
	else sprintf(s, "window['%s'].%s=%s", query, key, JavaScript::GetStringFromPointer(value));
	JavaScript::Eval(s);
}
char* HTMLElement::getProperty(const char* key) {
	char s[64] = "";
	if (inBody) sprintf(s, "%s.querySelector('%s').%s", docname, query, key);
	else sprintf(s, "window['%s'].%s", query, key);
	return JavaScript::Eval(s);
}
void HTMLElement::setAttribute(const char* key, const char* value) {
	char k[64] = "\"";			char v[64] = "\"";
	strcat(k, key);				strcat(v, value);
	strcat(k, "\"");			strcat(v, "\"");
	runFunction("setAttribute", k, v);
}
char* HTMLElement::getAttribute(const char* key) {
	char k[64] = "";
	strcpy(k, "");
	sprintf(k, "\"%s\"", key);
	return runFunction("getAttribute", k);
}
void HTMLElement::setStyleProperty(const char* key, const char* value) {
	char s[64] = "";
	sprintf(s, "style['%s']", key);
	setProperty(s, value);
}
char* HTMLElement::getStyleProperty(const char* key) {
	char s[64] = "";
	sprintf(s, "style['%s']", key);
	return getProperty(s);
}
void HTMLElement::addEventListener(const char* eventname, void(*h)(HTMLElement&)) {
	char a[32] = "";
	sprintf(a, "\"%s\"", eventname);
	runFunction("addEventListener", a, getJSHandler(new Handler(h), true));
}
char* HTMLElement::runFunction(const char* fname, const char* p1, const char* p2) {
	char s[128] = "";
	if (inBody) sprintf(s, "%s.querySelector('%s')['%s'](%s, %s)", docname, query, fname, p1, p2);
	else sprintf(s, "window['%s']['%s'](%s, %s)", query, fname, p1, p2);
	return JavaScript::Eval(s);
}
const char* HTMLElement::getJSHandler(EventHandler* handler, bool function) {
	HTMLElement snd = HTMLElement(query);
	HTMLElement* sender = (HTMLElement*)malloc(sizeof(HTMLElement));
	snd.Destroyable = false;
	*sender = snd;
	static string s = handler->GetWithPointer(sender, function).CharArray;
	return s;
}

HTMLElement HTMLDocument::querySelector(const char* CSS_QUERY) {
	return HTMLElement(CSS_QUERY, *this);
};
HTMLElementCollection HTMLDocument::querySelectorAll(const char* CSS_QUERY) {
	return HTMLElementCollection(CSS_QUERY, *this);
}
HTMLElement HTMLDocument::getElementById(const char* ID) {
	char b[64] = "";
	sprintf(b, "#%s", ID);
	return HTMLElement(b, *this);
};
void HTMLDocument::Append(HTMLElement* element) {
	//HTMLElement body("body");
	body.Append(element);
}
void HTMLDocument::Append(const char* text) {
	//HTMLElement body("body");
	body.Append(text);
}
HTMLBodyElement HTMLDocument::getbody() {
	return HTMLBodyElement(*this);
}
int HTMLElementCollection::get_length() {
	return len;
}
HTMLElementCollection::HTMLElementCollection(string CSS_QUERY, HTMLDocument doc) {
	object q = object(string::Format("%s.querySelectorAll(\"%s\")", doc.Name, CSS_QUERY.CharArray));
	len = (int)q["length"];
	collectionptr = (HTMLElement*)malloc(len * sizeof(HTMLElement));
	for (int i = 0; i < len; i++)
	{
		HTMLElement el = HTMLElement(CSS_QUERY + string::Format(":nth-of-type(%i)", i + 1), doc);
		el.Destroyable = false;
		collectionptr[i] = el;
	}
}
HTMLElementCollection::~HTMLElementCollection() {
	free(collectionptr);
}
HTMLElement HTMLElementCollection::operator[](int index) {
	return collectionptr[index];
}
void HTMLElementCollection::setProperty(const char* key, const char* value) {
	for (int i = 0; i < length; i++)
	{
		collectionptr[i].setProperty(key, value);
	}
}
string HTMLElementCollection::getProperty(const char* key) {
	string s = "";
	for (int i = 0; i < length; i++)
	{
		s += collectionptr[i].getProperty(key);
	}
	return s;
}
void HTMLElementCollection::addEventListener(const char* eventname, void(*handler)(HTMLElement&)) {
	for (int i = 0; i < length; i++)
	{
		collectionptr[i].addEventListener(eventname, handler);
	}
}
void HTMLMediaElement::play() {
	runFunction("play", "null", "null");
}
void HTMLMediaElement::pause() {
	runFunction("pause", "null", "null");
}
void HTMLMediaElement::load() {
	runFunction("load", "null", "null");
}
void HTMLButtonElement::click() {
	runFunction("click", "null", "null");
}
void HTMLDialogElement::Show() {
	runFunction("show", "null", "null");
}
void HTMLDialogElement::ShowModal() {
	runFunction("showModal", "null", "null");
}
void HTMLDialogElement::Close() {
	runFunction("close", "null", "null");
}

HTMLElement $(const char* CSS_QUERY) {
	return document.querySelector(CSS_QUERY);
}
HTMLElementCollection $$(const char* CSS_QUERY) {
	return document.querySelectorAll(CSS_QUERY);
}