#pragma once
#include "Evento.h"

class Concierto : public Evento {
private:
    std::string artista;

public:
    Concierto(const std::string& nombre, const std::string& fecha, const std::string& lugar, double precio,
        const std::string& artista,
        int asientosPrincipal = 10, int asientosGeneral = 10, int asientosVIP = 5)
        : Evento(nombre, fecha, lugar, precio, asientosPrincipal, asientosGeneral, asientosVIP),
        artista(artista) {
    }

    void mostrar(int x=45, int y=18) const override {
        std::cout << "\n   |   CONCIERTO: " << nombre << std::endl;
        std::cout << "   |   Artista: " << artista << std::endl;
        std::cout << "   |   Fecha: " << fecha << std::endl;
        std::cout << "   |   Lugar: " << lugar << std::endl;
        std::cout << "   |   Precio: S/." << precio << "\n" << std::endl;
    }
};
