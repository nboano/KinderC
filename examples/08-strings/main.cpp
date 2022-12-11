#include "../../kinderc.hpp"

int main() {
    string s = "Stringa di prova.";

    printf("%s. Lunghezza: <b>%i</b><br><br>", (char*)s, s.Length);

    s += "Altri caratteri concatenati.";
    s += "<br>";

    puts(s);
    puts(s.ToUpper());

    puts((string)"Posso anche aggiungere numeri a una stringa: <b>" + (string)25 + "</b><br><br>");


    string* spl = String("Provo;Lo;Split...").Split(';');

    puts(spl[0] + "<br>");
    puts(spl[1] + "<br>");
    puts(spl[2] + "<br>");
}