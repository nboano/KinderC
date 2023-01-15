## Strutturazione del file sorgente

Il file sorgente, ovvero quello che viene compilato da terminale, deve includere obbligatoriamente la libreria all’inizio per poter funzionare. È possibile includere file e librerie esterne, come in un ambiente C standard, utilizzando una `#include`.  
Apppena l’albero DOM viene caricato in memoria (cioè, appena la pagina viene caricata) il metodo `int main()` viene mandato in esecuzione. Proprio come in un’applicazione console, quindi, è necessario inserire tutto il codice che vogliamo venga eseguito all’interno del metodo principale.

## Tipi di dato

Come in ogni linguaggio a tipizzazione forte, anche in C e C++ abbiamo una serie di tipi dato diversi. Oltre ai tipi dato di sistema, utilizzando KinderC ne vengono aggiunti altri due.

### Tipi di dato fondamentali

| Nome del tipo | Dimensione (Byte) | Descrizione                        | Flag |
|---------------|-------------------|------------------------------------|------|
| `char`        | 1                 | Rappresenta un carattere ASCII.    | %c   |
| `bool`        | 1                 | Rappresenta un valore booleano.    | -    |
| `wchar_t`     | 2                 | Rappresenta un carattere Unicode.  | -    |
| `short`       | 2                 | Rappresenta un intero su 16bit.    | %i   |
| `int`         | 4                 | Rappresenta un intero su 32bit.    | %i   |
| `long`        | 8                 | Rappresenta un intero su 64bit.    | %i   |
| `float`       | 4                 | Rappresenta un decimale su 32bit.  | %f   |
| `double`      | 8                 | Rappresenta un decimale su 64bit.  | %f   |

### Tipi di dato aggiuntivi

| Nome del tipo | Dimensione (Byte) | Descrizione                                    |
|---------------|-------------------|------------------------------------------------|
| `string`      | 4 + n.di caratteri| Rappresenta una serie di char allocata in heap.|
| `object`      | 8                 | Punta a un qualunque oggetto JavaScript.       |

Generalmente, quando dichiariamo una variabile, è necessario specificare il suo tipo.

```cpp
int n = 15;
const double PI = 3.14159;
```

Tuttavia, a seconda delle nostre preferenze, è anche possibile ometterlo, lasciando tipizzare il sistema. 

Le due scritture presentate sotto sono assolutamente equivalenti. Lo standard C++ prevede l'utilizzo di `auto`, ma includendo KinderC è anche possibile utilizzare `var`.

```cpp
var mStr = "Ciao a tutti";
auto str2 = "Seconda stringa";
```