#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 //prueba

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct{
  char name[100];
  int edad;
  int id;
  int prioridad[3];
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
  printf("Ingrese el nombre: ");
  scanf("%s", persona->name);
  getchar();
  printf("Ingrese la edad: ");
  scanf("%s", persona->edad);
  list_pushBack(clientes, persona);
  

}

void mostrar_lista_clientes(List *clientes) {
  // Mostrar pacientes en la cola de espera
  //ticket *persona = (ticket *)malloc(sizeof(ticket));
  Node *nodoAux = clientes;
  int total_clientes = list_size(clientes);
  printf("clientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
  ticket *persona = (ticket *)nodoAux->data;
  for(int k = 0; k < total_clientes; k++){
    printf("Nombre: %s, Edad: %d.", persona->name, persona->edad);
    nodoAux = nodoAux->next;
  }
}

int main() {
  char opcion;
  List *clientes = list_create(); // puedes usar una lista para gestionar los pacientes, general

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
      /**/
      break;
    case '3':
      mostrar_lista_clientes(clientes);
      break;
    case '4':
      // Lógica para atender al siguiente cliente
      break;
    case '5':
      // Lógica para mostrar clientes por prioridad
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