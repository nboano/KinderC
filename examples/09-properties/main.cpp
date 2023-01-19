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