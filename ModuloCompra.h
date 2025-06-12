#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cliente.h"
#include "Compra.h"
#include "GestorEventos.h"
#include "ModuloUtils.h"

class ModuloCompra {
    GestorEventos& gestorEventos;
    vector<Cliente>& clientes;
public:
    ModuloCompra(GestorEventos& gestor, vector<Cliente>& clientesRef)
        : gestorEventos(gestor), clientes(clientesRef) {}

    void ejecutar() {
        int opcion;
        do {
            limpiarYCentrarPantalla();
            mostrarTituloModulo("MODULO USUARIOS Y COMPRAS");
            int y = 50;
            gotoxy(45, y++); cout << "1. Registrar usuario";
            gotoxy(45, y++); cout << "2. Registrarse en un evento";
            gotoxy(45, y++); cout << "3. Mostrar compras";
            gotoxy(45, y++); cout << "4. Consultar precios";
            gotoxy(45, y++); cout << "5. Consultar puntos de lealtad";
            gotoxy(45, y++); cout << "6. Ver detalles del cliente";
            gotoxy(45, y++); cout << "7. Imprimir entradas";
            gotoxy(45, y++); cout << "0. Volver al menu principal";
            gotoxy(45, y++); cout << "Opcion: ";
            gotoxy(53, y - 1); cin >> opcion;
            system("cls");

            switch (opcion) {
            case 1:
                registrarUsuario();
                break;
            case 2:
                registrarseEnEvento();
                break;
            case 3:
                mostrarCompras();
                break;
            case 4:
                consultarPrecios();
                break;
            case 5:
                consultarPuntosLealtad();
                break;
            case 6:
                verDetallesCliente();
                break;
            case 7:
                imprimirEntradas();
                break;
            case 0:
                gotoxy(45, 30); cout << "Saliendo del modulo de usuarios y compras...";
                break;
            default:
                gotoxy(45, 30); cout << "Opcion invalida.";
                pausarContinuar();
            }
        } while (opcion != 0);
    }

private:
    int buscarClientePorDNI(const string& dni) {
        for (size_t i = 0; i < clientes.size(); ++i) {
            if (clientes[i].getDNI() == dni) return static_cast<int>(i);
        }
        return -1;
    }

    void registrarUsuario() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("REGISTRO DE USUARIO");
        string dni, nombre, apellido, email, telefono, direccion;
        gotoxy(45, 20); cout << "DNI: "; cin >> dni;
        gotoxy(45, 21); cout << "Nombre: "; cin >> nombre;
        gotoxy(45, 22); cout << "Apellido: "; cin >> apellido;
        gotoxy(45, 23); cout << "Email: "; cin >> email;
        gotoxy(45, 24); cout << "Telefono: "; cin >> telefono;
        gotoxy(45, 25); cout << "Direccion: "; cin >> direccion;

