#include "D:\kinderc\kinderc.hpp"

int main() {
    string s = "CIAO!";
    printf("<h1>Hello World!</h1>");
    printf("<i>Prova della funzione <code>printf</code></i><br>");
    printf("Stampo un numero e un carattere: %i, %c <br>", 42, 'A');
    printf("Stampo un numero con la virgola: %f<br>", 3.1415);
    printf("Stampo un numero con notazione esponenziale: %e<br>", 1.58e-19);
    printf("Stampo una stringa: <b>%s</b><br>", (char*)s);
    printf("Stampo un puntatore in esadecimale: %x<br>", (char*)s);
    printf("Stampo un numero in binario: %b<br>", 65);
}