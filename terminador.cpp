#include "include.h"

int main() {
    printf("*******************************************************\n");
    printf("* TP 2 : Semaforos - Tema 3 (Ferry) - Proceso Terminador\n");
    printf("*******************************************************\n");
    printf("* Integrantes:\n");

    printf("      Villani Cristian        93358\n");
    printf("*******************************************************\n");
    printf("\n");
    
    sv_sem orillaA("orillaa", 0);
    sv_sem orillaB("orillab", 0);
    sv_shm compartida("cargamento");
    
    orillaA.del();
    orillaB.del();
    compartida.del();
//falta eliminar la carga

    system("ipcs -s");
}
