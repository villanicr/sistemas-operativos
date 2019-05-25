CXXFLAGS= -std=c++11

todos= inicializar finalizar agregar_vehiculo ferry liberar

inicializar: ferry.h vehiculo.h nombre.h inicializar.cpp
	g++ $(CXXFLAGS) inicializar.cpp -o inicializar

liberar: ferry.h vehiculo.h nombre.h liberar.cpp
	g++ $(CXXFLAGS) liberar.cpp -o liberar

finalizar: ferry.h vehiculo.h nombre.h finalizar.cpp
	g++ $(CXXFLAGS) finalizar.cpp -o finalizar

agregar_vehiculo: ferry.h vehiculo.h nombre.h agregar_vehiculo.cpp
	g++ $(CXXFLAGS) agregar_vehiculo.cpp -o agregar_vehiculo

ferry: ferry.h vehiculo.h nombre.h ferry.cpp
	g++ $(CXXFLAGS) ferry.cpp -o ferry

all: $(todos)

clean:
	rm -f $(todos)
