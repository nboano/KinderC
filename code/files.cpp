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

Property<File*> OpenFileDialog::Files = Property<File*>([](){
    int len = FilesNumber;
    Console::Write("numero file: %i", len);
    File* arr = new File[len];

    for (int i = 0; i < len; i++)
    {
        arr[i] = File((string)"document.querySelector('#" + (string)ID + "').files[" + (string)i + "]");
    }

    return arr;
});

Property<int> OpenFileDialog::FilesNumber = Property<int>([]() {
    return (int)JavaScript::Eval((string)"document.querySelector('#" + (string)ID + "').files.length");
});

void File::ReadAsTextAsync(void(*callback)(const char* data)) {
    Handler* h = new EventHandler((void(*)(void*))callback);
    JavaScript::Eval("%s.text().then(txt=>__lambda_call(%i,IO.encode(txt)))", (char*)s, h->LambdaIndex);
}

#ifndef __INTELLISENSE__
unsigned long File::get_LastModified() {
    return (int)operator[]("lastModified");
}
unsigned long File::get_Size() {
    return (int)operator[]("size");
}
string File::get_Name() {
    return (char*)operator[]("name");
}
string File::get_MimeType() {
    return (char*)operator[]("type");
}
#endif