#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "acciones.h"
#include "escenario.h"


int main(){
  int niveles;
  int posi = 0;
  elemento *ele;
  int opcion;
  int pos;
  int agrega;
  escenario *esc_main;
  acciones *acc_main;
  esc_main = CrearEscenario();
  printf("BIENVENIDO AL JUEGO MARIO PORFI RECUPERA LA MEMORIA.\n");
  printf("¿Cuantos niveles desea que tenga el juego?: ");
  scanf("%i",&niveles); //se asume que se pasara un numero mayor y distinto de 0
  esc_main->length = niveles;
  esc_main->largo_inicial = niveles;
  esc_main = crear_niveles(esc_main, niveles);
  while ( posi < niveles){
    printf("Puede realizar los siguientes cambios:\n");
    printf("1. Mostrar un elemento.\n");
    printf("2. Mostrar todo.\n");
    printf("3. Anadir un elemento.\n");
    printf("4. Borrar un elemento.\n");
    printf("5. Borrar todo.\n");
    printf("6. No quiero realizar ningun cambio.\n");
    printf("Seleccione una opcion: ");
    scanf("%i", &opcion);
    if (opcion == 1){
      printf("¿Que nivel desea ver?\n");
      printf("Posicion: ");
      scanf("%i", &pos);
      mostrar(esc_main, pos);
    }
    else if (opcion == 2){
      mostrar_todo(esc_main);
    }
    else if (opcion == 3){
      printf("Que elemento desea anadir?\n");
      printf("1. Objeto\n");
      printf("2. Enemigo\n");
      printf("3. Bloque.\n");
      printf("4. Suelo\n");
      printf("Opcion: ");
      scanf("%i",&pos);
      printf("¿En que posicion?: ");
      scanf("%i",&agrega);
      if (pos == 1){
        ele = objeto();
        anadir_elemento(esc_main,ele,agrega, 2);
      }
      else if (pos == 2){
        ele = enemigo();
        anadir_elemento(esc_main, ele, agrega, 3);
      }
      else if (pos == 3){
        ele = bloque();
        anadir_elemento(esc_main,ele,agrega,4);
      }
      else if (pos == 4){
        ele = suelo();
        anadir_elemento(esc_main,ele,agrega,5);
      }
      else{
        printf("Elemento invalido. Ingrese uno de los numeros mostrados por pantalla.\n");
      }
    }
    else if (opcion == 4){
      printf("Que posicion desea eliminar?\n");
      printf("Posicion: ");
      scanf("%i",&pos);
      borrar_elemento(esc_main, pos);
      
    }
    else if (opcion == 5){
      borrar_todo(esc_main);
      printf("Escenario vacio.\n");
      }
    else{
      break;
    }
  }
  opcion = 0;
  personaje(esc_main);
  acc_main = CrearAcciones();
  acc_main = fun_iniciales(acc_main);
  esc_main->curr = esc_main->head;
  esc_main->posCurr = 0;
  printf("Comienza el juego!\n");
  while (esc_main->largo_inicial != 0){
    printf("¿Que desea hacer?\n");
    printf("1. Saltar encima\n");
    printf("2. Caminar\n");
    printf("3. Taclear al frente\n");
    printf("4. Rushear\n");
    printf("5. Ver plata\n");
    printf("6. ¡Muestrame todo el mapa!\n");
    printf("7. Ver una casilla en especifico\n");
    printf("Opcion: ");
    scanf("%i", &opcion);
    if (opcion == 6){
      mostrar_todo(esc_main);
    }
    else if (opcion == 7){
      printf("Que casilla desea ver?\n");
      printf("Posicion: ");
      scanf("%i",&pos);
      mostrar(esc_main, pos);
    }
    else if (opcion == 1){
      choice(1, acc_main, esc_main);
      if (esc_main->pos_pj != esc_main->length){
        casos(acc_main, esc_main);
      }
    }
    else if (opcion == 2){
      choice(2,acc_main, esc_main);
      if (esc_main->pos_pj != esc_main->length){
        casos(acc_main, esc_main);
      }
    }
    else if (opcion == 3){
      choice(3, acc_main, esc_main);
      if (esc_main->pos_pj != esc_main->length){
        casos(acc_main, esc_main);
      }
    }
    else if (opcion == 4){
      choice(4, acc_main, esc_main);
      if (esc_main->pos_pj != esc_main->length){
        casos(acc_main, esc_main);
      }
    }
    else if (opcion == 5){
      choice(5, acc_main, esc_main);
    }
    else{
      printf("Ingrese una opcion valida\n");
    }
  }
  borrar_accall(acc_main);
  borrar_todo(esc_main);
  free(esc_main);
  //free(acc_main);
  //free(ele);
  return 0;
}

