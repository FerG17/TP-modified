#pragma once
#include "Evento.h"

class Festival : public Evento {
private:
    int diasDuracion;
    string categoria;

public:
    Festival(const string& nombre, const string& fecha, const string& lugar, double precio,
        int dias, const string& cat,
        int asientosPrincipal = 10, int asientosGeneral = 10, int asientosVIP = 5)
        : Evento(nombre, fecha, lugar, precio, asientosPrincipal, asientosGeneral, asientosVIP),
        diasDuracion(dias), categoria(cat) {
    }

    void mostrar(int x =45, int y=18) const override {
        cout << "\n   |   Festival: " << nombre << endl;
        cout << "   |   Categoria: " << categoria << endl;
        cout << "   |   Duracion: " << diasDuracion << " dias" << endl;
        cout << "   |   Fecha: " << fecha << endl;
        cout << "   |   Lugar: " << lugar << endl;
        cout << "   |   Precio: S/." << precio << "\n" << endl;
    }
};
