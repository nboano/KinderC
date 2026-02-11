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