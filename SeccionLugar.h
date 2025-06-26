#pragma once
#include <iostream>
#include <fstream>
#include "Asiento.h"
#include <conio.h>

using namespace std;

// Declaración para evitar advertencias del compilador, la implementación real la proporciona <conio.h>
void gotoxy(int x, int y);

class SeccionLugar {
private:
    string nombre;
    Asiento* asientos;
    int cantidadAsientos;
public:
    SeccionLugar() : nombre(""), asientos(nullptr), cantidadAsientos(0) {}

    SeccionLugar(const string& nombre, int cantidadAsientos)
        : nombre(nombre), cantidadAsientos(cantidadAsientos) {
        asientos = new Asiento[cantidadAsientos];
        for (int i = 0; i < cantidadAsientos; ++i)
            asientos[i] = Asiento(i + 1);
    }

    // Constructor de copia
    SeccionLugar(const SeccionLugar& otra)
        : nombre(otra.nombre), cantidadAsientos(otra.cantidadAsientos) {
        asientos = new Asiento[cantidadAsientos];
        for (int i = 0; i < cantidadAsientos; ++i)
            asientos[i] = otra.asientos[i];
    }

    // Operador de asignación
    SeccionLugar& operator=(const SeccionLugar& otra) {
        if (this != &otra) {
            delete[] asientos;
            nombre = otra.nombre;
            cantidadAsientos = otra.cantidadAsientos;
            asientos = new Asiento[cantidadAsientos];
            for (int i = 0; i < cantidadAsientos; ++i)
                asientos[i] = otra.asientos[i];
        }
        return *this;
    }

    ~SeccionLugar() {
        delete[] asientos;
    }

    string getNombre() const { return nombre; }
    int getCantidadAsientos() const { return cantidadAsientos; }

    void mostrarAsientos(int x = 45, int y = 18) const {
        for (int i = 0; i < cantidadAsientos; ++i) {
            gotoxy(x, y + i);
            cout << "Asiento [" << asientos[i].getNumero() << "] "
                << (asientos[i].estaDisponible() ? "Disponible" : "Ocupado") << endl;
        }
    }

    void mostrarAsientosDisponibles(int x = 45, int y = 18) const {
        int line = 0;
        for (int i = 0; i < cantidadAsientos; ++i) {
            if (asientos[i].estaDisponible()) {
                gotoxy(x, y + line++);
                cout << "Asiento [" << asientos[i].getNumero() << "] Disponible" << endl;
            }
        }
        if (line == 0) {
            gotoxy(x, y);
            cout << "No hay asientos disponibles en esta seccion." << endl;
        }
    }

    Asiento* buscarAsientoPorNumero(int num) {
        for (int i = 0; i < cantidadAsientos; ++i) {
            if (asientos[i].getNumero() == num)
                return &asientos[i];
        }
        return nullptr;
    }

    Asiento* getAsientos() { return asientos; }
    const Asiento* getAsientos() const { return asientos; }

    // Guardar asientos de la sección en un archivo
    void guardarAsientos(ofstream& out) const {
        out << nombre << " " << cantidadAsientos << endl;
        for (int i = 0; i < cantidadAsientos; ++i)
            asientos[i].guardar(out);
    }

    // Cargar asientos de la sección desde un archivo
    void cargarAsientos(ifstream& in) {
        in >> nombre >> cantidadAsientos;
        delete[] asientos;
        asientos = new Asiento[cantidadAsientos];
        for (int i = 0; i < cantidadAsientos; ++i)
            asientos[i].cargar(in);
    }
};
