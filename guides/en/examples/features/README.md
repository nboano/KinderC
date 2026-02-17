
[Back to index](../../README.md)
# KinderC Features examples

1. [Function import and export](#function-import-and-export)
    - [Live example](./01_function_import_export/index.html)
    - [Importing JS functions into KinderC](#importing-js-functions-into-kinderc)
    - [Exporting C functions to JavaScript](#exporting-c-functions-to-javascript)
    - [Evaluating JavaScript code](#evaluating-javascript-code)

2. [Data types and memory](#data-types-and-memory)
    - [Live example](./02_data_types_malloc/index.html)
    - [Data types](#data-types)
    - [Static allocation](#static-allocation)
    - [Variable Length Arrays (VLA)](#variable-length-arrays-vla)
    - [Dynamic allocation](#dynamic-allocation)
    - [List class](#listt)

3. [Simple I/O](#simple-io)
    - [Live example](./03_simple_io/index.html)
    - [Console class](#console-class)
    - [Blocking windows](#blocking-windows)
    - [printf and puts](#printf-and-puts)

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

## Data types and memory

View the live example [here](./02_data_types_malloc/index.html).

### Data types

In KinderC, all the standard C/C++ types are available, and are mapped to the corresponding WebAssembly types.

This includes:
- `bool`
- `char`
- `short` (signed / unsigned)
- `int` (signed / unsigned)
- `long`(signed / unsigned)
- Pointer types

### Static allocation

A static array has a fixed size, that cannot be changed.

```cpp
int arr[10];
```

### Variable Length Arrays (VLA)

A VLA has variable size, and it's allocated on the function stack.

```cpp
int arr[size];
```

### Dynamic allocation

Allocating memory dynamically gives you more flexibility. 
Memory is allocated on the heap.
You can use `new` and `delete` (C++), or `malloc` and `free`.

```cpp
int* el = malloc(sizeof(int)); /* ... */ free((void*)el);
int* arr = malloc(n * sizeof(int)); /* ... */ free((void*)arr);

int* el = new int; /* ... */ delete el;
int* arr = new int[n]; /* ... */ delete[] arr;
```

### `List<T>`

The `List` is a generic, dynamically allocated List of any type. Memory is managed automatically, and freed when it's no longer of use.

```cpp
List<int> lst;
lst.Add(1);
lst.Add(2, 3, 4);
lst.Count; // 4
lst.Sort([](int a, int b) { return a - b;}); // QuickSort
```

## Simple IO

View the live example [here](./03_simple_io/index.html).

### Console class

The `Console` class allows you to write something into the browser console for debugging purposes.

You can use printf-like flags in `Console::Write`, as shown.

```cpp
Console::Write("This is a test console message on %s line %i.", __FILE__, __LINE__);
Console::Info("This is a test info message.");
Console::Error("This is a test error message.");
```

### Blocking windows

Blocking windows are wrappers for the corresponding JavaScript functions.

- `void alert(const char*)` shows and alert message.
- `bool confirm(const char*)` asks the user a Yes/No question (or Ok/Cancel, depending on the browser) and returns the result as a boolean.
- `char* prompt(const char*, const char*)` ask the user a question, specified by the 1st parameter. The user can write a text response, which is returned and must be freed. The second parameter is the default response. 

### `printf` and `puts`

`printf` and `puts` have the same syntax as C. They append content at the bottom of the page.

```cpp
puts("This content was printed using puts.<br>");

printf("This content was printed using <code>%s</code>.<br>The current file is %s, the current line is %d.", "printf", __FILE__, __LINE__);
```