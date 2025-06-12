#pragma once
#include "Evento.h"

class Deporte : public Evento {
private:
    string equipoLocal;
    string equipoVisitante;

public:
    Deporte(const string& nombre, const string& fecha, const string& lugar, double precio,
        const string& local, const string& visitante,
        int asientosPrincipal = 10, int asientosGeneral = 10, int asientosVIP = 5)
        : Evento(nombre, fecha, lugar, precio, asientosPrincipal, asientosGeneral, asientosVIP),
        equipoLocal(local), equipoVisitante(visitante) {
    }

    void mostrar(int x =45, int y =18) const override {
        cout << "\n   |   Partido Deportivo: " << equipoLocal << " vs " << equipoVisitante << endl;
        cout << "   |   Evento: " << nombre << endl;
        cout << "   |   Fecha: " << fecha << endl;
        cout << "   |   Lugar: " << lugar << endl;
        cout << "   |   Precio: S/." << precio << "\n" << endl;
    }
};
