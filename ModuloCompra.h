#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Cliente.h"
#include "Evento.h"

using namespace std;

class ModuloCompra {
private:
    vector<Cliente> clientes;
    vector<int> historialCompras; // Guarda IDs de eventos comprados
    // Referencia al gestor de eventos (puedes pasarla por referencia o puntero en el constructor)
    vector<Evento>* eventosDisponibles;

public:
    ModuloCompra(vector<Evento>* eventos) : eventosDisponibles(eventos) {}

    // Registrar nuevo cliente
    void registrarCliente(const Cliente& cliente) {
        clientes.push_back(cliente);
    }

    // Buscar cliente por DNI
    int buscarClientePorDNI(const string& dni) {
        for (int i = 0; i < clientes.size(); ++i) {
            if (clientes[i].getDNI() == dni) return i;
        }
        return -1;
    }

    // Mostrar eventos disponibles
    void mostrarEventos() {
        for (Evento& evento : *eventosDisponibles) {
            evento.mostrar();
        }
    }

    // Registrar a cliente en un evento
    void registrarseEnEvento() {
        string dni;
        cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            cout << "Usuario no encontrado. Realice el registro primero." << endl;
            return;
        }
        Cliente& cliente = clientes[idx];

        mostrarEventos();
        cout << "Ingrese ID del evento: ";
        int eventoId;
        cin >> eventoId;

        Evento* evento = nullptr;
        for (Evento& e : *eventosDisponibles) {
            if (e.getId() == eventoId) {
                evento = &e;
                break;
            }
        }
        if (!evento) {
            cout << "Evento no encontrado." << endl;
            return;
        }

        cout << "Seleccione sección: 1. Principal | 2. General | 3. VIP Gold: ";
        int seccionOpcion;
        cin >> seccionOpcion;
        SeccionLugar* seccionPtr = nullptr;
        if (seccionOpcion == 1) seccionPtr = evento->getSeccionPrincipal();
        else if (seccionOpcion == 2) seccionPtr = evento->getSeccionGeneral();
        else if (seccionOpcion == 3) seccionPtr = evento->getSeccionVIP();
        else {
            cout << "Opcion de sección invalida." << endl;
            return;
        }

        seccionPtr->mostrarAsientosDisponibles();
        cout << "Ingrese número de asiento: ";
        int asientoNum;
        cin >> asientoNum;
        Asiento* asiento = seccionPtr->buscarAsientoPorNumero(asientoNum);
        if (!asiento || !asiento->estaDisponible()) {
            cout << "Asiento no disponible." << endl;
            return;
        }

        asiento->reservar();
        double precio = evento->getPrecio();
        Entrada entrada(evento->getId(), asiento->getNumero(), precio, evento->getNombre(), seccionPtr->getNombre());
        cliente.getCompra().agregarEntrada(entrada);

        // Sumar puntos de lealtad
        cliente.sumarPuntos(20);
        historialCompras.push_back(evento->getId());
        cout << "Evento y asiento reservados con exito. Puntos actuales: " << cliente.getPuntosLealtad() << endl;
    }

    // Mostrar compras de un cliente
    void mostrarComprasCliente() {
        string dni;
        cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            cout << "Usuario no encontrado." << endl;
            return;
        }
        clientes[idx].getCompra().mostrarEntradas();
    }

    // Guardar clientes y compras en archivo
    void guardarDatos(const string& archivo) {
        ofstream out(archivo);
        for (Cliente& cliente : clientes) {
            cliente.guardar(out);
        }
        out.close();
    }

    // Cargar clientes y compras desde archivo
    void cargarDatos(const string& archivo) {
        ifstream in(archivo);
        clientes.clear();
        while (!in.eof()) {
            Cliente cliente;
            if (!cliente.cargar(in)) break;
            clientes.push_back(cliente);
        }
        in.close();
    }
};
