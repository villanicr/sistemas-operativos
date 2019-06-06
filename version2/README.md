# sistemas-operativos

A continuacion listamos los pasos a seguir para ejecutar la simulacion:

1- Abrir una consola desde el directorio donde se encuentran los archivos, y escribir "make all"
de esta manera se crearan los ejecutables.

2- En una consola escribir ./inicializar de esta manera se iniciaran los semaforos.

3- Continuando escribir el comando ./ferry (capacidad maxima >0) (carga minima para zarpar>0). Estamos invocando al ferry con sus respectivos parametros los cuales deben ser positivos y ademas el segundo debe ser menor al primer parametro, de esta manera el ferry espera la llegada de vehiculos desde el inicio de su ejecucion en la orilla norte por defecto.
En caso olvidar los parametros o no saber su orden el programa lanzara un error explicando por salida std como realizar la correcta ejecucion.

4- Luego en una nueva consola escribir ./agregar_vehiculo (nombre del mismo) (peso > 0) (origen Norte o Sur), describimos la invocacion con sus parametros respectivos.
Este paso puede ser realizados tantas veces como se desee, creando multiples vehiculos para realizar la simulacion.

5- Cuando se desee finalizar la ejecucion de la simulacion, se debe escribir en una consola ./finalizar.

6- Posteriormente se debe escribir ./liberar de esta manera se liberan los recursos utilizados.


