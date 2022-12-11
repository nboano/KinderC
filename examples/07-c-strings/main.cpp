#include "../../kinderc.hpp"

int main() {
    char str[128];

    strcpy(str, "Stringa di prova. ");
    puts(str);
    printf("<br><b>Lunghezza stringa:</b> %i<br><br>", strlen(str));

    strcat(str, "Testo aggiunto alla stringa str.");
    puts(str);
    printf("<br><b>Lunghezza stringa:</b> %i<br>", strlen(str));

    strupr(str);
    printf("<br>Metto in maiuscolo la stringa e la visualizzo: <b>%s</b><br><br>", str);

    strcpy(str, "");
    sprintf(str, "%s: %i, %c", "Stampo dei valori nella stringa", 10, 'A');
    puts(str);
}