        if (buscarClientePorDNI(dni) != -1) {
            gotoxy(45, 27); cout << "El usuario ya existe.";
        } else {
            clientes.emplace_back(dni, nombre, apellido, email, telefono, direccion);
            gotoxy(45, 27); cout << "Usuario registrado correctamente.";
        }
        pausarContinuar();
    }

    void registrarseEnEvento() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("REGISTRO EN EVENTO");
        string dni;
        gotoxy(45, 18); cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            gotoxy(45, 20); cout << "Usuario no encontrado. Realice el registro primero.";
            pausarContinuar();
            return;
        }
        Cliente& cliente = clientes[idx];
        Compra& compra = cliente.getCompra();

        // Mostrar eventos disponibles con ID
        limpiarYCentrarPantalla();
        mostrarTituloModulo("EVENTOS DISPONIBLES");
        gestorEventos.mostrarEventos();
        gotoxy(45, 25); cout << "Ingrese ID del evento: ";
        int eventoId;
        cin >> eventoId;
        Evento* evento = gestorEventos.buscarPorId(eventoId);
        if (!evento) {
            gotoxy(45, 27); cout << "Evento no encontrado.";
            pausarContinuar();
            return;
        }

        // Elegir sección
        gotoxy(45, 27); cout << "Seleccione sección: 1. Principal | 2. General | 3. VIP Gold: ";
        int seccionOpcion;
        cin >> seccionOpcion;
        SeccionLugar* seccionPtr = nullptr;
        if (seccionOpcion == 1) seccionPtr = evento->getSeccion();
        else if (seccionOpcion == 2) seccionPtr = evento->getSeccionGeneral();
        else if (seccionOpcion == 3) seccionPtr = evento->getSeccionVIP();
        else {
            gotoxy(45, 29); cout << "Opcion de sección invalida.";
            pausarContinuar();
            return;
        }

        // Mostrar asientos disponibles
        limpiarYCentrarPantalla();
        mostrarTituloModulo("ASIENTOS DISPONIBLES");
        seccionPtr->mostrarAsientosDisponibles(45, 18);
        gotoxy(45, 30); cout << "Ingrese número de asiento: ";
        int asientoNum;
        cin >> asientoNum;
        Asiento* asiento = seccionPtr->buscarAsientoPorNumero(asientoNum);
        if (!asiento || !asiento->estaDisponible()) {
            gotoxy(45, 32); cout << "Asiento no disponible.";
            pausarContinuar();
            return;
        }

        asiento->reservar();
        double precio = evento->getPrecio();
        Entrada entrada(evento->getId(), asiento->getNumero(), precio, evento->getNombre(), seccionPtr->getNombre());
        compra.agregarEntrada(entrada);

        cliente.sumarPuntos(20);
        gotoxy(45, 34);
        setColor(VERDE_CLARO, COLOR_FONDO);
        cout << "Evento y asiento reservados con exito. Puntos actuales: " << cliente.getPuntosLealtad();
        setColor(BLANCO, COLOR_FONDO);
        pausarContinuar();
    }

    void mostrarCompras() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("COMPRAS DEL USUARIO");
        string dni;
        gotoxy(45, 18); cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            gotoxy(45, 20); cout << "Usuario no encontrado.";
            pausarContinuar();
            return;
        }
        clientes[idx].getCompra().mostrarEntradas();
        pausarContinuar();
    }

    void consultarPrecios() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("CONSULTA DE PRECIOS");
        string dni;
        gotoxy(45, 18); cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            gotoxy(45, 20); cout << "Usuario no encontrado.";
            pausarContinuar();
            return;
        }
        double total = clientes[idx].getCompra().calcularTotal();
        gotoxy(45, 20); cout << "Total a pagar: S/ " << total;
        pausarContinuar();
    }

    void consultarPuntosLealtad() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("PUNTOS DE LEALTAD");
        string dni;
        gotoxy(45, 18); cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            gotoxy(45, 20); cout << "Usuario no encontrado.";
            pausarContinuar();
            return;
        }
        gotoxy(45, 20); cout << "Puntos de lealtad: " << clientes[idx].getPuntosLealtad();
        pausarContinuar();
    }

    void verDetallesCliente() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("DETALLES DEL CLIENTE");
        string dni;
        gotoxy(45, 18); cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            gotoxy(45, 20); cout << "Usuario no encontrado.";
            pausarContinuar();
            return;
        }
        clientes[idx].mostrar();
        pausarContinuar();
    }

    void imprimirEntradas() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("IMPRIMIR ENTRADAS");
        string dni;
        gotoxy(45, 18); cout << "Ingrese su DNI: "; cin >> dni;
        int idx = buscarClientePorDNI(dni);
        if (idx == -1) {
            gotoxy(45, 20); cout << "Usuario no encontrado.";
            pausarContinuar();
            return;
        }
        clientes[idx].getCompra().imprimirEntradas();
        pausarContinuar();
    }
};
