#include "Sem-sv/sv_sem.h"
#include "Sem-sv/sv_shm.h"
#include "ferry.h"

using namespace std;
int main(int argc, char const *argv[]) {
    // Inicio el ferry en el área compartida
    sv_shm mem_comp("/Ferry");

    // Inicio los semáforos. Por defecto el ferry comienza en la orilla norte.
    sv_sem("/Norte", 1);
    sv_sem("/Sur", 0);
    return 0;
}
