#include "Sem-sv/sv_sem.h"
#include "nombre.h"

#ifndef VEHICULO_H
#define VEHICULO_H

/**
 * Modela al Vehiculo.
 * @param string nombre: nombre del vehículo. No debe haber dos vehiculos con el mismo
 *  nombre para que funcionen correctamente los semáforos.
 * @param int peso: peso del vehículo.
 * @param string origen: orilla desde la que parte el vehículo. Puede ser Norte o Sur.
 */
using namespace std;
class Vehiculo
{

private:
    Nombre nombre;
    int peso;
    string origen;

public:
    Vehiculo(string nombre = "vehiculo1", int peso = 1, string origen = "Norte") {
        this->nombre = nombre;
        this->peso = peso;
        this->origen = origen;
    }

    int get_peso() {
        return peso;
    }

    string get_nombre() {
        return nombre.get_nombre();
    }

    string get_origen() {
        return origen;
    }

    friend ostream &operator<<(ostream &os, Vehiculo vehiculo) {
        return os << vehiculo.get_nombre();
    }
};

#endif