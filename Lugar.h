#pragma once
#include <string>
#include "SeccionLugar.h"

using namespace std;

class Lugar {
private:
    string nombre;
    SeccionLugar principal;
    SeccionLugar general;
    SeccionLugar vip;
public:
    Lugar(const string& nombre, int asientosPrincipal, int asientosGeneral, int asientosVIP)
        : nombre(nombre), principal("Principal", asientosPrincipal),
        general("General", asientosGeneral), vip("VIP Gold", asientosVIP) {
    }

    // Getters para secciones
    SeccionLugar& getPrincipal() { return principal; }
    SeccionLugar& getGeneral() { return general; }
    SeccionLugar& getVIP() { return vip; }
};
