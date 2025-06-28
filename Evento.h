#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "SeccionLugar.h"

using namespace std;

class Evento {
protected:
    static int nextId;
    int id;
    string nombre;
    string fecha;
    string lugar;
    double precio;
    SeccionLugar seccionPrincipal;
    SeccionLugar seccionGeneral;
    SeccionLugar seccionVIP;
public:
    Evento()
        : id(nextId++), nombre(""), fecha(""), lugar(""), precio(0.0),
          seccionPrincipal("Principal", 10),
          seccionGeneral("General", 10),
          seccionVIP("VIP Gold", 5) {}

    Evento(const string& nombre, const string& fecha, const string& lugar, double precio,
           int asientosPrincipal = 10, int asientosGeneral = 10, int asientosVIP = 5)
        : id(nextId++), nombre(nombre), fecha(fecha), lugar(lugar), precio(precio),
          seccionPrincipal("Principal", asientosPrincipal),
          seccionGeneral("General", asientosGeneral),
          seccionVIP("VIP Gold", asientosVIP) {}

    virtual ~Evento() {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getFecha() const { return fecha; }
    string getLugar() const { return lugar; }
    double getPrecio() const { return precio; }

    SeccionLugar* getSeccionPrincipal() { return &seccionPrincipal; }
    SeccionLugar* getSeccionGeneral() { return &seccionGeneral; }
    SeccionLugar* getSeccionVIP() { return &seccionVIP; }

    // Para compatibilidad con código antiguo
    SeccionLugar* getSeccion() { return &seccionPrincipal; }

    // Mostrar información del evento
    virtual void mostrar(int x = 45, int y = 18) const {
        gotoxy(x, y++); cout << "ID: " << id << endl;
        gotoxy(x, y++); cout << "Nombre: " << nombre << endl;
        gotoxy(x, y++); cout << "Fecha:  " << fecha << endl;
        gotoxy(x, y++); cout << "Lugar:  " << lugar << endl;
        gotoxy(x, y++); cout << "Precio base: S/ " << precio << endl;
    }

    // Guardar evento y sus asientos
    virtual void guardarEvento(ofstream& out) const {
        out << id << " " << nombre << " " << fecha << " " << lugar << " " << precio << endl;
        seccionPrincipal.guardarAsientos(out);
        seccionGeneral.guardarAsientos(out);
        seccionVIP.guardarAsientos(out);
    }

    // Cargar evento y sus asientos
    virtual void cargarEvento(ifstream& in) {
        in >> id >> nombre >> fecha >> lugar >> precio;
        seccionPrincipal.cargarAsientos(in);
        seccionGeneral.cargarAsientos(in);
        seccionVIP.cargarAsientos(in);
        if (id >= nextId) nextId = id + 1;
    }

    // Buscar asiento por sección y número
    Asiento* buscarAsiento(int seccion, int numero) {
        if (seccion == 1) return seccionPrincipal.buscarAsientoPorNumero(numero);
        else if (seccion == 2) return seccionGeneral.buscarAsientoPorNumero(numero);
        else if (seccion == 3) return seccionVIP.buscarAsientoPorNumero(numero);
        return nullptr;
    }
};

// Inicialización de variable estática
int Evento::nextId = 1;
