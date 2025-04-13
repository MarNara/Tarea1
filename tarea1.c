#include "tdas/list.h"
#include "tdas/quque.h"
#include "tdas/extra.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

 //prueba

typedef struct{
  int id;
  char descripcion[1000];
  int prioridad;
  char hora[25];
}ticket;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de gestión de tickets de soporte técnico");
  puts("========================================");

  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a ticket ");
  puts("3) Mostrar lista de tickets pendientes");
  puts("4) Procesar siguiente ticket ");
  puts("5) Buscar ticket por ID y mostrar detalles");
  puts("6) Salir");
}

void registrar_clientes(List *clientes, Queue *colaBaja) {
  
  printf("Registrar nuevo ticket\n");
  //guardamos memoria para cada persona que registrará su ticket
  ticket *persona = (ticket *)malloc(sizeof(ticket));
  
  printf("Ingrese el ID: ");
  scanf("%d", &persona->id);
  getchar();
  printf("Ingrese la descripción: ");
  fgets(persona->descripcion, 100, stdin);
  persona->descripcion[strcspn(persona->descripcion, "\n")] = 0;
  //prioridad por defecto.
  persona->prioridad = 3;
  list_pushBack(clientes, persona);
  //insertar prioridad a la cola
  queue_insert(colaBaja, persona);
  time_t horaDe_ahora = time(NULL);
  struct tm *tiempo_actual = localtime(&horaDe_ahora);
  strftime(persona->hora, 25, "%H:%M:%S", tiempo_actual);
  printf("El ticket se a registrado con exito. \n");

}


/*crear una funcion que elimine el ticket de una cola y solo guarde los que no quiero modificar*/
void eliminarDeCola(Queue *cola, ticket *persona) {
  int total_de_la_cola = list_size(cola);
  /*crear una cola temporal o auxiliar para ver si el ticket 
  actual es diferenete a los datos del cliente*/
  Queue *cola_temporal = list_create();

  /*1ro necesito algo que elimine y devuelva el elemento de la cola original ya que ese 
  elemento lo voy a eliminar, luego insertar los elementos que no sean el 
  ticket actual a la cola temporal
  */
  for (int k = 0; k < total_de_la_cola; k++) {
    ticket *ticket_actual = queue_remove(cola);
    if (ticket_actual != persona) queue_insert(cola_temporal, ticket_actual);
  }

  /*insertar los datos de la cola temporal a la cola original para liberar la cola temporal
  y mantener los datos que no necesito eliminar en la original*/
  while (list_size(cola_temporal) > 0) {
    queue_insert(cola, queue_remove(cola_temporal));
  }

  free(cola_temporal); // liberar memoria de la lista temporal
}


void asignar_Prioridad(Queue *colaAlta, Queue *colaMedia, Queue *colaBaja, List *clientes){

  int buscar;
  printf("Ingrese el ID al cual quiere asignar una nueva prioridad: ");
  scanf("%d", &buscar);

  int tamano = list_size(clientes);
  ticket *persona = (ticket *)list_first(clientes);
  //crear una variable booleana para evaluar los diferentes casos (si hay o no tickets)
  bool encontrado = false;
  
  for(int k = 0; k < tamano; k++){
    if(persona->id == buscar){
      encontrado = true;
      printf("Asigne la prioridad: \n Alta es 1\n Media es 2\n Baja es 3. \n");
      scanf("%d", &persona->prioridad);
      switch (persona->prioridad) {
        case 1:
          eliminarDeCola(colaBaja, persona);
          queue_insert(colaAlta, persona);
          printf("su prioridad a sido asignada como Alta\n");
          break;
        case 2:
          eliminarDeCola(colaBaja, persona);
          queue_insert(colaMedia, persona);
          printf("su prioridad a sido asignada como Media\n");
          break;
        case 3:
          eliminarDeCola(colaBaja, persona);
          queue_insert(colaBaja, persona);
          printf("su prioridad a sido asignada como Baja\n");
          break;
        default:
          printf("Opción invalida %d", persona->prioridad);
          
      }
      
    }
    //pasar al siguiente cliente 
    persona = list_next(clientes);
  }
  if(!encontrado){
    printf("El ID que a ingresado no existe\n");
  }
}
  

void mostrar_lista_clientes(Queue *colaAlta, Queue *colaMedia, Queue *colaBaja) {
  // Mostrar pacientes en la cola de espera
  //hacer ciclos while para cada cola
  ticket *datosPersona;/*la usarepara asignar le un valor y luego para imprimir la prioridad.
  Como todos los datos de la cola ya son tickets, no necesito castear*/
  printf("Mostrar ticket por prioridad y orden de llegada:\n\n");
  //sacar el primer elemento de la cola.
  datosPersona = queue_front(colaAlta);
  //si la cola llega a null frenar el ciclo.
  while(datosPersona != NULL){
    printf("ID: %d.\nDescripción: %s.\nPrioridad: Alta.\n", datosPersona->id, datosPersona->descripcion);
    printf("Hora de Registro: %s\n\n", datosPersona->hora);
    datosPersona = list_next(colaAlta);//usaremos un list_next en una cola ya que la cola fue echa con List .
  }

  datosPersona = queue_front(colaMedia);
  while(datosPersona != NULL){
    printf("ID: %d.\nDescripción: %s.\nPrioridad: Media.\n", datosPersona->id, datosPersona->descripcion);
    printf("Hora de Registro: %s\n\n", datosPersona->hora);
    datosPersona = list_next(colaMedia);
  }

  datosPersona = queue_front(colaBaja);
  while(datosPersona != NULL){
    printf("ID: %d.\nDescripción: %s.\nPrioridad: Baja.\n", datosPersona->id, datosPersona->descripcion);
    printf("Hora de Registro: %s\n\n", datosPersona->hora);
    datosPersona = list_next(colaBaja);
  }

}

