#pragma once
#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "Persona.h"
#include "Compra.h"
#include "Lista.h"
using namespace std;

class Compra;

class Cliente : public Persona {
private:
    string direccion;
    string fechaRegistro;
    int puntosLealtad;
    vector<Compra> compras;
    string dni;
	Lista<int> historialCompras; // Guarda IDs de compras realizadas

public:
    Cliente()
        : Persona(), direccion(""), fechaRegistro(""), puntosLealtad(0), dni("") {
        time_t now = time(0);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now));
        fechaRegistro = fecha;
    }

    Cliente(int _id, string _dni, string _nombre, string _apellido, string _email, string _telefono, string _direccion)
        : Persona(_id, _nombre, _apellido, _email, _telefono), direccion(_direccion), puntosLealtad(0), dni(_dni) {
        time_t now = time(0);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now));
        fechaRegistro = fecha;
    }
    string getDNI() const { return dni; }
    void setDNI(const string& _dni) { dni = _dni; }
    string getDireccion() const { return direccion; }
    string getFechaRegistro() const { return fechaRegistro; }
    int getPuntosLealtad() const { return puntosLealtad; }
    void setDireccion(string _direccion) { direccion = _direccion; }
    void setFechaRegistro(string _fecha) { fechaRegistro = _fecha; }
    void setPuntosLealtad(int _puntos) { puntosLealtad = _puntos; }
    void aumentarPuntos(int puntos) {
        puntosLealtad += puntos;
    }
    void guardar(ofstream& archivo) const {
        archivo << id << "," << dni << "," << nombre << "," << apellido << "," << email << "," << telefono << ",";
        archivo << direccion << "," << fechaRegistro << "," << puntosLealtad << "," << compras.size() << endl;
        for (const Compra& c : compras) c.guardar(archivo);
    }
    bool canjearPuntos(int puntos) {
        if (puntosLealtad >= puntos) {
            puntosLealtad -= puntos;
            return true;
        }
        return false;
    }
    void agregarCompraAlHistorial(int compraId) {
        historialCompras.insertarFinal(compraId);
    }
    Lista<int>& obtenerHistorialCompras() {
        return historialCompras;
    }

    const Lista<int>& obtenerHistorialCompras() const {
        return historialCompras;
    }

    double calcularTotalCompras(Lista<Compra>& compras, size_t index = 0) const;
    void guardarEnArchivo(ofstream& archivo) const {
        archivo << id << "," << nombre << "," << apellido << "," << email << "," << telefono << ",";
        archivo << direccion << "," << fechaRegistro << "," << puntosLealtad << ",";
        archivo << historialCompras.tamaño();
        for (size_t i = 0; i < historialCompras.tamaño(); i++) {
            int valor = historialCompras.obtener(i);
            archivo << "," << valor;
        }
        archivo << endl;
    }
    static Cliente cargarDesdeArchivo(ifstream& archivo) {
        string linea;
        Cliente cliente;
        if (!getline(archivo, linea) || linea.empty()) return cliente;
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ','); cliente.id = stoi(campo);
        getline(ss, cliente.dni, ',');
        getline(ss, cliente.nombre, ',');
        getline(ss, cliente.apellido, ',');
        getline(ss, cliente.email, ',');
        getline(ss, cliente.telefono, ',');
        getline(ss, cliente.direccion, ',');
        getline(ss, cliente.fechaRegistro, ',');
        getline(ss, campo, ','); cliente.puntosLealtad = stoi(campo);
        getline(ss, campo, ',');
        int cantCompras = stoi(campo);
        for (int i = 0; i < cantCompras; ++i) {
            Compra compra;
            if (compra.cargar(archivo))
                cliente.compras.push_back(compra);
        }
        return cliente;
    }
    //RECURSIVIDAD
    void mostrarDetalles(int nivel = 0) const {
        if (nivel == 0) {
            cout << "Detalles de Cliente:" << endl;
            cout << "ID: " << id << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 1) {
            cout << "Nombre completo: " << getNombreCompleto() << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 2) {
            cout << "Email: " << email << " | Telefono: " << telefono << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 3) {
            cout << "Direccion: " << direccion << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 4) {
            cout << "Fecha de registro: " << fechaRegistro << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 5) {
            cout << "Puntos de lealtad: " << puntosLealtad << endl;
            mostrarDetalles(nivel + 1);
        }
    }
    void sumarPuntos(int puntos) {
        puntosLealtad += puntos;
    }
    void agregarCompra(const Compra& compra) { compras.push_back(compra); }
    Compra& getCompra() {
        if (compras.empty()) compras.emplace_back(id, "Pendiente");
        return compras.back();
    }
    const vector<Compra>& getCompras() const { return compras; }

    friend ostream& operator<<(ostream& os, const Cliente& cliente) {
        os << "Cliente [" << cliente.id << "]: " << cliente.getNombreCompleto()
            << " | Puntos: " << cliente.puntosLealtad;
        return os;
    }
};

#endif
