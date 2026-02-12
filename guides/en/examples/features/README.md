
[Back to index](../../README.md)
# KinderC Features examples

1. [Function import and export](#function-import-and-export)
    - [Importing JS functions into KinderC](#importing-js-functions-into-kinderc)
    - [Exporting C functions to JavaScript](#exporting-c-functions-to-javascript)
    - [Evaluating JavaScript code](#evaluating-javascript-code)

## Function import and export

View the live example [here](./01_function_import_export/index.html).

### Importing JS functions into KinderC

Let's start by creating some JavaScript functions:

```js
function displayNumber(n) {
    document.getElementById("displayNumber").innerHTML = n.toString();
}
function displayText(txt_ptr, txt_len) {
    // We have to construct a string from the pointer
    var myText = IO.decode(txt_ptr, txt_len);
    document.getElementById("displayText").innerHTML = myText;
}
function getCurrentLang() {
    // IO.encode dynamically allocates new memory to fit the string
    return IO.encode(navigator.language);
}
```

> `IO.encode(str)` copies his parameter to WASM memory, and returns a pointer (that will be a `char*`) to the allocated memory. To avoid memory leaks, `free()` this pointer after it has been used.

> `IO.decode(ptr, len)` decodes $len$ bytes of memory as a string, starting from `ptr`.

To import these three functions we must:
- Make them available to the environment:
    ```js
    // Add functions to the enviroment
    env.displayNumber = displayNumber;
    env.displayText = displayText;
    env.getCurrentLang = getCurrentLang;
    ````
- Import them, using the `imported` macro:
    ```cpp
    imported void displayNumber(int n);
    imported void displayText(const char* str, int len);
    imported const char* getCurrentLang();
    ```

Now we can use our functions inside the C/C++ environment:

```cpp
// displayText wrapper
void print(const char* str) {
    displayText(str, strlen(str));
}

// Calls the 3 imported functions, directly or not
displayNumber(rand() % 100 + 1);
print("Hello World!");
const char* userLang = getCurrentLang();

// ...
free((void*)userLang); // or delete[] userLang;
```

### Exporting C functions to JavaScript

To export C/C++ functions to JavaScript, we must declare them as `exported`.

```cpp
exported int factorial(int n) {
    if(n <= 1) return n; 
    return n * factorial(n - 1);
}

exported int stringLength(const char* str) {
    return strlen(str);
}
```

Now we can call them, from example from a button:

```html
<button onclick="document.getElementById('factorial_result').innerHTML = factorial(10);">Factorial of 10</button>
```

### Evaluating JavaScript code

There are two functions to call the JS interpreter.

Use `JavaScript::Eval()` if you expect a result.
- If the result is a string, a dynamically allocated `char*` is returned.
- If the result is an `int`/`float`, cast it to the corresponding data type.
```cpp
const char* currentURL = JavaScript::Eval("location.href");
// ...
free((void*)currentURL);
```
Use `JavaScript::VoidEval()` if you don't expect a result.
```cpp
JavaScript::VoidEval(R"(
document.getElementById("voideval_output").innerHTML = 'Hello!';
)");
```