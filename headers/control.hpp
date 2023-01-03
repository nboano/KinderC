#pragma once
#include "../kinderc.hpp"

#define ControlInit(name) name(HTMLElement el) : Control(el) {}; static constexpr const char* TagName = #name;

template<class T>
class Control : public HTMLElement {
public:
    Control(HTMLElement el) : HTMLElement(el.query) {}
    static void Use() {
        ChangeHandler(nullptr);
        Handler hndl { ChangeHandler };
        JavaScript::Eval("new MutationObserver(%s).observe(document.body,{childList:true})", (char*)hndl.GetWithPointer(0, true));
    }
private:
    static void ChangeHandler(void*) {
        HTMLElementCollection coll = $$(T::TagName);

        for(int i = coll.length - 1; i >= 0; i--) {
            coll[i].outerHTML = T::Render((T)coll[i]);
        }
    }
};