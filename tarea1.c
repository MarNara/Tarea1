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
  printf("Ingrese la descripción: ");
  scanf("%s", persona->descripcion);
  getchar();
  list_pushBack(clientes, persona);
  

}


void asignar_Prioridad(Queue *colaAlta, Queue *colaMedia, Queue *colaBaja, ticket *persona){

  printf("Asigne la prioridad: Alta es 1, Media es 2 y Baja es 3.");
  //ingresar un dato a la cola
  scanf("%d", &persona->prioridad);

  switch (persona->prioridad) {
    case 1:
      queue_insert(colaAlta, persona);
      printf("su prioridad a sido asignada como Alta");
      break;
    case 2:
      queue_insert(colaMedia, persona);
      printf("su prioridad a sido asignada como Media");
      break;
    case 3:
      queue_insert(colaBaja, persona);
      printf("su prioridad a sido asignada como Media");
      break;
    //default:
      //printf("Opción invalida %d", persona->prioridad);
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
    printf("ID: %d, Descripción: %s, Prioridad: %d", perso->id, perso->descripcion, perso->prioridad);
    perso = list_next(clientes);
  }
}



int main() {
  char opcion;
  List *clientes = list_create(); // puedes usar una lista para gestionar los pacientes, general
  Queue *colaAlta;
  Queue *colaMedia;
  Queue *colaBaja;
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
      queue_create(colaAlta);
      queue_create(colaMedia);
      queue_create(colaBaja);
      //asignar_Prioridad(colaAlta, colaMedia, colaBaja, persona);
      break;
    case '3':
      mostrar_lista_clientes(clientes);
      break;
    case '4':
      // Lógica para atender al siguiente cliente
      break;
    case '5':
      // Lógica para mostrar clientes por prioridad, mostrar la pila
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