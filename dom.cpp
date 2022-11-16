#include "string.hpp"
#include "malloc.hpp"
#include "kinderc.hpp"

class HTMLElement;
class HTMLBodyElement;

class HTMLDocument {
	public:
		HTMLDocument(const char* n) {
			name = (char*)malloc(strlen(n));
			strcpy(name, n);
		}
		HTMLDocument() {
			name = (char*)-1;
		}
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
		#ifndef __INTELLISENSE__
		const char* getname() { if ((int)name != -1) return (const char*)name; else return "document"; }
		#endif
		HTMLBodyElement getbody();
		__declspec(property(get = getname)) const char* Name;
		__declspec(property(get = getbody)) HTMLBodyElement body;
	private:
		char* name;
};
HTMLDocument document;
class HTMLElement
{
	public:
		HTMLElement(const char* CSS_QUERY, HTMLDocument doc = document) {
			docname = (char*)malloc(strlen(doc.Name));
			strcpy(docname, doc.Name);
			query = (char*)malloc(strlen(CSS_QUERY));
			strcpy(query, CSS_QUERY);
			inBody = true;
		}
		HTMLElement(const char* TAGNAME, const char* ID, HTMLDocument doc = document) {
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
		~HTMLElement() {
			if (Destroyable) {
				free(query);
				free(docname);
			}
		}
		void Append(const char* text) {
			char* s = (char*)malloc(strlen(innerHTML) + strlen(text));
			strcpy(s, innerHTML);
			strcat(s, text);
			innerHTML = s;
			free(s);
		}
		void Append(HTMLElement* element) {
			char b[64] = "";
			sprintf(b, "window['%s']", element->query);
			runFunction("appendChild", b);
			//char c[64] = "delete ";
			//strcat(c, b);
			//JavaScript::Eval(c);
			element->inBody = true;
		}
		void operator << (const HTMLElement* res) {
			Append((HTMLElement*)res);
		}
		void operator << (const char* res) {
			Append(res);
		}
		void setProperty(const char* key, const char* value) {
			char s[64] = "";
			if(inBody) sprintf(s, "%s.querySelector('%s').%s=%s", docname, query, key, JavaScript::GetStringFromPointer(value));
			else sprintf(s, "window['%s'].%s=%s", query, key, JavaScript::GetStringFromPointer(value));
			JavaScript::Eval(s);
		}
		char* getProperty(const char* key) {
			char s[64] = "";
			if(inBody) sprintf(s, "%s.querySelector('%s').%s", docname, query, key);
			else sprintf(s, "window['%s'].%s", query, key);
			return JavaScript::Eval(s);
		}
		void setAttribute(const char* key, const char* value) {
			char k[64] = "\"";			char v[64] = "\"";
			strcat(k, key);				strcat(v, value);
			strcat(k, "\"");			strcat(v, "\"");
			runFunction("setAttribute", k, v);
		}
		char* getAttribute(const char* key) {
			char k[64] = "";
			strcpy(k, "");
			sprintf(k, "\"%s\"", key);
			return runFunction("getAttribute", k);
		}
		void setStyleProperty(const char* key, const char* value) {
			char s[64] = "";
			sprintf(s, "style['%s']", key);
			setProperty(s, value);
		}
		char* getStyleProperty(const char* key) {
			char s[64] = "";
			sprintf(s, "style['%s']", key);
			return getProperty(s);
		}
		void addEventListener(const char* eventname, EventHandler* handler) {
			char a[32] = "";
			sprintf(a, "\"%s\"", eventname);
			
			runFunction("addEventListener", a, getJSHandler(handler, true));
		}
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
		char* runFunction(const char* fname, const char* p1, const char* p2 = "null") {
			char s[128] = "";
			if(inBody) sprintf(s, "%s.querySelector('%s')['%s'](%s, %s)", docname, query, fname, p1, p2);
			else sprintf(s, "window['%s']['%s'](%s, %s)", query, fname, p1, p2);
			return JavaScript::Eval(s);
		}
		const char* getJSHandler(EventHandler* handler, bool function = false) {
			//static char s[64];
			//strcpy(s, "");
			//HTMLElement snd = HTMLElement(query);
			//HTMLElement* sender = (HTMLElement*)malloc(sizeof(HTMLElement));
			//snd.Destroyable = false;
			//*sender = snd;
			//sprintf(s, function ? "()=>%s(%i)" : "%s(%i)", handler->HandlerFunctionName.CharArray, (int)sender);
			//return s;
			HTMLElement snd = HTMLElement(query);
			HTMLElement* sender = (HTMLElement*)malloc(sizeof(HTMLElement));
			snd.Destroyable = false;
			*sender = snd;
			static string s = handler->GetWithPointer(sender, function).CharArray;
			return s;
		}
		char* query;
		bool inBody;
		char* docname;
};
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

HTMLElement HTMLDocument::querySelector(const char* CSS_QUERY) {
	return HTMLElement(CSS_QUERY, *this);
};
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


HTMLElement $(const char* CSS_QUERY) {
	return document.querySelector(CSS_QUERY);
}