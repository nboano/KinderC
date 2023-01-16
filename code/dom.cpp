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
HTMLElement::HTMLElement(const char* CSS_QUERY, int CollectionIndex, HTMLDocument doc) : HTMLElement(CSS_QUERY, doc) {
	cindex = CollectionIndex;
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
	const char* key = "innerHTML";
	char s[64 + strlen(query)];
	strcpy(s, "");
	if (inBody) sprintf(s, "%s.querySelectorAll('%s')[%i].%s+=%s", docname, query, cindex, key, JavaScript::GetStringFromPointer(text));
	else sprintf(s, "window['%s'].%s=%s", query, key, JavaScript::GetStringFromPointer(text));
	JavaScript::VoidEval(s);
}
void HTMLElement::Append(HTMLElement* element) {
	if(element->inBody) return;
	char b[64 + strlen(query)];
	strcpy(b, "");
	sprintf(b, "window['%s']", element->query);
	runFunction("appendChild", b);
	element->inBody = true;
}
void HTMLElement::setProperty(const char* key, const char* value) {
	char s[64 + strlen(query)];
	strcpy(s, "");
	if (inBody) sprintf(s, "%s.querySelectorAll('%s')[%i].%s=%s", docname, query, cindex, key, JavaScript::GetStringFromPointer(value));
	else sprintf(s, "window['%s'].%s=%s", query, key, JavaScript::GetStringFromPointer(value));
	JavaScript::VoidEval(s);
}
char* HTMLElement::getProperty(const char* key) {
	char s[64 + strlen(query)];
	strcpy(s, "");
	if (inBody) sprintf(s, "%s.querySelectorAll('%s')[%i].%s", docname, query, cindex, key);
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
void HTMLElement::removeAttribute(const char* key) {
	string s = (string)"\"" + key + "\"";
	runFunction("removeAttribute", s);
}
bool HTMLElement::hasAttribute(const char* key) {
	char* resp = runFunction("hasAttribute", (string)"\"" + key + "\"");
	bool r = strcmp(resp, "true") == 0;
	free(resp);
	return r;
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
	char s[128 + strlen(query)];
	strcpy(s, "");
	if (inBody) sprintf(s, "%s.querySelectorAll('%s')[%i]['%s'](%s, %s)", docname, query, cindex, fname, p1, p2);
	else sprintf(s, "window['%s']['%s'](%s, %s)", query, fname, p1, p2);
	return JavaScript::Eval(s);
}
HTMLElement HTMLElement::Find(const char* CSS_QUERY) {
	return HTMLElement(CSS_QUERY, HTMLDocument(String::Format("%s.querySelectorAll('%s')[%i]", docname, query, cindex)));
}
class HTMLElementCollection;
HTMLElementCollection HTMLElement::FindAll(const char* CSS_QUERY) {
	return HTMLElementCollection(CSS_QUERY, HTMLDocument(String::Format("%s.querySelectorAll('%s')[%i]", docname, query, cindex)));
}
const char* HTMLElement::getJSHandler(EventHandler* handler, bool function) {
	HTMLElement snd = HTMLElement(query);
	HTMLElement* sender = (HTMLElement*)malloc(sizeof(HTMLElement));
	snd.Destroyable = false;
	*sender = snd;
	string s = handler->GetWithPointer(sender, function).CharArray;
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
	body.Append(element);
}
void HTMLDocument::Append(const char* text) {
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
		HTMLElement el = HTMLElement(CSS_QUERY, i, doc);
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
void HTMLElementCollection::setAttribute(string key, string value) {
	for (int i = 0; i < length; i++)
	{
		collectionptr[i].setAttribute(key, value);
	}
}
void HTMLElementCollection::setStyleProperty(string key, string value) {
	for (int i = 0; i < length; i++)
	{
		collectionptr[i].setStyleProperty(key, value);
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
template<class T>
void Control<T>::Use(HTMLElement elm) {
    ChangeHandler(nullptr);
    Handler hndl { ChangeHandler };
    JavaScript::Eval("new MutationObserver(%s).observe(document.querySelector('%s'),{childList:true,subtree:true,attributes:true})", (char*)hndl.GetWithPointer(0, true), elm.query);
}

template<class T>
void Control<T>::ChangeHandler(void*) {
    HTMLElementCollection coll = $$(T::TagName);
	int l = coll.length;

    for(int i = 0; i < l; i++) {
        if(!coll[i].hasAttribute("kc_rendered")) {
            coll[i].innerHTML = T(coll[i]).Render();
            coll[i].setAttribute("kc_rendered", "");
			T(coll[i]).PostRender();
        }
    }

	if(firstrender && l) {
		OnFirstRender();
		firstrender = false;
	} 
	OnRender();
}

template<class T>
void(*Control<T>::OnRender)() = [](){};

template<class T>
void(*Control<T>::OnFirstRender)() = [](){};

template<class T>
bool Control<T>::firstrender = true;

HTMLElement $(const char* CSS_QUERY) {
	return document.querySelector(CSS_QUERY);
}
HTMLElementCollection $$(const char* CSS_QUERY) {
	return document.querySelectorAll(CSS_QUERY);
}