#pragma once
#include "Evento.h"
#include <string>
using namespace std;

class ObraTeatral : public Evento {
private:
    string director;
public:
    ObraTeatral(const string& nombre, const string& fecha, const string& lugar, double precio,
        const string& director, int asientosPrincipal = 10, int asientosGeneral = 10, int asientosVIP = 5)
        : Evento(nombre, fecha, lugar, precio, asientosPrincipal, asientosGeneral, asientosVIP),
        director(director) {
    }

    void mostrar(int x = 45, int y = 18) const override {
        Evento::mostrar(x, y);
        cout << "Director: " << director << endl;
    }
};
