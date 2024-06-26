# Serializzazione e deserializzazione di dati in formato JSON

## Introduzione
All'interno del namespace `KinderC::Serialization` è presente la classe `JSON`, che contiene metodi utili al fine di serializzare e deserializzare oggetti C++ in formato JSON, utilizzando un parser integrato alla libreria.

Per importare la classe nel namespace corrente, è necessario includerlo:
```cpp
using namespace KinderC::Serialization;
```

In questo modo si avranno a disposizione:
- La classe `JSON`, che contiene metodi per serializzare e deserializzare oggetti.
- La classe `Serilizable`, da cui gli oggetti serializzabili devono ereditare.
- La classe `Field`, che rappresenta il campo di un oggetto C++ e che lo associa al nome JSON del campo (ad esempio, il campo `Test.Field`, stringa, può essere serializzato come `"field":"..."`)

Vediamo un esempio di mappatura a classi di un oggetto JSON:

#### **`model.hpp`** [Visualizza](../../../../examples/10-json/model.hpp)
```cpp
#include "../../kinderc.hpp"

using namespace KinderC::Serialization; // Importa le classi necessarie

class Address; // Predefinizione delle classi annidate
class SocialEntry;

class Person : public Serializable {
    public:
        // Eredito i costruttori della classe Serializable
        using Serializable::Serializable;

        // Aggiungo i campi
        // La stringa come secondo parametro serve a indicare il nome
        // del campo JSON
        Field<const char*> Name {this, "name"};
        Field<const char*> Surname {this, "surname"};
        Field<const char*> Thumbnail {this, "thumbnail"};
        Field<Address> Address {this, "address"};
        Field<JSON::TypisedArray<const char*>> Interests {this, "interests"};
        Field<JSON::TypisedArray<SocialEntry>> Socials {this, "socials"};
};

class Address : public Serializable {
    public:
        using Serializable::Serializable;

        Field<const char*> Address {this, "address"};
        Field<const char*> City {this, "city"};
        Field<const char*> PostalCode {this, "postalCode"};
};

class SocialEntry : public Serializable {
    public:
        using Serializable::Serializable;

        Field<const char*> Name {this, "name"};
        Field<const char*> Link {this, "link"};
        Field<const char*> Image {this, "img"};
};
```

Un'esempio del genere potrebbe mappare l'oggetto seguente:
```json
{
    "name": "John",
    "surname": "Gwin",
    "thumbnail": "../images/tb1.png",
    "address": {
        "address":"4295 Monroe Street",
        "city":"Houston",
        "postalCode":"77021"
    },
    "interests": ["Tennis", "Football"],
    "socials": [
        {
            "name":"Instagram", 
            "link":"https://www.instagram.com/testaccount", 
            "img":"fonts/awbTIfYNeoMZ.svg"
        }
    ]
}
```

## Serializzare un oggetto qualunque

La libreria vi consente, dato un oggetto di qualunque tipo che eredita da `Serializable` in maniera simile alle classi riportate sopra, di serializzarlo in formato JSON. Questo processo può essere utile, ad esempio, per inviare dati a un server.

Viene fornito un esempio che mostra come serializzare un oggetto di tipo `Person` con alcuni campi.

#### **`json-serialization.html`** [Visualizza](../../../../examples/10-json/json-serialization.html) *(Omesso in quanto senza contenuto nel body)*

#### **`json-serialization.cpp`** [Visualizza](../../../../examples/10-json/json-serialization.cpp)

```cpp
#include "model.hpp"

int main() {
    Person p1;
    Address addr;
    SocialEntry test;
    test.Image = "https://test.com/image.png";
    test.Name = "Facebook";
    test.Destroyable = false;

    addr.Address = "Test Address";
    addr.PostalCode = "1234";

    p1.Name = "Lorenzo";
    p1.Surname = "Rossi";
    p1.Address = addr;
    p1.Interests = {"Basket", "Programming", "C++"};
    p1.Socials = {test};

    document << "<pre id='jsonContainer'></pre>";
    $("#jsonContainer") << JSON::SerializeObject(p1, true);
}
```

Il codice produrrà un output simile al seguente:
```json
{
	"name" : "Lorenzo",
	"surname" : "Rossi",
	"thumbnail" : null,
	"address" : {
		"address" : "Test Address",
		"city" : null,
		"postalCode" : "1234"
	},
	"interests" : ["Basket", "Programming", "C++"],
	"socials" : [{"name":"Facebook","link":null,"img":"https://test.com/image.png"}]
}
```

## Deserializzare un oggetto qualunque

In maniera uguale e contraria alla serializzazione, è possibile deserializzare una stringa JSON in un oggetto.

In questo esempio, il file `example.json` viene letto e successivamente deserializzato dal parser.

#### **`example.json`** [Visualizza](../../../../examples/10-json/example.json) 
#### **`json-deserialization.html`** [Visualizza](../../../../examples/10-json/json-deserialization.html) *(Omesso in quanto senza contenuto nel body)*

#### **`json-deserialization.cpp`** [Visualizza](../../../../examples/10-json/json-deserialization.cpp)

```cpp
int main() {
    const char* _FPATH = "./example.json";

    fetch(_FPATH).then([](Response& resp) {
        Person p = JSON::DeserializeObjectAs<Person>(resp.Text());
        Address addr = p.Address;
        JSON::TypisedArray<SocialEntry> socials = p.Socials;

        printf("<h2>%s %s</h2>", p.Name.Get(), p.Surname.Get());
        printf("%s, <b>%s</b><br><br>", addr.Address.Get(), addr.City.Get());

        for(SocialEntry sc : socials) {
            printf("<a href='%s'>%s</a><br>", sc.Link.Get(), sc.Name.Get());
        }

        printf("<br>Interessi: ");

        for(const char* intr : p.Interests.Get()) {
            printf("<b>%s</b>; ", intr);
        }
    });
}
```