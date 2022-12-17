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
    $((string)"#" + ID).removeAttribute("accept");
    $((string)"#" + ID).removeAttribute("multiple");
}