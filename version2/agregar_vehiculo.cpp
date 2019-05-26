#include "ferry.h"
#include "vehiculo.h"
#include "Sem-sv/sv_shm.h"
#include "Sem-sv/sv_sem.h"

using namespace std;
int main(int argc, char const *argv[]) {
    // Valido la cantidad de argumentos
    if (argc != 4) {
        cout << "No se recibieron los parámetros del vehículo necesarios." << endl;
        cout << "El uso es: ./agregar_vehiculo $nombre_unico(string) $peso(int > 0) $origen(Norte o Sur)." << endl;
        return 1;
    }

    // Valido el peso
    try {
        int peso = stoi(string(argv[2]));
        if (peso < 1)
            throw invalid_argument("");
    } catch (exception const &e) {
        cout << "error: " << argv[2] << " no es un peso válido. Debe ser un número mayor que cero." << endl;
        return 1;
    }

    // Valido el origen
    if (strcmp(argv[3], "Norte") != 0 && strcmp(argv[3], "Sur") != 0) {
        cout << "error: el origen debe ser Norte o Sur, no " << argv[3] << "." << endl;
        return 1;
    }

    // Busco el ferry.
    sv_shm mem_comp("/Ferry");
    Ferry *ptero_ferry;
    ptero_ferry = reinterpret_cast<Ferry *>(mem_comp.map(sizeof(Ferry)));

    // Agrego el auto al ferry.
    Vehiculo vehiculo(argv[1], atoi(argv[2]), argv[3]);
    ptero_ferry->agregar_vehiculo(vehiculo);

    // Elimino el semaforo luego de cruzar.
    cout << "Se liberó el vehiculo " << vehiculo.get_nombre() << endl;
    sv_sem (vehiculo.get_nombre()).del();

    return 0;
}