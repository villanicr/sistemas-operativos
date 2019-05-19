#ifndef Carga_h
#define Carga_h
#include "include.h"
class Carga{
	bool ultimo;
	char dato [40];
	int load;
	char orilla;
	bool viajando;
	int colchonSeg;
	int esperaA;
	int esperaB;
	bool end;
	public:
		Carga() {
			strcpy (dato,"");
			ultimo=false;
			esperaA=0;
			esperaB=0;
			end=false;
			}
		Carga(std::string d) {
			strcpy (dato,d.c_str());
			ultimo=false;
			}
		Carga (const Carga & m){
			strcpy(dato,m.dato);
			ultimo=false;
			}
		std::string getDato(){return dato;};
		void setDato(std::string d){
		  strcpy (dato,d.c_str());
		  ultimo=false;
		}
		
		void filaAddA(){esperaA=esperaA+1;};
		void filaAddB(){esperaB=esperaB+1;};
		int tamFilaA(){return esperaA;};
		int tamFilaB(){return esperaB;};
		void filaRestarA(){esperaA=esperaA-1;};		
		void filaRestarB(){esperaB=esperaB-1;};		

		void setColchonSeg(int cs){colchonSeg=cs;}
		int getColchonSeg(){return colchonSeg;};		
		void setUltimo(){ultimo=true;};
		bool esUltimo(){return ultimo;};
		
		void setCarga(int cargamento){
			load=load+cargamento;		
		};
		
		void vaciarCarga(){
			load=0;
		}
		
		bool esFin(){return end;};
		void fin(){end=true;};

		int getCarga(){
			return load;
		};

		void setOrilla(char lado){
			orilla=lado;
		};
	
		char getOrilla(){
			return orilla;
		}
		bool estaViajando(){return viajando;};
		void setViajando(bool v){viajando=v;};

		friend std::ostream& operator<<(std::ostream& os, Carga m){
			os<<"("<<m.getDato();
			if (m.esUltimo()) os<<", ultimo";
			return os<<")";
			} 
};
#endif
