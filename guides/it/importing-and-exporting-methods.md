## Importazione ed esportazione di metodi

Le due macro che vi vengono illustrate (`imported` ed `exported`), se scritte prima del prototipo di una funzione qualsiasi, permettono ad essa di essere esportata oppure importata dall'ambiente JavaScript.

### Importazione dei metodi (`imported`)

Utilizzando la parola chiave `imported` è possibile rendere accessibile un qualsiasi metodo JavaScript dal nostro programma C++.

Segue un esempio dove viene importato un metodo che ritorna il timestamp UNIX corrente.

#### **`index.html`** [Visualizza](../../examples/02-imported/index.html)
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>KinderC - Importing functions</title>

    <script src="https://cdn.jsdelivr.net/gh/nboano/kinderc/kinderc.js"></script>
    <assembly src="main.wasm"></assembly>

    <script>
        env.ottieniTempo = function() {
            return Date.now() / 1000;
        }
    </script>
</head>
<body>
```
> Per scrivere una funzione JavaScript che sia visibile dal programma compilato, è necessario farla figliare all'oggetto `env`. In caso contrario, un errore verrà generato.

#### **`main.cpp`** [Visualizza](../../examples/02-imported/main.cpp)
```cpp
#include "../../kinderc.hpp"

imported unsigned long ottieniTempo();

int main() {
    printf("Secondi passati dal 1 GEN 1970: %i", ottieniTempo());
}
```

> Nell'esempio, la funzione importata viene richiamata, e il suo risultato stampato a schermo.

![](guides/images/04-imported-ex.png)

**N.B.** Con una `imported` è possibile importare solo funzioni che hanno parametri numerici e che restituiscono valori numerici. Non è possibile passare direttamente le stringhe a una funzione JS, in quanto la stringa, in un linguaggio come il C++, è un puntatore.

### Esportazione dei metodi (`exported`)

Al contrario, la macro `exported` rende una funzione o una procedura del compilato globalmente accessibile dalla pagina. 

Di seguito viene riportato lo snippet di una funzione che calcola il valore della potenza dati base ed esponente e lo scrive in un elemento del DOM.

#### **`index.html`** [Visualizza](../../examples/03-exported/index.html)
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>KinderC - Exporting functions</title>

    <script src="https://cdn.jsdelivr.net/gh/nboano/kinderc/kinderc.js"></script>
    <assembly src="main.wasm"></assembly>

</head>
<body>
    <input type="number" placeholder="Base" id="txtBase">
    <br>
    <input type="number" placeholder="Esponente" id="txtEsponente">
    <br><br>
    <button onclick="esponenziale(document.querySelector('#txtBase').valueAsNumber, document.querySelector('#txtEsponente').valueAsNumber)">Calcola</button>
    <br><br>
    Il risultato &egrave;: <b id="lblRisultato"></b>
</body>
</html>
```

#### **`main.cpp`** [Visualizza](../../examples/03-exported/main.cpp)

```cpp
#include "../../kinderc.hpp"

exported void esponenziale(int base, int esponente) {
    long risultato = base;
    for (int i = 0; i < esponente - 1; i++) risultato *= base;

    $("#lblRisultato").innerText = String::Format("%i", risultato);
}

int main() {}
```

![](../images/05-exported-ex.png)