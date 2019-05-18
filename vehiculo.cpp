//#include "include.h"
#include "Carga.h"
int main(int argc, char** argv) 
{
    printf("*******************************************************\n");
    printf("* TP 2 : Semaforos - Tema 3 (Ferry) - Proceso Atomo\n");
    printf("*******************************************************\n");
    printf("* Integrantes:\n");
    printf("      Villani Cristian        93358\n");
    printf("*******************************************************\n");
    printf("\n");

    Carga *carga;
    sv_shm compartida("cargamento");
    
    carga=reinterpret_cast<Carga *> (compartida.map(BUFSIZ));	
    
    
    
    if(argc <= 1) {
    	cout<< "parametros faltantes ingrese nombre vehiculo,carga y orilla de partida.\n";
	//exit(0);
    }

    int load= atoi(argv[2]);
    cout<<"carga aca:    "<<load<<"valor seg arg"<<argv[2]<<endl;
    //despues de las validaciones

    cout<<"Vehiculo:   "<<argv[1]<<endl;
    cout<<"colchon seg"<<carga->getColchonSeg()<<endl;

    if(!strcmp(argv[3],"a"))
    {
 	sv_sem orillaA("orillaA", 0);    
    	if(carga->estaViajando() == true || carga->getOrilla() == 'b'){
		cout<<"aca "<<carga->estaViajando()<<":viajando  "<<"orilla  "<<carga->getOrilla()<<endl;		
		orillaA.wait();
		if(carga->getColchonSeg()>=load){
			carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: a"<<endl;
			cout<<"carga ferry1:  "<<carga->getCarga()<<endl;
		}
	}
    	if(carga->estaViajando() == false and carga->getOrilla() == 'a'){
		if(carga->getColchonSeg()>=load){
			carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: a"<<endl;
			cout<<"carga ferry2:  "<<carga->getCarga()<<endl;
		}
	}
	if(carga->getColchonSeg() <= carga->getCarga()){
		cout<<"El ferry listo para zarpar desde la orilla A:  "<<"carga interna: "<<carga->getCarga()<<" se dirijira a la orilla B"<<endl;
		orillaA.post();
	}	
    }
    
    if(!strcmp(argv[3],"b"))
    {
 	sv_sem orillaB("orillaB", 0);    
    	if(carga->estaViajando() == true || carga->getOrilla() == 'a'){
		orillaB.wait();
		if(carga->getColchonSeg()>=load){
			carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: b"<<endl;
		}
	}
    	if(carga->estaViajando() == false and carga->getOrilla() == 'b'){
		if(carga->getColchonSeg()>=load){
			carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: b"<<endl;
		}
	}
	if(carga->getColchonSeg() <= carga->getCarga()){
		cout<<"El ferry listo para zarpar desde la orilla B:  "<<"carga interna: "<<carga->getCarga()<<" se dirijira a la orilla A"<<endl;
		orillaB.post();
		
   	}	
    }
}
