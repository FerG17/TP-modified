#pragma once
#include <iostream>
#include "conio.h"
using namespace std;

class Asiento {
private:
    int numero;
    bool disponible;
public:
    Asiento() : numero(0), disponible(true) {}
    Asiento(int numero) : numero(numero), disponible(true) {}

    int getNumero() const { return numero; }
    bool estaDisponible() const { return disponible; }
    void reservar() { disponible = false; }
    void liberar() { disponible = true; }
};
