#include  "../Sem-sv/sv_sem.h"
#include  "../Sem-sv/sv_shm.h"
#include "Carga.h"
using namespace std;

int main(){
	sv_sem ferry("ferry",0);
	Carga *carga;
        sv_shm compartida("cargamento");
        carga=reinterpret_cast<Carga *> (compartida.map(BUFSIZ));	
	carga->fin();
	ferry.post();
	cout<<"simulacion terminada"<<endl;
}
	
