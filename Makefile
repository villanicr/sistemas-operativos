CXXFLAGS= -std=c++11

todos= main vehiculo terminador

all: $(todos)

clean:
	rm -f $(todos)
