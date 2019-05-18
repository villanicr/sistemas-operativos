//#include "include.h"
#include "Carga.h"
int main()
{
    printf("*******************************************************\n");
    printf("* TP 2 : Semaforos - Tema 3 (Ferry) - Proceso Principal\n");
    printf("*******************************************************\n");
    printf("* Integrantes:\n");

    printf("      Villani Cristian        93358\n");
    printf("*******************************************************\n");

    sv_sem orillaA("orillaA",0);
    sv_sem orillaB("orillaB", 0);
        
    Carga *carga;
    sv_shm compartida("cargamento");
    carga=reinterpret_cast<Carga *> (compartida.map(BUFSIZ));	
    carga->setOrilla('a');
    carga->setViajando(false);
   // system("ipcs -s");    
    int i = 0; 
    carga->setColchonSeg(20);   
    print_state();
    carga->vaciarCarga();

    do {
//        debug_int(i++);    
	orillaA.wait();
//	orillaA.wait();
	cout<<"El ferry zarpo desde orilla A hacia la B  con una carga de :"<<carga->getCarga()<<endl;
	carga->vaciarCarga();
	cout<<"carga vaciada  "<<carga->getCarga()<<endl;
//	spleep(10);
	carga->setOrilla('b');
//ESTE POST ESTA MAL, POR QUE NO HABIA NADIE ESPERANDO EN B HACE PASAR AL PRIMERO Q VIENE

//PERO ATENCION!!!!!!!  ESTE POST B HACE Q SE SALTE EL SIGUIENTE WAIT B 
	if(carga->verEsperaB()){	
		orillaB.post();	
	}
	cout<<"llego a la orilla B esperando para cargarse"<<endl;
//	orillaB.wait();
	orillaB.wait();
	cout<<"El ferry zarpo desde orilla B hacia la A  con una carga de :"<<carga->getCarga()<<endl;
	carga->vaciarCarga();
	cout<<"carga vaciada  "<<carga->getCarga()<<endl;
//s	spleep(5);
	carga->setOrilla('a');
	if(carga->verEsperaA()){
		orillaA.post();	// libera a los vehiculos que estaban esperando en la orillaA  
	}
	cout<<"llego a la orilla A esperando para cargarse"<<endl;
	

    } while(true);

    system("ipcs -s");
}
