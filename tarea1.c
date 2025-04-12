#include "tdas/list.h"
#include "tdas/quque.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 //prueba

typedef struct{
  int id;
  char descripcion[100];
  int prioridad;
}ticket;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión de Soporte Tecnico");
  puts("========================================");

  puts("1) Registrar cliente");
  puts("2) Asignar prioridad a cliente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente cliente");
  puts("5) Mostrar clientes por prioridad");
  puts("6) Salir");
}

void registrar_clientes(List *clientes) {
  printf("Registrar nuevo cliente\n");
  // Aquí implementarías la lógica para registrar un nuevo paciente
  ticket *persona = (ticket *)malloc(sizeof(ticket));
  printf("Ingrese el ID: ");
  scanf("%d", &persona->id);
  getchar();
  printf("Ingrese la descripción: ");
  fgets(persona->descripcion, 100, stdin);
  persona->descripcion[strcspn(persona->descripcion, "\n")] = 0;
  persona->prioridad = 3;
  list_pushBack(clientes, persona);
  printf("El cliente se a registrado con exito. \n");

}


void asignar_Prioridad(Queue *colaAlta, Queue *colaMedia, Queue *colaBaja, ticket *persona){

  printf("Asigne la prioridad: \n Alta es 1\n Media es 2\n Baja es 3. \n");
  //ingresar un dato a la cola
  scanf("%d", &persona->prioridad);

  switch (persona->prioridad) {
    case 1:
      queue_insert(colaAlta, persona);
      printf("su prioridad a sido asignada como Alta\n");
      break;
    case 2:
      queue_insert(colaMedia, persona);
      printf("su prioridad a sido asignada como Media\n");
      break;
    case 3:
      queue_insert(colaBaja, persona);
      printf("su prioridad a sido asignada como Baja\n");
      break;
    default:
      printf("Opción invalida %d", persona->prioridad);
  }
}
  

void mostrar_lista_clientes(List *clientes) {
  // Mostrar pacientes en la cola de espera
  //ticket *persona = (ticket *)malloc(sizeof(ticket));
  ticket *perso = (ticket*)list_first(clientes);
  int total_clientes = list_size(clientes);
  printf("clientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
  for(int k = 0; k < total_clientes; k++){
    if(perso->prioridad == 1){
      printf("ID: %d.\nDescripción: %s.\nPrioridad: Alta.\n", perso->id, perso->descripcion);
    }
    else if(perso->prioridad == 2){
      printf("ID: %d.\nDescripción: %s.\nPrioridad: Media.\n", perso->id, perso->descripcion);
    }
    else if(perso->prioridad == 3){
      printf("ID: %d.\nDescripción: %s\nPrioridad: Baja.\n", perso->id, perso->descripcion);
    }
    perso = list_next(clientes);
  }
}

void atender_siguiente(Queue *colaAlta, Queue *colaMedia, Queue *colaBaja, ticket *persona){
  if(persona = queue_remove(colaAlta)){
    printf("cliente de prioridad Alta siendo atendido\n");
  }
  else if(persona = queue_remove(colaMedia)){
    printf("cliente de prioridad Media siendo atendido\n");
  }
  else if(persona = queue_remove(colaBaja)){
    printf("cliente de prioridad Baja siendo atendido\n");
  }
  
    /* code */
}
  
void mostrar_clientes_por_prioridad(List *clientes){
  
}

int main() {
  char opcion;
  List *clientes = list_create(); // puedes usar una lista para gestionar los pacientes, general
  /*Queue *colaAlta;
  Queue *colaMedia;
  Queue *colaBaja;
  */
  Queue *colaAlta = NULL;
  colaAlta = queue_create(colaAlta);
 
  Queue *colaMedia = NULL;
  colaMedia = queue_create(colaMedia);
 
  Queue *colaBaja = NULL;
  colaBaja = queue_create(colaBaja);
  ticket* persona;
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior
      
    switch (opcion) {
    case '1':
      registrar_clientes(clientes);
      break;
    case '2':
      // Lógica para asignar prioridad
      /*usar 3 colas, asignar prioridad, 1 ALto, 2: Medio, 3 Bajo.
      Hacer una funcion, ya que hacer el codigo aqui es mucho enredo y el main no se ve limpio */

      persona = (ticket*)list_first(clientes);
      asignar_Prioridad(colaAlta, colaMedia, colaBaja, persona);
      break;
    case '3':
      mostrar_lista_clientes(clientes);
      break;
    case '4':
      // Lógica para atender al siguiente cliente, con un if y funciones de colas, primero ver si sirve el remove.
      atender_siguiente(colaAlta, colaMedia, colaBaja, persona);
      break;
    case '5':
      // Lógica para mostrar clientes por prioridad, mostrar la cola
      //mostrar_clientes_por_prioridad(clientes);
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