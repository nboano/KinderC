#include "D:\kinderc\kinderc.hpp"

exported void esponenziale(int base, int esponente) {
    long risultato = base;
    for (int i = 0; i < esponente - 1; i++) risultato *= base;

    $("#lblRisultato").innerText = String::Format("%i", risultato);
}

int main() {}
