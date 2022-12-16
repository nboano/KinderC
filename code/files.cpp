#pragma once
#include "../kinderc.hpp"

const char* OpenFileDialog::ID = "__kc_ofd";

void OpenFileDialog::assert_ofd() {
    if(!$has((string)"#" + ID)) {
        document << (string)"<input type='file' id='" + ID + "' style='display:none;'/>";
    }
}
void OpenFileDialog::Show() {
    assert_ofd();
	((HTMLButtonElement)$((string)"#" + ID)).click();
}
void OpenFileDialog::Reset() {

}