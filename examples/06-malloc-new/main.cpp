#include "../../kinderc.hpp"

exported void allocate_and_print(int n) {
    int* array = new int[n];
    // Same as int* array = (int*)malloc(n*sizeof(int));

    $("#results").innerHTML = "";
    string rs = "";

    for (int i = 0; i < n; i++)
    {
        array[i] = i + 1;
        rs += (char*)string::Format("<b>array[%i]</b>: %i<br>", i, array[i]);
    } 

    $("#results").innerHTML = rs;

    delete[] array;
    // Same as free(array);
}

int main() {}