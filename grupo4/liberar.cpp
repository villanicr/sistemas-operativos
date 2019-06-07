#include "Sem-sv/sv_sem.h"
#include "Sem-sv/sv_shm.h"

using namespace std;
int main(int argc, char const *argv[]) {

    // Elimino el área compartida.
    sv_shm mem_comp("/Ferry");
    mem_comp.del();

    // Elimino los semáforos.
    sv_sem("/Ferry").del();
    sv_sem("/Norte").del();
    sv_sem("/Sur").del();
    return 0;
}
