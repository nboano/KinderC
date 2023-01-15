## Le stringhe come oggetti: il tipo `string`

La libreria vi mette a disposizione un comodo tipo dati, `string`, che come in tanti altri linguaggi non è altro che una semplice sequenza di caratteri con però molte proprietà e metodi che ne facilitano l'utilizzo.

Utilizzare una stringa rispetto a un array di caratteri ha alcuni vantaggi:
- I caratteri di una `string` vengono sempre allocati nell'*heap* tramite `malloc`.
- La memoria che la stringa occupa viene liberata non appena essa non è più necessaria (attraverso il distruttore `~String()`).
- La concatenazione di un'altra stringa alla stringa di partenza ne provoca il ridimensionamento automatico.

> **N.B.** Vi viene in ogni caso offerta la possibilità di lavorare manualmente sulla zona di memoria che contiene i caratteri della stringa accedendo alla proprietà `CharArray`. Si utilizzi l'accesso diretto all'array di caratteri solo se si sa su cosa si sta lavorando, in quanto il suo utilizzo spropositato potrebbe portare a problemi di vario genere.

### Metodi e proprietà dell'oggetto `string`

-   Inizializzano nuove stringhe, a partire da *string literals* oppure da interi, che vengono automaticamente convertiti.
    ```cpp
    string s = "Nel mezzo del cammin di nostra vita...";
    auto s2 = (string)11;
    ```

-   Riassegnazione e concatenazione (la stringa si ridimensiona da sola).
    ```cpp
    s2 = String("Riassegnazione di una stringa");
    s += "e concatenazione di un'altra stringa";
    ```

-   Comparazione tra stringhe.
    ```cpp
    if(s == s2) {
        ...
    }

    if(s.CompareTo(s2) < 0) {
        ...
    }
    ```

-   Lunghezza di una stringa.  
    ```cpp
    string myStr = "Ciaoo";

    myStr.Length
    ```
-   Casting esplitito di una stringa.
    ```cpp
    printf("La mia stringa: %s", (char*)myStr);
    ```
-   Concatenazione multipla.
    ```cpp
    string s = String("ciao") + s + s2;
    ```
-   Metodi `StartsWith` ed `EndsWith`.
    ```cpp
    String("Ciao a tutti").StartsWith("Ciao");
    String("Ciao a tutti").EndsWith("tutti");
    ```
-   Metodo `Split`.
    ```cpp
    String("Nome;Cognome;Classe;Data").Split(';');
    ```
-   Metodi `ToUpper` e `ToLower`.
    ```cpp
    s.ToUpper();
    s.ToLower();
    ```

### Esempio di utilizzo dell'oggetto `string`

#### **`index.html`** [Visualizza](examples/08-strings/index.html) *(Omesso in quanto senza contenuto nel body)*

#### **`main.cpp`** [Visualizza](examples/08-strings/main.cpp)
```cpp
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
```