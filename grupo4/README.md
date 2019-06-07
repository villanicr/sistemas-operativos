# Sistemas operativos: trabajo práctico 2

A continuacion listamos los pasos a seguir para ejecutar la simulacion:

1. Abrir una consola en el directorio en el que se encuentra el archivo `grupo4.tar.gz`.

1. Descomprimir el archivo utilizando el comando `tar -xzf grupo4.tar.gz`.

1. Camiar al directorio creado (`cd grupo4`).

1. Si desea volver a compilar los archivos puede ejecutar `make all`.

1. Como primera instancia se debe inicializar la simulición, para ello ejecutar `./inicializar`.

1. Continuando escribir el comando `./ferry $capacidad_maxima $carga_minima_para_zarpar` (capacidad maxima > 0, 0 < carga minima para zarpar < capacidad maxima). Estamos invocando al ferry con sus respectivos parametros los cuales deben ser positivos y ademas el segundo debe ser menor al primer parametro, de esta manera el ferry espera la llegada de vehiculos desde el inicio de su ejecucion en la orilla **Norte** por defecto.
En caso olvidar los parametros o no saber su orden el programa lanzara un error explicando por consola como realizar la correcta ejecucion. Ejemplo: `./ferry 20 15`.

1. Luego en una nueva consola escribir `./agregar_vehiculo $nombre $peso $origen` (peso > 0, origen = Norte o Sur) para agregar un nuevo vehiculo a la simulación. Este paso puede ser realizados tantas veces como se desee, creando multiples vehiculos para realizar la simulacion pero utilizando siempre un nombre distinto para cada vehículo. Ejemplo: `./agregar_vehiculo "auto de pedro" 5 Norte`.

1. Cuando se desee finalizar la ejecucion de la simulacion, se debe escribir en una consola `./finalizar`.

1. Posteriormente se debe escribir `./liberar`. De esta manera se liberan los recursos (ipc) utilizados.
