# 01 - Function import and export

View the live example [here](./01_function_import_export/index.html).

[Back to index](../../README.md)

**index.html**
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>01 - Function import and export</title>
    <script src="../../../../../kinderc.js"></script>
    <assembly src="./main.wasm"></assembly>
    <style>
        div#main {
            font-family: sans-serif;
            text-align: center;
        }
    </style>
    <script>
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

        // Add functions to the enviroment
        env.displayNumber = displayNumber;
        env.displayText = displayText;
        env.getCurrentLang = getCurrentLang;
    </script>
</head>
<body>
    <a href="../01_function_import_export.md">Back</a>
    <div style="text-align: center;">
        <h1>Welcome to KinderC!</h1>
        <h3>01 - Function import and export</h3>
    </div>
    <br>
    <fieldset>
        <legend><b>Importing JS functions into KinderC</b></legend>
        <i>Calling</i> <code>displayNumber(n)</code>... <span id="displayNumber">Wait a moment...</span><br>
        <i>Calling</i> <code>displayText(txt_ptr, txt_len)</code>... <span id="displayText">Wait a moment...</span><br>
        <i>Calling</i> <code>getCurrentLang()</code>... <span id="userLang">Wait a moment...</span>
    </fieldset>
    <br>
    <fieldset>
        <legend><b>Exporting C functions to JavaScript</b></legend>
        Try <button onclick="document.getElementById('factorial_result').innerHTML = factorial(10);">Factorial of 10</button> <span id="factorial_result"></span><br><br>
        Try <button onclick="document.getElementById('strlen_result').innerHTML = stringLength(IO.encode('Hello!'));"><code>strlen("Hello!")</code></button> <span id="strlen_result"></span><br>
    </fieldset>
    <br>
    <fieldset>
        <legend><b>Evaluating JavaScript code</b></legend>
        Current page: <span id="eval_output"></span><br>
        <span id="voideval_output"></span>
    </fieldset>
</body>
</html>
```

**main.cpp**
```cpp
#include "../../../../../kinderc.hpp"

// Importing function from JS environment
imported void displayNumber(int n);
imported void displayText(const char* str, int len);
imported const char* getCurrentLang();

// Exporting functions
exported int factorial(int n) {
    if(n <= 1) return n; 
    return n * factorial(n - 1);
}

exported int stringLength(const char* str) {
    return strlen(str);
}

// displayText wrapper
void print(const char* str) {
    displayText(str, strlen(str));
}

// generates the country flag as an HTML entity
string getCountryEmoji(const char* coutry_code) {
    string upperized = String(coutry_code).ToUpper();
    int ch0 = upperized[0] + 127397;
    int ch1 = upperized[1] + 127397;
    return String::Format("&#%d;&#%d;", ch0, ch1);
}

int main() {
    srand(time()); // Init random
    
    // Call the 3 imported functions, directly or not
    displayNumber(rand() % 100 + 1);
    print("Hello World!");
    const char* userLang = getCurrentLang();
    
    // Using the DOM manipulation library
    $("#userLang").innerHTML = String("User is from: ") + getCountryEmoji(userLang);

    // This memory was dynamically allocated, so it must be freed
    free((void*)userLang);

    // JavaScript interpreter calls
    const char* currentURL = JavaScript::Eval("location.href");
    $("#eval_output").innerHTML = currentURL;

    JavaScript::VoidEval(R"(
        document.getElementById("voideval_output").innerHTML = 'Hello!';
    )");
    
    // This memory was dynamically allocated, so it must be freed
    free((void*)currentURL);
}
```

[Back to index](../../README.md)