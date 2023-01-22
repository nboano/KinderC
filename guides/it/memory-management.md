## Gestione della memoria

Sicuramente uno dei vantaggi dell'utilizzo di questa libreria è la possibilità per il programmatore di allocare la memoria come meglio crede. Vediamo come.

### La memoria in KinderC

Basandosi su WebAssembly, KinderC ne eredita lo schema di memoria.  
Al caricamento della pagina un'area virtuale di memoria dalla dimensione di 131072 byte (128 kB) viene allocata. Al suo interno saranno memorizzate e allocate (in maniera statica, cioè al caricamento del binario in memoria) tutte le variabili, locali e globali, insieme agli array allocati staticamente (vedi [Allocazione statica](#allocazione-statica)). Quest'area di memoria costituisce il cosiddetto **stack**, che ha una dimensione limitata.

Se sono necessarie quantità di memoria più grandi, esse vanno richieste esplicitamente a runtime, utilizzando le funzioni di [allocazione dinamica](#allocazione-dinamica). Allocando dinamicamente la memoria, viene riservato spazio nella cosiddetta **heap**, area di memoria successiva allo stack, dove si può accedere esclusivamente con puntatori. La creazione e la distruzione di blocchi di memoria heap avviene su richiesta del programmatore e dinamicamente, cioè a runtime.

> Alcuni tipi dato, come ad esempio `string`, utilizzano l'allocazione dinamica in maniera implicita. Un'istanza di stringa, pur parendo una normale variabile statica, in realtà contiene al suo interno un puntatore alla heap (il `CharArray`) dove la stringa è effettivamente allocata.

### Allocazione statica

Tutte le variabili sono allocate staticamente dal sistema, in una zona di memoria chiamata *stack*. Le variabili globali vengono allocate al caricamento del programma, e saranno deallocate solo alla chiusura della pagina. Lo stesso discorso vale per le variabili dichiarate `static`.

Le variabili locali, invece, vengono allocate al momento della loro dichiarazione e deallocate alla fine del metodo che le contiene.

Infine anche gli array sono allocati nello stack. Per questo motivo la loro dimensione deve essere decisa a priori e non può essere cambiata.

```cpp
int n = 0x16; // Sono allocati nello stack 4 byte.
int vett[50] = {-16, 0, 8, 65, -10e2, -4, ...}; // Sono allocati nello stack 4*50 byte.
char str[] = "CIAO"; // Sono allocati nello stack 5 byte (4 char + \0)
```

### Allocazione dinamica

Come già specificato prima, è possibile e spesso necessaro allocare dinamicamente la memoria. KinderC offre due funzioni in particolare adatte a questo scopo: `malloc` e `free`, già presenti nelle librerie ANSI C standard. Il loro funzionamento è identico a queste ultime.

#### La funzione `malloc`

La `malloc` alloca N byte all'interno dell'*heap* e restituisce il puntatore all'area allocata. Nel caso in cui la memoria richiesta non bastasse, verrà richiesto automaticamente browser di espanderla di 65536 byte alla volta.

**N.B.** Il puntatore restituito è un puntatore generico (`void*`). Per assegnarlo a un puntatore di altro tipo, è necessario un cast esplicito.

```cpp
int* arrayptr = (int*)malloc(5 * sizeof(int)); // Riservo posto per 5 interi.

arrayptr[0] = 15;
*(arrayptr + 1) = -130;
```

#### La funzione `free` 

Una volta che la memoria allocata dinamicamente non è più necessaria, è buona norma liberarla. A tal scopo, esiste la funzione `free`, che, passato un puntatore in input, libera la zona di memoria a esso associata.

```cpp
free(arrayptr);
```

#### Gli operatori `new` e `delete` di C++

Vi sono due operatori appositi in C++ che svolgono le stesse operazioni di `malloc` e `free`, cioè `new` e `delete`.

- `new` alloca un oggetto in heap.
    ```cpp
    auto el = new HTMLElement(...);
    ```
- `delete` elimina un oggetto allocato con `new`.
    ```cpp
    delete el;
    ```
- `new[]` alloca dinamicamente un array di un certo tipo, data una dimensione.
    ```cpp
    int* arrayptr = new int[5];
    ```
- `delete[]` elimina un array allocato con `new[]`.
    ```cpp
    delete[] arrayptr;
    ```

### Esempio di utilizzo dell'allocazione dinamica

#### **`index.html`** [Visualizza](../../examples/06-malloc-new/index.html)
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>KinderC - Malloc</title>

    <script src="https://cdn.jsdelivr.net/gh/nboano/kinderc/kinderc.js"></script>
    <assembly src="main.wasm"></assembly>
</head>
<body>
    <button onclick="allocate_and_print(10);">Alloca 10 elementi</button>
    <button onclick="allocate_and_print(50);">Alloca 50 elementi</button>
    <button onclick="allocate_and_print(100);">Alloca 100 elementi</button>
    <div id="results"></div>
</body>
</html>
```

#### **`main.cpp`** [Visualizza](../../examples/06-malloc-new/main.cpp)
```cpp
#include "../../kinderc.hpp"

exported void allocate_and_print(int n) {
    int* array = new int[n];
    // Same as int* array = (int*)malloc(n*sizeof(int));

    $("#results").innerHTML = "";
    string rs = "";

    for (int i = 0; i < n; i++)
    {
        array[i] = rand() % 100;
        rs += (char*)string::Format("<b>array[%i]</b>: %i<br>", i, array[i]);
    } 

    $("#results").innerHTML = rs;

    delete[] array;
    // Same as free(array);
}

int main() {
    srand(time());
}
```