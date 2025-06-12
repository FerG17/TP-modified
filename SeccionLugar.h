#pragma once
#include <iostream>
#include "Asiento.h"
#include "conio.h"

using namespace std;

class SeccionLugar {
private:
    string nombre;
    Asiento* asientos;
    int cantidadAsientos;
public:
    SeccionLugar() : nombre(""), asientos(NULL), cantidadAsientos(0) {}

    SeccionLugar(const string& nombre, int cantidadAsientos)
        : nombre(nombre), cantidadAsientos(cantidadAsientos) {
        asientos = new Asiento[cantidadAsientos];
        for (int i = 0; i < cantidadAsientos; ++i)
            asientos[i] = Asiento(i + 1);
    }

    ~SeccionLugar() {
        if (asientos != NULL) delete[] asientos;
    }

    string getNombre() const { return nombre; }
    int getCantidadAsientos() const { return cantidadAsientos; }

    void mostrarAsientos(int x = 45, int y = 18) const {
        for (int i = 0; i < cantidadAsientos; ++i) {
            gotoxy(x, y + i);
            cout << "Asiento [" << asientos[i].getNumero() << "] "
                << (asientos[i].estaDisponible() ? "Disponible" : "Ocupado");
        }
    }

    void mostrarAsientosDisponibles(int x = 45, int y = 18) const {
        int line = 0;
        for (int i = 0; i < cantidadAsientos; ++i) {
            if (asientos[i].estaDisponible()) {
                gotoxy(x, y + line++);
                cout << "Asiento [" << asientos[i].getNumero() << "] Disponible";
            }
        }
        if (line == 0) {
            gotoxy(x, y);
            cout << "No hay asientos disponibles en esta seccion.";
        }
    }

    Asiento* buscarAsientoPorNumero(int num) {
        for (int i = 0; i < cantidadAsientos; ++i) {
            if (asientos[i].getNumero() == num)
                return &asientos[i];
        }
        return NULL;
    }

    Asiento* getAsientos() { return asientos; }
    const Asiento* getAsientos() const { return asientos; }
};
