## Le stringhe C ANSI

Esattamente come in un programma C ANSI, è possibile creare e manipolare semplici stringhe come array di caratteri. Questo approccio è tuttavia sconsigliato, in quanto esiste un oggetto [`string`](string-class.md#le-stringhe-come-oggetti-il-tipo-string) di più facile utilizzo, che si ridimensiona automaticamente e che viene deallocato quando non più necessario.

### Caratteristiche delle stringhe C
 - Hanno tipo `char*` se allocate dinamicamente, `char[]` se allocate staticamente, `const char*` se inizializzate con uno *string literal*.
 - Sono semplici sequenze di caratteri, terminate da un tappo (`'\0'`).
 - Non sono ridimensionabili. Per creare una stringa più grande è necessario allocarla e copiarci dentro la vecchia stringa.
 - Possono essere inizializzate con uno *string literal* (es. `"CIAO"`) o con un *RAW string literal* (es. `R"(CIAO)"`)
 - Le stringhe allocate dinamicamente vanno deallocate.

```cpp
char* s = new char[20]; // Allocazione dinamica
char s[20];             // Allocazione statica
const char* sl = "STRING LITERAL";
const char* rsl = R"(
    RAW STRING LITERAL
)";
```

### Metodi per manipolare le stringhe C

|Metodo   |Descrizione                                                           |
|---------|----------------------------------------------------------------------|
|`strlen` | Dato un array di caratteri (`char*`) in input, restituisce la    lunghezza della stringa associata.                                               |
|`strrev` | Dato un array di caratteri, lo inverte.                              |
|`strcmp` | Dati due array di caratteri, li compara. Restituisce 0 se sono uguali, un valore <0 se la prima precede alfabeticamente la seconda, un valore >0 altrimenti.|
|`strcpy` | Dato un array di caratteri abbastanza capiente, vi copia dentro il secondo array passato come parametro e aggiunge un terminatore (`'\0'`). **N.B.** Non ci sono controlli di overflow.                                                   | 
|`strcat` | Concatena la seconda stringa alla prima e aggiunge un terminatore (`'\0'`). &Egrave; necessario che la prima stringa sia abbastanza grande.        |
|`strupr` | Rende una stringa completamente maiuscola.                           |
|`strlwr` | Rende una stringa completamente minuscola.                           |
|`strtok` | Dati una stringa e un carattere separatore, restituisce la stringa fino a quel carattere (il *token*).                                                     |
|`sprintf`| Data una stringa abbastanza grande, utilizza i flag della funzione [`printf`](#la-funzione-printf) per stamparvi variabili all'interno in un preciso formato.                                                                         |

### Esempio di utilizzo dei metodi delle stringhe C

#### **`index.html`** [Visualizza](../../examples/07-c-strings/index.html) *(Omesso in quanto senza contenuto nel body)*

#### **`main.cpp`** [Visualizza](../../examples/07-c-strings/main.cpp)
```cpp
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
```