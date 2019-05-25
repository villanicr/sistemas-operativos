#include "Sem-sv/sv_sem.h"
#include "Sem-sv/sv_shm.h"
#include "ferry.h"

using namespace std;
int main(int argc, char const *argv[]) {
    
    // Valido la cantidad de argumentos
    if (argc != 3) {
        cout << "No se recibieron los parámetros del ferry necesarios." << endl;
        cout << "El uso es: ./ferry $capacidad_maxima(int > 0) $carga_minima_para_zarpar(0 < int < $capacidad_maxima)." << endl;
        return 1;
    }

    // Valido capacidad_maxima.
    int capacidad_maxima;
    try {
        capacidad_maxima = stoi(string(argv[1]));
        if (capacidad_maxima < 1)
            throw invalid_argument("");
    } catch (exception const &e) {
        cout << "error: " << argv[1] << " no es una capacidad máxima válida. Debe ser un número mayor que cero." << endl;
        return 1;
    }

    // Valido carga_minima_para_zarpar.
    int carga_minima_para_zarpar;
    try {
        carga_minima_para_zarpar = stoi(string(argv[2]));
        if (carga_minima_para_zarpar < 1 || carga_minima_para_zarpar >= capacidad_maxima)
            throw invalid_argument("");
    } catch (exception const &e) {
        cout << "error: " << argv[2] << " no es una carga minima para zarpar válida. Debe ser un número mayor que cero y menor que la capacidad máxima." << endl;
        return 1;
    }

    // Inicio el ferry en el área compartida.
    sv_shm mem_comp("/Ferry");
    Ferry *ptero_ferry;
    ptero_ferry = reinterpret_cast<Ferry *>(mem_comp.map(sizeof(Ferry)));
    ptero_ferry->inicializar(capacidad_maxima, carga_minima_para_zarpar);

    sv_sem semaforo("/Ferry", 0);
    cout << "Se inicia el ferry." << endl;
    while (true) {
        cout << "Esperando para zarpar desde la orilla " << ptero_ferry->get_orilla() << "..." << endl;
        semaforo.wait();
        if (ptero_ferry->finalizar)
            break;
        ptero_ferry->zarpar();
    }

    return 0;
}
