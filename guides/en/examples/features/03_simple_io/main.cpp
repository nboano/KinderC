#include "../../../../../kinderc.hpp"

exported void console_test() {
    Console::Write("This is a test console message on %s line %i.", __FILE__, __LINE__);
    Console::Info("This is a test info message.");
    Console::Error("This is a test error message.");
}

exported void alert_test() {
    alert("This is a test alert.");
}

exported void confirm_test() {
    bool result = confirm("Are you 18?");

    if(result) {
        $("#result").innerHTML = "User is 18.";
    } else {
        $("#result").innerHTML = "User is not 18.";
    }
}

exported void prompt_test() {
    char* response = prompt("What is your name?", "BOB");

    $("#result").innerHTML = String::Format("User's name is '%s'", response);

    free(response); // Dynamically allocated
}

int main() {
    puts(R"(
    <br>
    <fieldset>
        <legend><b><code>printf</code> and <code>puts</code></b></legend>
        This content was printed using <code>puts</code>.
    </fieldset>
    )");

    printf("This content was printed using <code>%s</code>.<br>The current file is %s, the current line is %d.", "printf", __FILE__, __LINE__);
}