void procesar_siguiente_ticket(Queue *colaAlta, Queue *colaMedia, Queue *colaBaja, List *clientes){
  ticket *persona = (ticket*)list_first(clientes);
  //obtener los datos de un ticket
  //utilizar if para que vaya por orden
  //en cada if mostrar al cliente que se este procesando (o el ticket del cliente)
  if(persona = queue_remove(colaAlta)){
    printf("Ticket de prioridad Alta siendo atendido\n");
    printf("ID: %d.\nDescripción: %s.\nPrioridad: Alta.\n", persona->id, persona->descripcion);
    printf("Hora de Registro: %s\n\n", persona->hora);
    persona = list_next(clientes);/*pasamos al siguiente ticket dentro de su cola y el remove se encargara 
    de eliminar al actual*/
  }
  else if(persona = queue_remove(colaMedia)){
    printf("Ticket de prioridad Media siendo atendido\n");
    printf("ID: %d.\nDescripción: %s.\nPrioridad: Media.\n", persona->id, persona->descripcion);
    printf("Hora de Registro: %s\n\n", persona->hora);
    persona = list_next(clientes);
  }
  else if(persona = queue_remove(colaBaja)){
    printf("Ticket de prioridad Baja siendo atendido\n");
    printf("ID: %d.\nDescripción: %s.\nPrioridad: Baja.\n", persona->id, persona->descripcion);
    printf("Hora de Registro: %s\n\n", persona->hora);
    persona = list_next(clientes);
  }
  else{
    printf("No quedan más tickets por atender\n");
  }
  
  
}


// Mostrar ticket que se busca  
void mostrar_clientes_por_busqueda(List *clientes){
  //ingresar ticket que se busca
  int buscar;
  printf("Ingrese el ID que desea buscar: ");
  scanf("%d", &buscar);

  
  int tamano = list_size(clientes);
  ticket *persona = (ticket *)list_first(clientes);
  //usar un ciclo con bool para evaluar casoso donde exista o no el ticket
  bool El_Id_esta = false;
  for(int k = 0; k < tamano; k++){
    if(persona->id == buscar){
      El_Id_esta = true;
      break;
    }
    persona = list_next(clientes);
  }
  if(El_Id_esta == false){
    printf("El ID que a ingresado no existe\n");
  }

  //asignar otra vez el valor de persona para evaluar en el segundo for, ya que el frena el ciclo con ese dato
  persona = (ticket *)list_first(clientes);
  //crear un for para mostrar el ticket si se encontró en la lista
  for(int k = 0; k < tamano; k++){
    if(persona->id == buscar){
      if(persona->prioridad == 1){
        printf("ID: %d.\nDescripción: %s.\nPrioridad: Alta.\n", persona->id, persona->descripcion);
        printf("Hora de Registro: %s\n\n", persona->hora);

      }
      else if(persona->prioridad == 2){
        printf("ID: %d.\nDescripción: %s.\nPrioridad: Media.\n", persona->id, persona->descripcion);
        printf("Hora de Registro: %s\n\n", persona->hora);
      }
      else if(persona->prioridad == 3){
        printf("ID: %d.\nDescripción: %s.\nPrioridad: Baja.\n", persona->id, persona->descripcion);
        printf("Hora de Registro: %s\n\n", persona->hora);
      }
      
    }
    persona = list_next(clientes);
  }
  
  
}

int main() {
  char opcion;
  List *clientes = list_create(); // puedes usar una lista para gestionar los pacientes, general
  //CREAR COLAS PARA GUARDAR PRIORIDAD
  Queue *colaAlta = NULL;
  colaAlta = queue_create(colaAlta);
 
  Queue *colaMedia = NULL;
  colaMedia = queue_create(colaMedia);
 
  Queue *colaBaja = NULL;
  colaBaja = queue_create(colaBaja);

  //Para sacar los datos de solo un cliente.
  //ticket* persona = (ticket*)list_first(clientes);
  ticket* persona;
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior
      
    switch (opcion) {
    case '1':
      registrar_clientes(clientes, colaBaja);
      break;
    case '2':
      // Lógica para asignar prioridad
      /*usar 3 colas, asignar prioridad, 1 ALto, 2: Medio, 3 Bajo.
      Hacer una funcion, ya que hacer el codigo aqui es mucho enredo y el main no se ve limpio */
      //persona = (ticket*)list_first(clientes);
      asignar_Prioridad(colaAlta, colaMedia, colaBaja, clientes);
      break;
    case '3':
      mostrar_lista_clientes(colaAlta, colaMedia, colaBaja);
      break;
    case '4':
      // Lógica para atender al siguiente cliente, con un if y funciones de colas, primero ver si sirve el remove.
      procesar_siguiente_ticket(colaAlta, colaMedia, colaBaja, clientes);
      break;
    case '5':
      // Lógica para mostrar clientes por prioridad, mostrar la cola
      mostrar_clientes_por_busqueda(clientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión de Soporte Tecnico...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(clientes);

  return 0;
}