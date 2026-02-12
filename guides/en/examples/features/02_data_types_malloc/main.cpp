#include "../../../../../kinderc.hpp"

exported void sall() {
    int arr[10];

    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100;
    }
    
    $("#static_allocation").innerHTML = "";

    for(int el : arr) {
        $("#static_allocation") << String(el) + " ";
    }
}

exported void vlarr() {
    const char* len_str = HTMLInputElement($("#vla_len")).value;
    int len = atoi(len_str);
    free((void*)len_str);

    if(len <= 1 || len > 100) {
        $("#vla").innerHTML = "Invalid length.";
        return;
    }

    int arr[len];

    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % 100;
    }
    
    $("#vla").innerHTML = "";

    for(int i = 0; i < len; i++) {
        $("#vla") << String(arr[i]) + " ";
    }
}

exported void dallarr() {
    const char* len_str = HTMLInputElement($("#dall_len")).value;
    int len = atoi(len_str);
    free((void*)len_str);

    if(len <= 1 || len > 100) {
        $("#dall").innerHTML = "Invalid length.";
        return;
    }

    int* arr = new int[len]; // malloc(len * sizeof(int))

    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % 100;
    }
    
    $("#dall").innerHTML = "";

    for(int i = 0; i < len; i++) {
        $("#dall") << String(arr[i]) + " ";
    }

    delete[] arr; // free((void*)arr);
}


exported void intlst() {
    const char* len_str = HTMLInputElement($("#list_len")).value;
    int len = atoi(len_str);
    free((void*)len_str);

    if(len <= 1 || len > 100) {
        $("#list").innerHTML = "Invalid length.";
        return;
    }

    List<int> lst;

    for (int i = 0; i < len; i++)
    {
        lst.Add(rand() % 100);
    }

    lst.Sort([](int a, int b) { return a - b;});
    
    $("#list").innerHTML = "";

    for(int i = 0; i < lst.Count; i++) {
        $("#list") << String(lst[i]) + " ";
    }
}

int main() {

    srand(time()); // Init random

    int a = 15;
    double b = 3.1415;
    char c = 'A';
    void* d = &a;
    const char* e = "Hello!";

    $("#data_types") << String::Format(R"(
        This is an int: %d. Its size is %d bytes.<br>
        This is a double: %f. Its size is %d bytes.<br>
        This is a char: %c. Its size is %d bytes.<br>
        This is a pointer: %x. Its size is %d bytes.<br>
        This is a string: %s. Its size is %d bytes (pointer).<br>
    )", a, sizeof(a), b, sizeof(b), c, sizeof(c), d, sizeof(d), e, sizeof(e));
}