## Programmazione a oggetti (OOP)
Essendo C++ un linguaggio a oggetti, la maggior parte dei metodi che la libreria vi mette a disposizione sono proprio contenuti all'interno di oggetti specifici, come `HTMLElement` o `string`.

Vi viene data la possibilità di utilizzare le classi C++ per creare oggetti che più si adattano alla natura del vostro progetto.

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