#pragma once
#include "../kinderc.hpp"

const char* OpenFileDialog::ID = "__kc_ofd";

void OpenFileDialog::assert_ofd() {
    if(!$((string)"#" + ID).Exists) {
        document << (string)"<input type='file' id='" + ID + "' style='display:none;'/>";
    }
}
void OpenFileDialog::Show() {
    assert_ofd();
	((HTMLButtonElement)$((string)"#" + ID)).click();
}
void OpenFileDialog::Reset() {
    assert_ofd();
    $((string)"#" + ID).removeAttribute("accept");
    $((string)"#" + ID).removeAttribute("multiple");
}

Property<const char*> OpenFileDialog::Filter = Property<const char*>([](const char* filter) {
    assert_ofd();
    $((string)"#" + ID).setAttribute("accept", filter);
});

Property<bool> OpenFileDialog::Multiple = Property<bool>([](bool multiple) {
    assert_ofd();
    if(multiple) $((string)"#" + ID).setAttribute("multiple", "");
    else $((string)"#" + ID).removeAttribute("multiple");
});