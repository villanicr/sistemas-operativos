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
    
    char rta;
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
	if(carga->estaViajando() == false and carga->getOrilla() == 'a'){
		if(30>=carga->getCarga()+load){
			carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: a"<<endl;
			cout<<"carga ferry2:  "<<carga->getCarga()<<endl;
		}
	}    	
	if(carga->estaViajando() == true || carga->getOrilla() == 'b'){
		cout<<"aca "<<carga->estaViajando()<<":viajando  "<<"orilla  "<<carga->getOrilla()<<endl;		
		carga->filaAddA();		
		orillaA.wait();
		carga->filaRestarA();
		cout<<"t<m fila A "<<carga->tamFilaA()<<endl;
		carga->setCarga(load);		
		if(carga->tamFilaA() > 0 and carga->getColchonSeg()>=carga->getCarga()){
			orillaA.post();
		}

		cout<<"ingrese char para cargar el q esperaba"<<endl;
		cin>>rta; 

		if(carga->getColchonSeg()>=carga->getCarga()+load){
		//	carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: a"<<endl;
			cout<<"carga ferry1:  "<<carga->getCarga()<<endl;
		}
	}
    	
	if(carga->getColchonSeg() <= carga->getCarga()){
        	sv_sem ferry("ferry",0);    	
		cout<<"El ferry listo para zarpar desde la orilla A:  "<<"carga interna: "<<carga->getCarga()<<" se dirijira a la orilla B"<<endl;
		ferry.post();
	}	
    }
    
    if(!strcmp(argv[3],"b"))
    {
 	sv_sem orillaB("orillaB", 0);    
	if(carga->estaViajando() == false and carga->getOrilla() == 'b'){
		if(30>=carga->getCarga()+load){
			carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: b"<<endl;
		}
	}    	
	if(carga->estaViajando() == true || carga->getOrilla() == 'a'){
		carga->filaAddB();		
		orillaB.wait();
		carga->filaRestarB();
		cout<<"t<m fila B "<<carga->tamFilaB()<<endl;
		cout<<"ingrese char para cargar el q esperaba"<<endl;
		cin>>rta; 
		carga->setCarga(load);
		if(carga->tamFilaB() > 0 and carga->getColchonSeg()>carga->getCarga()){
			cout<<"entro al post  "<<"con carga interma"<<carga->getCarga()<<endl;			
			orillaB.post();
		}
		cout<<"t<m fila B "<<carga->tamFilaB()<<endl;
		cout<<"ingrese char para cargar el q esperaba"<<endl;
		cin>>rta; 
		if(carga->getColchonSeg()>= carga->getCarga()+load){
			//carga->setCarga(load);
			cout<<"El vehiculo:  "<<argv[1]<<" cargo: "<<load<<" unidades en la orilla: b"<<endl;
			cout<<"carga del ferry:   "<<carga->getCarga()<<endl;
		}
	}
    	
	if(carga->getColchonSeg() <= carga->getCarga()){
		sv_sem ferry("ferry",0);    		
		cout<<"El ferry listo para zarpar desde la orilla B:  "<<"carga interna: "<<carga->getCarga()<<" se dirijira a la orilla A"<<endl;
		ferry.post();
		
   	}	
    }
}
