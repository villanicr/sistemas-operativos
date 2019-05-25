#include "Sem-sv/sv_sem.h"
#include "Sem-sv/sv_shm.h"
#include "ferry.h"

using namespace std;
int main(int argc, char const *argv[]) {

    // Obtengo el ferry y seteo finalizar en true.
    sv_shm mem_comp("/Ferry");
    Ferry *ptero_ferry = reinterpret_cast<Ferry *>(mem_comp.map(sizeof(Ferry)));
    ptero_ferry->finalizar = true;

    // Libero la bodega.
    ptero_ferry->liberar_bodega();

    // Hago un post para liberar al ferry.
    sv_sem("/Ferry").post();

    return 0;
}
