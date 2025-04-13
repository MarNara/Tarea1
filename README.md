# Tarea1

Información que existirá dentro del README.md
1.	cómo compilar y ejecutar la tarea;

primero en el git bash compilar: 
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1

Luego debe escribir lo siguiente para ejecutar la tarea: 
./tarea1

2.	las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas;
Las opiones que funcionan son las siguientes: 
(1) Registrar cliente.
(2) Asignar prioridad a cliente.
(3) Mostrar lista de espera.
(4) Atender al siguiente cliente.
(5) Buscar ticket por ID y mostrar detalles.
(6) Salir.

Las funciones que funcionan correctamente son todas las de lista.h y la lista quque.h
Y las de la cola.

3.	un ejemplo mostrando como interactuar con la aplicación.

-----------------------EJEMPLO opción 1---------------------------
Ingrese su opci├│n: 1
Registrar nuevo ticket
Ingrese el ID: 45
Ingrese la descripci├│n: El Pc se apago y ya no enciende
El ticket se a registrado con exito. 
Presione una tecla para continuar...

-----------------------EJEMPLO opción 2---------------------------
Ingrese su opci├│n: 2
Ingrese el ID al cual quiere asignar una nueva prioridad: 45
Asigne la prioridad: 
 Alta es 1
 Media es 2
 Baja es 3.
1
su prioridad a sido asignada como Alta
Presione una tecla para continuar...


-----------------------EJEMPLO opción 3---------------------------
Ingrese su opci├│n: 3
Mostrar ticket por prioridad y orden de llegada:

ID: 45.
Descripci├│n: El Pc se apago y ya no enciende.
Prioridad: Alta.
Hora de Registro: 14:15:05

ID: 67.
Descripci├│n: El celular no carga muy bien aunque aveces si lo hace bien.
Prioridad: Media.
Hora de Registro: 14:16:34

ID: 80.
Descripci├│n: Se reinicia la laptop cuando abro algunos programas.
Prioridad: Media.
Hora de Registro: 14:17:53

ID: 23.
Descripci├│n: instalar un antivirus.
Prioridad: Baja.
Hora de Registro: 14:14:41

ID: 73.
Descripci├│n: actualizar aplicaciones.
Prioridad: Baja.
Hora de Registro: 14:17:10

Presione una tecla para continuar...


-----------------------EJEMPLO opción 4---------------------------
Ingrese su opci├│n: 4
Ticket de prioridad Alta siendo atendido
ID: 45.
Descripci├│n: El Pc se apago y ya no enciende.
Prioridad: Alta.
Hora de Registro: 14:15:05

Presione una tecla para continuar...

-----------------------Ejemplo opción 5---------------------------

#  Cuando hay un ID
Ingrese su opci├│n: 5
Ingrese el ID que desea buscar: 67
ID: 67.
Descripci├│n: El celular no carga muy bien aunque aveces si lo hace bien.
Prioridad: Media.
Hora de Registro: 14:16:34

Presione una tecla para continuar...

# Cuando NO hay ID:
Ingrese su opci├│n: 5
Ingrese el ID que desea buscar: 56
El ID que a ingresado no existe
Presione una tecla para continuar...