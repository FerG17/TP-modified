#pragma once
#include "Evento.h"

class ObraTeatral : public Evento {
private:
    string director;
    int duracionMin;

public:
    // Constructor compatible con el de Evento
    ObraTeatral(const string& nombre, const string& fecha, const string& lugar, double precio,
        const string& director, int duracion,
        int asientosPrincipal = 10, int asientosGeneral = 10, int asientosVIP = 5)
        : Evento(nombre, fecha, lugar, precio, asientosPrincipal, asientosGeneral, asientosVIP),
        director(director), duracionMin(duracion) {
    }

    void mostrar(int x=45, int y = 18) const override {
        cout << "\n   |   Obra Teatral: " << nombre << endl;
        cout << "   |   Director: " << director << endl;
        cout << "   |   Duracion: " << duracionMin << " min" << endl;
        cout << "   |   Fecha: " << fecha << endl;
        cout << "   |   Lugar: " << lugar << endl;
        cout << "   |   Precio: S/." << precio << "\n" << endl;
    }
};
