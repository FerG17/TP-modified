#pragma once
#include <iostream>
#include <fstream>

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

    // Serialización para guardar en archivo
    void guardar(std::ofstream& out) const {
        out << numero << " " << disponible << "\n";
    }

    // Deserialización para cargar desde archivo
    void cargar(std::ifstream& in) {
        int disp;
        in >> numero >> disp;
        disponible = (disp != 0);
    }
};
