## Programmazione a oggetti (OOP)
Essendo C++ un linguaggio a oggetti, la maggior parte dei metodi che la libreria vi mette a disposizione sono proprio contenuti all'interno di oggetti specifici, come `HTMLElement` o `string`.

Vi viene data la possibilità di utilizzare le classi (oppure le struct) C++ per creare oggetti che più si adattano alla natura del vostro progetto.

```cpp
class Persona {
    public:
    
    Persona();                      // COSTRUTTORE

    ~Persona();                     // DISTRUTTORE

    void Visualizza();              // METODO

    Property<const char*> Nome;     // PROPRIETA'
}
```

### Creazione di property: La classe `Property<T>`

La libreria vi mette a disposizione una comoda classe tipizzata (`Property<T>`) per la creazione di property all'interno di classi o struct, cosa non possibile utilizzando solo le funzionalità native del linguaggio C++.

#### Esempio di utilizzo

#### **`index.html`** [Visualizza](../../examples/09-properties/index.html) *(Omesso in quanto senza contenuto nel body)*

#### **`main.cpp`** [Visualizza](../../examples/09-properties/main.cpp)

```cpp
#include "../../kinderc.hpp"

class Persona {
    public:

    Property<const char*> Nome {
        [](void* pers) {
            return ((Persona*)pers)->nome;
        },
        [](void* pers, const char* value) {
            if(strlen(value) < 2) {
                Console::Error("Il nome di una persona deve essere lungo almeno 2 caratteri!");
                return;
            }

            ((Persona*)pers)->nome = value;
        }, this
    };

    private:
    const char* nome;
};

int main() {
    Persona p;
    p.Nome = "TIZIO"; // Il nome sarà settato correttamente
    p.Nome = ""; // Il nome non sarà settato

    printf(p.Nome); // Richiamo il getter
}
```


