# Serializzazione di dati in formato JSON

## Serializzare un oggetto qualunque

La libreria vi consente, dato un oggetto di qualunque tipo, di serializzarlo in formato JSON. Questo processo può essere utile, ad esempio, per inviare dati a un server.

Dato che il linguaggio C++ non permette di default la riflessività degli oggetti, è necessario esplicitare quali sono i suoi campi. Per fare ciò, vi vengono fornite due macro in particolare: `FIELDS` e `FIELD`.

In questo snippet ne viene illustrata la sintassi:

```cpp
struct Person
{
    const char* Name;
    const char* Surname;
    int BirthYear;

    FIELDS(Person,
        FIELD(Person, Name),
        FIELD(Person, Surname),
        FIELD(Person, BirthYear)
    )
};
```

> **N.B.** Senza esplicitare i campi nella maniera descritta sopra, la serializzazione e la deserializzazione dell'oggetto non risultano possibili.

Viene fornito un esempio che mostra come serializzare un'oggetto di tipo `Person`.

#### **`index.html`** [Visualizza](../../examples/10-json-serialisation/index.html) *(Omesso in quanto senza contenuto nel body)*

#### **`main.cpp`** [Visualizza](../../examples/10-json-serialisation/main.cpp)

```cpp
struct Person
{
    const char* Name;
    const char* Surname;
    int BirthYear;

    FIELDS(Person,
        FIELD(Person, Name),
        FIELD(Person, Surname),
        FIELD(Person, BirthYear)
    )
};


int main() {
    Person p1;

    p1.Name = "Lorenzo";
    p1.Surname = "Rossi";
    p1.BirthYear = 2003;

    printf(JSON::SerializeObjectOfType<Person>(p1));
}
```

Il codice produrrà un output simile al seguente:
```json
{
	"Name" : "Lorenzo",
	"Surname" : "Rossi",
	"BirthYear" : 2003
}
```