#pragma once
#include "Lista.h"
#include "Evento.h"
#include <stack>
#include <fstream>
#include <iostream>

class GestorEventos {
private:
    Lista<Evento*> eventos;
    stack<Evento*> historial;
public:
    Lista<Evento*>& getEventos();
    void agregarEvento(Evento* e);
    void mostrarEventos();
    Evento* buscarPorMes(const string& mes);
    Evento* buscarPorId(int id);
    void historialPush(Evento* e);
    void historialPop();
    bool historialVacio() const;
    void guardarAsientosEventos(const string& archivo) const;
    ~GestorEventos();
};

Lista<Evento*>& GestorEventos::getEventos() {
    return eventos;
}
void GestorEventos::agregarEvento(Evento* e) {
    eventos.insertarOrdenado(e, [](Evento* a, Evento* b) {
        return a->getFecha() < b->getFecha();
        });
}
void GestorEventos::mostrarEventos() {
    eventos.forEach([](Evento* e) { e->mostrar(); });
}
Evento* GestorEventos::buscarPorMes(const string& mes) {
    return eventos.buscar([mes](Evento* e) {
        return e->getFecha().substr(5, 2) == mes;
        });
}
Evento* GestorEventos::buscarPorId(int id) {
    return eventos.buscar([id](Evento* e) {
        return e->getId() == id;
        });
}
void GestorEventos::historialPush(Evento* e) {
    historial.push(e);
}
void GestorEventos::historialPop() {
    if (!historial.empty()) {
        Evento* e = historial.top();
        historial.pop();
        cout << "Evento retirado del historial: ";
        e->mostrar();
    }
    else {
        cout << "Historial vacio." << endl;
    }
}
bool GestorEventos::historialVacio() const {
    return historial.empty();
}
void GestorEventos::guardarAsientosEventos(const string& archivo) const {
    ofstream out(archivo);
    if (!out) {
        cerr << "Error al abrir archivo para guardar asientos." << endl;
        return;
    }
    eventos.forEach([&out](Evento* e) { e->guardarAsientos(out); });
    out.close();
}
GestorEventos::~GestorEventos() {
    eventos.forEach([](Evento*& e) {
        delete e;
        e = nullptr;
        });
}
