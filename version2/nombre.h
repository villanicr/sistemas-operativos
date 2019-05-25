// Inspirado en la clase Mensaje de "n productores y m consumidores".
#include <string>
#include <cstring>

#ifndef NOMBRE_H
#define NOMBRE_H

using namespace std;
class Nombre {
    char dato[40];

public:
    Nombre() {
        strcpy(dato, "");
    }

    Nombre(string d) {
        strcpy(dato, d.c_str());
    }

    Nombre(const Nombre &m) {
        strcpy(dato, m.dato);
    }

    string get_nombre() {
        return dato;
    };

    friend ostream &operator<<(ostream &os, Nombre nombre) {
        return os << nombre.get_nombre();
    }
};

#endif
