#include "vehiculo.h"
#include "nombre.h"
#include "Sem-sv/sv_sem.h"

#include <unistd.h>

#ifndef FERRY_H
#define FERRY_H

#define NORTE 0
#define SUR 1

/**
 * Modela al Ferry.
 * @param int capacacidad_maxima: capacidad máxima del ferry.
 * @param int carga_actual: carga actual del ferry.
 * @param int carga_minima: carga mínima total que debe tener el ferry
 *                          antes de zarpar.
 * @param string costa: nombre de la costa en la que está el ferry.
 *                      Puede ser "Norte" o "Sur". Por defecto comienza
 *                      en la costa "Norte".
 */
class Ferry
{

private:
    int capacidad_maxima;
    int carga_minima;
    int carga_actual;
    int orilla_actual;
    int cantidad_de_vehiculos;
    Nombre bodega[100];
    
public:
    Ferry(int capacidad_maxima = 20, int carga_minima = 5);
    void inicializar(int capacidad_maxima = 20, int carga_minima = 5);
    
    bool agregar_vehiculo(Vehiculo vehiculo);
    void liberar_bodega();
    string get_orilla();
    bool finalizar;
    void zarpar();
};

Ferry::Ferry(int capacidad_maxima, int carga_minima)
{
    inicializar(capacidad_maxima, carga_minima);
}

void Ferry::inicializar(int capacidad_maxima, int carga_minima)
{
    this->capacidad_maxima = capacidad_maxima;
    this->carga_minima = carga_minima;
    carga_actual = 0;
    orilla_actual = NORTE;
    cantidad_de_vehiculos = 0;
    finalizar=false;
}

bool Ferry::agregar_vehiculo(Vehiculo vehiculo)
{
    // Obtengo el semaforo correspondiente al origen del vehiculo y espero.
    sv_sem semaforo(vehiculo.get_origen());
    cout << vehiculo.get_nombre() << " espera para entrar al ferry en la orilla " << vehiculo.get_origen() << "..." << endl;
    semaforo.wait();

    // El vehiculo entró al ferry, asi que lo agrego a la bodega.
    cout << vehiculo.get_nombre() << " entró al ferry." << endl;
    bodega[cantidad_de_vehiculos] = vehiculo.get_nombre();
    cantidad_de_vehiculos++;
    carga_actual += vehiculo.get_peso();

    if (carga_actual >= carga_minima)
    {
        // El ferry puede zarpar -> se despierta al ferry.
        sv_sem("/Ferry").post();
    }
    else
    {
        // Dejo que entre otro vehiculo.
        cout << "La carga actual del ferry es " << carga_actual << ". Zarpará cuando iguale o supere " << carga_minima << "." << endl;
        semaforo.post();
    }
}

/**
 * @return string: devuelve la orilla en la que se encuentra el ferry.
 */
string Ferry::get_orilla()
{
    if (orilla_actual == NORTE)
    {
        return "Norte";
    }
    else
    {
        return "Sur";
    }
}

/**
 * Hace zarpar al ferry. Luego al llegar a la orilla libera los vehiculos.
 */
void Ferry::zarpar()
{
    // Cambio la orilla actual.
    cout << "El ferry va a zarpar desde la orilla " << get_orilla() << "!" << endl;
    if (orilla_actual == NORTE)
    {
        orilla_actual = SUR;
    }
    else
    {
        orilla_actual = NORTE;
    }

    // Countdown para simular el viaje.
    for (int i = 5; i >= 1; i--)
    {
        cout << "Arribo a la orilla " << get_orilla() << " en " << i << " segundo(s)" << endl;
        usleep(1000000);
    }

    // Libero la bodega al llegar.
    cout << "El ferry arribó a la orilla " << get_orilla() << "!" << endl;
    liberar_bodega();

    // Por último, realizo un post en la orilla a la que llegué para
    // que entren vehículos.
    sv_sem(get_orilla()).post();
}

/**
 * Libera la bodega haciendo post en los vehiculos y reinicializando
 * cantidad_de_vehiculos y carga_actual.
 */
void Ferry::liberar_bodega()
{
    for (int i = 0; i < cantidad_de_vehiculos; ++i)
    {
        cout << "Liberando vehiculo " << bodega[i] << endl;
        sv_sem(bodega[i].get_nombre()).post();
    }
    cantidad_de_vehiculos = carga_actual = 0;
}

#endif