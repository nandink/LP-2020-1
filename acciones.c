#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "escenario.h"
#include "acciones.h"


/*
dun CrearDun
-----------------------------------
No recibe parametros
------------------------------------
Funcion constructora de un dun
*/
dun* CrearDun(){
    dun* au;
    au = (dun*)malloc(sizeof(dun));
    au->next = (dun*)malloc(sizeof(dun));
    au->identificador = 0;
    au->funcion= NULL;
    return au;
}
/*
acciones CrearAcciones
-----------------------------------
No recibe parametros
------------------------------------
Funcion constructora de un struct acciones 
*/
acciones* CrearAcciones(){
    acciones *acc;
    acc = (acciones*)malloc(sizeof(acciones));
    acc->head = CrearDun();
    acc->curr = acc->head;
    acc->tail = acc->head;
    acc->length =  acc->posCurr = 0;
    return acc;
}
//funcion destructora del dun
void DestruirDun(dun* algo){
    //algo->funcion = NULL;
    free(algo);
}
/*
void borrar_dun
-----------------------------------
Recibe como parametro un struct acciones y un entero eliminado
------------------------------------
Funcion que elimina un struct dun, segun su posicion "eliminado"
*/
void borrar_dun(acciones* acc, int eliminado){ 
    acc->curr = acc->head;
    acc->posCurr = 0;
    dun* auxiliar;
    auxiliar= (dun*)malloc(sizeof(dun));
    if (eliminado == 0){ //si se quiere eliminar la cabeza
        auxiliar = acc->head;
        acc->curr = acc->head->next;
        acc->head = acc->curr;
    }
    else if (eliminado == acc->length-1){ //si se quiere eliminar la cola
        acc->curr = acc->tail;
        auxiliar = acc->curr;
        while(eliminado <= acc->length-2 ){
            acc->posCurr++;
            acc->curr = acc->curr->next;  //quedara en el penultimo
        }
        acc->tail = acc->curr;
        acc->tail->next = NULL;

    }
    else{ //de otro lugar
        while (acc->posCurr <= eliminado-1 ){ //termina en el anterior a la posicion que quiero borrar
            acc->curr = acc->curr->next;
            acc->posCurr++;
        }
        auxiliar= acc->curr->next;
        acc->curr->next = auxiliar->next;
    }
    DestruirDun(auxiliar);
    acc->length--;
}
/*
void anadir_piso
-----------------------------------
Recibe como parametro un struct escenario y un entero i
------------------------------------
Funcion auxiliar que anade una casilla de tipo suelo normal a la lista de casillas
*/
void anadir_piso(escenario *esc, int i){
    elemento* agregar;
    agregar = (elemento*)malloc(sizeof(elemento));
    agregar->caracteristica1 = (int*)malloc(sizeof(int));
    (*(int*)agregar->caracteristica1) = 0;
    anadir_elemento(esc, agregar, i , 5);
}
/*
void eliminar_delista
-----------------------------------
Recibe como parametro un struct acciones y un entero eliminado
------------------------------------
Funcion que elimina de nuestra lista de acciones la funcion que tenga el identificador "eliminado"
*/
void eliminar_delista(acciones* listaAcc, int eliminado){ //borra la funcion con identificador "eliminado" de la lista acciones
    int i;
    listaAcc->curr = listaAcc->head; 
    for (i=0 ; i < listaAcc->length ; i++){
        if (eliminado == listaAcc->curr->identificador){
            borrar_dun(listaAcc, i);
            listaAcc->length--;
            return;
        }
    }
    return;
}
/*
int en_lista
-----------------------------------
Recibe como parametro un struct acciones y un entero identificador
------------------------------------
Funcion auxiliar que revisa si la funcion con identificador "identificador" se encuentra en la lista. Retorna 1 si se encuentra y 0 si no.
*/
int en_lista(acciones* listaAcc, int identificador){
    int i;
    listaAcc->curr = listaAcc->head;
    for (i=0; i < listaAcc->length; i++){
        if (identificador == listaAcc->curr->identificador){
            return 1;
        }
        else{
            listaAcc->curr = listaAcc->curr->next;
        }
    }
    return 0;
}
/*
void saltar_encima                   -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario y un entero i
------------------------------------
Funcion que mueve a nuestro personaje "i" casillas con respecto a la posicion
*/
void saltar_encima(escenario* esc, int i){
    esc->curr = esc->head;
    esc->posCurr = 0;
    while (esc->posCurr != esc->pos_pj){
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
    if (esc->pos_pj+1 < 1){ //se devuelve el pj al inicio
        if (esc->pos_pj != 0){
            printf("Retrocediste mas de lo posible, quedas en la primera casilla./n");
            borrar_elemento(esc, esc->pos_pj);
            elemento* auxiliar;
            auxiliar = (elemento*)malloc(sizeof(elemento));
            auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
            auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
            auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
            auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
            (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
            (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
            anadir_elemento(esc,auxiliar,0, 1);
            esc->curr = esc->head;
            esc->pos_pj = 0;
            esc->posCurr = 0;
            return;
        }
        else{ //ya estaba al principio, lo dejo igual
            return;
        }
    }
    else if (esc->pos_pj+i >= esc->length){ //salta mas alla del final, gana el juego
        printf("-------------------------------\n");
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
        printf("-------------------------------\n");
        esc->largo_inicial = 0;
        return;
    }
    else{ //en otro caso, ver donde cae
        elemento* auxiliar;
        auxiliar = (elemento*)malloc(sizeof(elemento));
        auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
        auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
        auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
        auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
        (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
        (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
        borrar_elemento(esc, esc->pos_pj);
        esc->pos_pj = esc->pos_pj + i;
        anadir_elemento(esc,auxiliar, esc->pos_pj-1, 1);
        esc->pos_pj = esc->pos_pj -1;
        esc->curr = esc->head;
        esc->posCurr = 0;
        while (esc->posCurr != esc->pos_pj){
            esc->curr = esc->curr->next;
            esc->posCurr++;
        }
        if (esc->curr->next->tipo == 2){ //si es objeto, lo tomo
            printf("-------------------------------\n");
            printf("Saltaste sobre el objeto: %s !!\n", ((char*)esc->curr->next->cosa->caracteristica1));
                if ((*(int*)esc->curr->next->cosa->caracteristica2) == 1 ){
                    (*(int*)esc->curr->cosa->caracteristica2) = 1;
                    printf("El objeto te dio el estado de: Normal!\n");
                    
                }
                else if ((*(int*)esc->curr->next->cosa->caracteristica2) == 2 ){
                    (*(int*)esc->curr->cosa->caracteristica2) = 3;
                    printf("El objeto te dio el estado de: Mareado!\n");
                
                }
                else if ((*(int*)esc->curr->next->cosa->caracteristica2) == 3 ){
                    (*(int*)esc->curr->cosa->caracteristica2) = 4;
                    printf("El objeto te dio el estado de: Wario!\n");
                }
                else{ // caracteristica de objeto 4=brillante
                    (*(int*)esc->curr->cosa->caracteristica2) = 2;
                    printf("El objeto te dio el estado de: Brillante!\n");
                }
                printf("-------------------------------\n");
                borrar_elemento(esc, esc->pos_pj+1);
                if (esc->pos_pj == 0){
                    anadir_piso(esc, 0);
                }
                else{
                    anadir_piso(esc,esc->pos_pj-1);
                }
                esc->posCurr++;
                esc->pos_pj++;
        }
        else if (esc->curr->next->tipo == 3){ //si es enemigo, lo mato
            printf("-------------------------------\n");
            printf("Saltaste sobre %s, lo has matado!\n", ((char*)esc->curr->next->cosa->caracteristica1));
            printf("-------------------------------\n");
            borrar_elemento(esc, esc->pos_pj+1);
            if (esc->pos_pj == 0){
                anadir_piso(esc, 0);
            }
            else{
                anadir_piso(esc,esc->pos_pj-1);
            }
            esc->pos_pj++;
            esc->posCurr++;
    }       
        else if (esc->curr->next->tipo == 5){ //si es suelo
            if ((*(int*)esc->curr->next->cosa->caracteristica1) == 1){ //si es agujero infinito
                printf("-----------------------------\n");
                printf("Oh no! Te has pillado con un agujero infinito y vuelves al inicio del juego\n");
                printf("-----------------------------\n");
                (*(int*)esc->curr->next->cosa->caracteristica1) = 0; //se cambia a piso firme la casilla donde el pj murio
                if (esc->pos_pj != 0){
                    elemento* auxiliar;
                    auxiliar = (elemento*)malloc(sizeof(elemento));
                    auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
                    auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
                    auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
                    auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
                    (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
                    (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
                    borrar_elemento(esc, esc->pos_pj);
                    anadir_elemento(esc,auxiliar, 0, 1);
                    esc->curr = esc->head;
                    esc->pos_pj = 0;
                    esc->posCurr = 0;
                    return;
                }
                else{
                    return;
                }
            }
            else if ((*(int*)esc->curr->next->cosa->caracteristica1) == 0){ //es piso firme
                borrar_elemento(esc, esc->pos_pj+1);
                if (esc->pos_pj == 0){
                    anadir_piso(esc, 0);
                }
                else{
                    anadir_piso(esc,esc->pos_pj-1);
                }
                esc->pos_pj++;
                esc->posCurr++;
            }
        }
        else if (esc->curr->next->tipo == 4){ //si es objeto
            if (*(int*)esc->curr->next->cosa->caracteristica2 == 0){ //son monedas
                printf("-------------------\n");
                printf("Has encontrado monedas!! Se han agregado a tu inventario\n");
                printf("-------------------\n");
                if (*(int*)esc->curr->cosa->caracteristica2 == 4){ //si esta en modo wario
                    (*(int*)esc->curr->cosa->caracteristica3) += 2 * (*(int*)esc->curr->next->cosa->caracteristica1);
                    (*(int*)esc->curr->cosa->caracteristica2) = 1; //vuelve a modo normal
                }
                else{
                    (*(int*)esc->curr->cosa->caracteristica3) += (*(int*)esc->curr->next->cosa->caracteristica1);
                }
                borrar_elemento(esc, esc->pos_pj+1);
                if (esc->pos_pj == 0){
                anadir_piso(esc, 0);
                }
                else{
                    anadir_piso(esc,esc->pos_pj-1);
                }            
            }
            else{ //es objeto
                printf("-------------------------------\n");
                printf("Saltando te has encontrado el objeto: %s\n", ((char*)esc->curr->next->cosa->caracteristica1));
                if ((*(int*)esc->curr->next->cosa->caracteristica3) == 1 ){
                    (*(int*)esc->curr->cosa->caracteristica2) = 1;
                    printf("El objeto te dio el estado de: Normal!\n");
                }
                else if ((*(int*)esc->curr->next->cosa->caracteristica3) == 2 ){
                    (*(int*)esc->curr->cosa->caracteristica2) = 3;
                    printf("El objeto te dio el estado de: Mareado!\n");
                }
                else if ((*(int*)esc->curr->next->cosa->caracteristica3) == 3 ){
                    (*(int*)esc->curr->cosa->caracteristica2) = 4;
                    printf("El objeto te dio el estado de: Wario!\n");
                }
                else{ // caracteristica de objeto 4=brillante
                    (*(int*)esc->curr->cosa->caracteristica3) = 2;
                    printf("El objeto te dio el estado de: Brillante!\n");
                }
                printf("-------------------------------\n");
                borrar_elemento(esc, esc->pos_pj+1);
                if (esc->pos_pj == 0){
                anadir_piso(esc, 0);
                }
                else{
                    anadir_piso(esc,esc->pos_pj-1);
                }
            }
            esc->posCurr++;
            esc->pos_pj++;
        }
    }
   
}
/*
void rushear                  -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario
------------------------------------
Funcion que mueve a nuestro personaje tres casillas a la derecha
*/
void rushear(escenario* esc){ //tres a la derecha
    int i = 0;
    esc->curr = esc->head;
    esc->posCurr = 0;
    while (esc->posCurr != esc->pos_pj){
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
    if (esc->pos_pj+3 >= esc->length){
        printf("-------------------------------\n");
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
        printf("-------------------------------\n");
        esc->largo_inicial = 0;
        return;
    }
    if (esc->pos_pj == esc->length-1){
        printf("-------------------------------\n");
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
        printf("-------------------------------\n");
        esc->pos_pj = esc->length+1;
        return;
    }
    while ( i < 3){
        esc->curr = esc->head;
        esc->posCurr = 0;
        while (esc->posCurr != esc->pos_pj){ //volver el curr al personaje
            esc->curr = esc->curr->next;
            esc->posCurr++;
        }
        if (esc->curr->next->tipo == 2){ //si es objeto, lo tomo
            printf("-------------------------------\n");
            printf("Rusheando te has encontrado el objeto: %s\n", ((char*)esc->curr->next->cosa->caracteristica1));
            if ((*(int*)esc->curr->next->cosa->caracteristica2) == 1 ){
                (*(int*)esc->curr->cosa->caracteristica2) = 1;
                printf("El objeto te dio el estado de: Normal!\n");
            }
            else if ((*(int*)esc->curr->next->cosa->caracteristica2) == 2 ){
                (*(int*)esc->curr->cosa->caracteristica2) = 3;
                printf("El objeto te dio el estado de: Mareado!\n");
            }
            else if ((*(int*)esc->curr->next->cosa->caracteristica2) == 3 ){
                (*(int*)esc->curr->cosa->caracteristica2) = 4;
                printf("El objeto te dio el estado de: Wario!\n");
            }
            else{ // caracteristica de objeto 4=brillante
                (*(int*)esc->curr->cosa->caracteristica2) = 2;
                printf("El objeto te dio el estado de: Brillante!\n");
            }
            printf("-------------------------------\n");
            borrar_elemento(esc, esc->pos_pj+1);
            if (esc->pos_pj == 0){
                anadir_piso(esc, 0);
            }
            else{
                anadir_piso(esc,esc->pos_pj-1);
            }
        }
        else if (esc->curr->next->tipo == 3){ //si es enemigo, lo mato
            printf("-------------------------------\n");
            printf("Rusheando has matado a %s en el camino!\n", ((char*)esc->curr->next->cosa->caracteristica1));
            printf("-------------------------------\n");
            borrar_elemento(esc, esc->pos_pj+1);
            if (esc->pos_pj == 0){
                anadir_piso(esc, 0);
            }
            else{
                anadir_piso(esc,esc->pos_pj-1);
            }
        }
        else if (esc->curr->next->tipo == 5){ //si es suelo
            if ((*(int*)esc->curr->next->cosa->caracteristica1) == 1){ //si es agujero infinito
                printf("-----------------------------\n");
                printf("Oh no! Te has pillado con un agujero infinito y vuelves al inicio del juego\n");
                printf("-----------------------------\n");
                (*(int*)esc->curr->next->cosa->caracteristica1) = 0; //se cambia a piso firme la casilla donde el pj murio
                if (esc->pos_pj != 0){
                    elemento* auxiliar;
                    auxiliar = (elemento*)malloc(sizeof(elemento));
                    auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
                    auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
                    auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
                    auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
                    (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
                    (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
                    borrar_elemento(esc, esc->pos_pj);
                    anadir_elemento(esc,auxiliar, 0, 1);
                    esc->curr = esc->head;
                    esc->pos_pj = 0;
                    esc->posCurr = 0;
                    return;
                }
                else{
                    return;
                }
            }
        
            else if ((*(int*)esc->curr->next->cosa->caracteristica1) == 0){ //es piso firme
                borrar_elemento(esc, esc->pos_pj+1);
                if (esc->pos_pj == 0){
                    anadir_piso(esc, 0);
                }
                else{
                    anadir_piso(esc,esc->pos_pj-1);
                }
            }
        }
        else if (esc->curr->next->tipo == 4){ //es bloque
            elemento* auxiliar;
            auxiliar = (elemento*)malloc(sizeof(elemento));
            auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
            auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
            auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
            auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
            (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
            (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
            borrar_elemento(esc, esc->pos_pj);
            anadir_elemento(esc,auxiliar, esc->pos_pj+1, 1);
        }
        esc->pos_pj++;
        esc->posCurr++;
        i++;
        
    }

}
/*
void caminar_en                    -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario
------------------------------------
Funcion que mueve a nuestro personaje a la siguiente casilla disponible (se asume como +1 a la derecha)
*/
void caminar_en(escenario* esc){
    esc->curr = esc->head;
    esc->posCurr = 0;
    while (esc->posCurr != esc->pos_pj){ //mover el curr a la posicion del personaje por cualquier caso de error
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
    if (esc->pos_pj == esc->length-1){
        printf("------------\n");
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
        printf("------------\n");
        esc->largo_inicial = 0;
        return;
    }
    if (esc->curr->next->tipo == 3){ //es enemigo
        printf("-----------------------------\n");
        printf("Oh no! %s te ha matado! Vuelves al inicio.\n", ((char*)esc->curr->next->cosa->caracteristica1));
        printf("------------------------------\n");
        borrar_elemento(esc, esc->pos_pj+1);
        anadir_piso(esc, esc->pos_pj+1);
        if (esc->pos_pj != 0){
            elemento* auxiliar;
            auxiliar = (elemento*)malloc(sizeof(elemento));
            auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
            auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
            auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
            auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
            (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
            (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
            borrar_elemento(esc, esc->pos_pj);
            anadir_elemento(esc,auxiliar, 0, 1);
            esc->curr = esc->head;
            esc->pos_pj = 0;
            esc->posCurr = 0;
            return;
        }
        else{
            return;
        }
    }
    else if (esc->curr->next->tipo == 5){ //es suelo
        if ((*(int*)esc->curr->next->cosa->caracteristica1) == 1){ //si es agujero infinito
            printf("-----------------------------\n");
            printf("Oh no! Te has pillado con un agujero infinito y vuelves al inicio del juego\n");
            printf("-----------------------------\n");
            (*(int*)esc->curr->next->cosa->caracteristica1) = 0; //se cambia a piso firme la casilla donde el pj murio
            if (esc->pos_pj != 0){
                elemento* auxiliar;
                auxiliar = (elemento*)malloc(sizeof(elemento));
                auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
                auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
                auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
                auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
                (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
                (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
                borrar_elemento(esc, esc->pos_pj);
                anadir_elemento(esc,auxiliar, 0, 1);
                esc->curr = esc->head;
                esc->pos_pj = 0;
                esc->posCurr = 0;
                return;
            }
            else{
                return;
            }
        }
        else if ((*(int*)esc->curr->next->cosa->caracteristica1) == 0){ //es piso firme
            printf("-----------------------------\n");
            printf("Caminaste por un suelo firme. Avanzas una casilla\n");
            printf("-----------------------------\n");
            borrar_elemento(esc, esc->pos_pj+1);
            if (esc->pos_pj == 0){
                anadir_piso(esc, 0);
            }
            else{
                anadir_piso(esc,esc->pos_pj-1);
            }
            esc->pos_pj++;
            esc->posCurr++;
            
        }
    }
    else if  (esc->curr->next->tipo == 2){ //es objeto
        printf("-------------------------------\n");
        printf("Te encontraste el objeto: %s\n", ((char*)esc->curr->next->cosa->caracteristica1));
        if ((*(int*)esc->curr->next->cosa->caracteristica2) == 1 ){
            (*(int*)esc->curr->cosa->caracteristica2) = 1;
            printf("El objeto te dio el estado de: Normal!\n");
        }
        else if ((*(int*)esc->curr->next->cosa->caracteristica2) == 2 ){
            (*(int*)esc->curr->cosa->caracteristica2) = 3;
            printf("El objeto te dio el estado de: Mareado!\n");
        }
        else if ((*(int*)esc->curr->next->cosa->caracteristica2) == 3 ){
            (*(int*)esc->curr->cosa->caracteristica2) = 4;
            printf("El objeto te dio el estado de: Wario!\n");
        }
        else{ // caracteristica de objeto 4=brillante
            (*(int*)esc->curr->cosa->caracteristica2) = 2;
            printf("El objeto te dio el estado de: Brillante!\n");
        }
        printf("-------------------------------\n");
        borrar_elemento(esc, esc->pos_pj+1);
        if (esc->pos_pj == 0){
            anadir_piso(esc, 0);
        }
        else{
            anadir_piso(esc,esc->pos_pj-1);
        }
        esc->pos_pj++;
        esc->posCurr++;
    }
    else if (esc->curr->next->tipo == 4){ //es bloque
        printf("-------------------------------\n");
        printf("Caminaste por debajo de un bloque, avanzas una casilla\n");
        printf("-------------------------------\n");
        elemento* auxiliar;
        auxiliar = (elemento*)malloc(sizeof(elemento));
        auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
        auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
        auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
        auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
        (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
        (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
        borrar_elemento(esc, esc->pos_pj);
        anadir_elemento(esc,auxiliar, esc->pos_pj+1, 1);
        esc->pos_pj++;
        esc->posCurr++;
    }
}
/*
void taclear_al_frente               -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario
------------------------------------
Funcion que mueve a nuestro personaje una casilla a la derecha
*/
void taclear_al_frente(escenario *esc){ //una a la derecha
    esc->curr = esc->head;
    esc->posCurr = 0;
    while (esc->posCurr != esc->pos_pj){
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
    if (esc->pos_pj == esc->length-1){
        printf("-------------------------------\n");
        printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
        printf("-------------------------------\n");
        esc->largo_inicial = 0;
        return;
    }
    if (esc->curr->next->tipo == 3){ //si es enemigo
        printf("-------------------------------\n");
        printf("Has matado a %s!\n", ((char*)esc->curr->next->cosa->caracteristica1));
        printf("-------------------------------\n");
        borrar_elemento(esc, esc->pos_pj+1);
        if (esc->pos_pj == 0){
            anadir_piso(esc, 0);
        }
        else{
            anadir_piso(esc,esc->pos_pj-1);
        }
        esc->pos_pj++;
        esc->posCurr++;
    }
    else if (esc->curr->next->tipo == 5){ //si es suelo
        if ((*(int*)esc->curr->next->cosa->caracteristica1) == 1){ //si es agujero infinito
            printf("-------------------------------\n");
            printf("Oh no! Te has pillado con un agujero infinito y vuelves al inicio del juego\n");
            printf("-------------------------------\n");
            (*(int*)esc->curr->next->cosa->caracteristica1) = 0; //se cambia a piso firme la casilla donde el pj murio
            elemento* auxiliar;
            auxiliar = (elemento*)malloc(sizeof(elemento));
            auxiliar->caracteristica1 = (char*)malloc(sizeof(char)*100);
            auxiliar->caracteristica1 = (char*)esc->curr->cosa->caracteristica1;
            auxiliar->caracteristica2 = (int*)malloc(sizeof(int));
            auxiliar->caracteristica3 = (int*)malloc(sizeof(int));
            (*(int*)auxiliar->caracteristica2) = (*(int*)esc->curr->cosa->caracteristica2);
            (*(int*)auxiliar->caracteristica3) = (*(int*)esc->curr->cosa->caracteristica3);
            borrar_elemento(esc, esc->pos_pj);
            anadir_elemento(esc,auxiliar, 0, 1);
            esc->curr = esc->head;
            esc->pos_pj = 0;
            esc->posCurr = 0;
        }
        else if ((*(int*)esc->curr->next->cosa->caracteristica1) == 0){ //si es piso firme
            printf("-------------------------------\n");
            printf("Has tacleado y no habian enemigos! Has entrado al estado mareado.\n");
            printf("-------------------------------\n");
            (*(int*)esc->curr->cosa->caracteristica2) = 3;
            //eliminar_delista(listaAcc, 1); //eliminar saltar de la lista de acciones disponibles
        }   
    }
    else{ //si es cualquier otro
        printf("-------------------------------\n");
        printf("Has tacleado y no habian enemigos! Has entrado al estado mareado.\n");
        printf("-------------------------------\n");
        (*(int*)esc->curr->cosa->caracteristica2) = 3;
    }   

}
/*
void ver_plata                   -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario
------------------------------------
Funcion que muestra por pantalla la cantidad de monedas actual de nuestro personaje
*/
void ver_plata(escenario* esc){
    esc->curr = esc->head;
    esc->posCurr = 0;
    while (esc->posCurr != esc->pos_pj){
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
    printf("Cantidad de monedas: %i\n", (*(int*)esc->curr->cosa->caracteristica3));
}
/*
acciones* fun_iniciales
-----------------------------------
Recibe como parametro un struct de acciones
------------------------------------
Funcion que crea una lista de acciones con todas las acciones que se podran realizar en un principio 
*/
acciones* fun_iniciales(acciones *acc){  //inicia todas las funciones que se pueden iniciar en un ppio (todas menos rushear)
    acc = CrearAcciones();
    acc->head->identificador = 1;
    acc->head->funcion= &saltar_encima;
    acc->head->next = CrearDun();
    acc->curr = acc->head->next;
    acc->curr->identificador = 2;
    acc->curr->funcion = &caminar_en;
    acc->curr->next = CrearDun();
    acc-> curr = acc->curr->next;
    acc->curr->identificador = 3;
    acc->curr->funcion = &taclear_al_frente;
    acc->curr->next = CrearDun();
    acc->curr = acc->curr->next;
    acc->curr->identificador = 5;
    acc->curr->funcion = &ver_plata;
    acc->curr->next = NULL;
    acc->tail = acc->curr;
    acc->length = 4; 
    return acc;
}
/*
void anadir_fun
-----------------------------------
Recibe como parametro un struct acciones y un entero i
------------------------------------
Funcion que agrega a la lista de acciones la funcion saltar_encima o rushear
*/
void anadir_fun(acciones *listaAcc, int i){ //i es el identificador, sera 1 (saltar) o 4 (rushear)
    dun* auxiliar;
    auxiliar = (dun*)malloc(sizeof(dun));
    if (i == 1){ //se agrega saltar_encima
        auxiliar->funcion = &saltar_encima; //siempre tendre a saltar en la cabeza 
        auxiliar->identificador = 1;
        auxiliar->next = listaAcc->head;
        listaAcc->head = auxiliar;
        listaAcc->curr = auxiliar;
    }
    else{
        auxiliar->funcion = &rushear; //siempre tendre a rushear en la cola
        auxiliar->identificador = 4;
        auxiliar->next = NULL;
        listaAcc->tail->next = auxiliar;
        listaAcc->tail = auxiliar;
    }
    listaAcc->length++;
}
/*
void casos
-----------------------------------
Recibe como parametro un struct de acciones y un struct de escenario
------------------------------------
Funcion auxiliar que revisa el estado del personaje y con flags de la funcion "en_lista" revisa si agregar o quitar "saltar_encima" y "rushear"
*/
void casos(acciones* listaAcc, escenario *esc){
    esc->curr = esc->head;
    esc->posCurr = 0;
    while (esc->posCurr != esc->pos_pj){
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
    int estado;
    estado = (*(int*)esc->curr->cosa->caracteristica2);
    if (estado == 1){
        if (en_lista(listaAcc, 1) == 0 ){
            anadir_fun(listaAcc, 1);
        }
        if ( en_lista( listaAcc, 4) == 1){
            eliminar_delista(listaAcc, 4);
        }
        else{
            return;
        }  
    }
    else if (estado == 2){
        if (en_lista(listaAcc, 4) == 0){
            anadir_fun(listaAcc, 4);
        }
        if (en_lista(listaAcc, 1) == 0){
            anadir_fun(listaAcc,1);
        }
        else{
            return;
        }
    }
    else if (estado == 3){
        if (en_lista(listaAcc, 1) == 1){
            eliminar_delista(listaAcc,1);
        }
        if (en_lista(listaAcc,4) == 1 ){
            eliminar_delista(listaAcc,4);
        }
        else{
            return;
        }
    }
    else{
        if (en_lista(listaAcc, 1) == 0){
            anadir_fun(listaAcc,1);
        }
        if (en_lista(listaAcc,4) == 1){
            eliminar_delista(listaAcc,4);
        }
        else{
            return;
        }
    }
    return;
}
/*
void choice                         -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un entero accion, un struct acciones y un struct escenario.
------------------------------------
Funcion que segun el entero accion recibido, verifica si su funcion se encuentra en la lista de acciones y la ejecuta
*/
void choice( int accion, acciones* listaAcc, escenario* esc){
    int i;
    listaAcc->curr = listaAcc->head;
    listaAcc->posCurr = 0;
    int bandera = 0;
    for (i=0; i < listaAcc->length; i++){
        if (accion == listaAcc->curr->identificador){
            bandera = 1;
        }
        else{
            listaAcc->curr = listaAcc->curr->next;
        }
    }
    if (bandera == 0){
        printf("---------------------\n");
        printf("OH OH!\n");
        printf("---------------------\n");
        return;
    }
    else{
        if (accion== 2){ //caminar
            (listaAcc->curr->funcion)(esc);
            if (esc->largo_inicial != 0){
                printf("HICE caminar_en\n");
                printf("------------------\n");
            }
            else{
                return;
            }
        }
        else if (accion == 3){ //taclear
            (listaAcc->curr->funcion)(esc);
            if (esc->largo_inicial != 0){
                printf("HICE taclear_al_frente\n");
                printf("------------------\n");
            }
            else{
                return;
            }
        }
        else if (accion == 4){ //rushear
            (listaAcc->curr->funcion)(esc);
            if (esc->largo_inicial != 0){
                printf("HICE rushear\n");
                printf("------------------\n");
            }
            else{
                return;
            }
        }
        else if (accion == 5){ //ver plata
            (listaAcc->curr->funcion)(esc);
            if (esc->largo_inicial != 0){
                printf("HICE ver_plata\n");
                printf("------------------\n");
            }
            else{
                return;
            }
        }
        else if ( accion == 1){ //saltar
            int salto;
            printf("¿Cuantas casillas desea saltar?: ");
            scanf("%i", &salto);
            (listaAcc->curr->funcion)(esc, salto);
            if (esc->largo_inicial != 0){
                printf("HICE saltar_encima\n");
                printf("------------------\n");
            }
            else{
                return;
            }
        }
    }
   return;
}
/*
void borrar_accall
-----------------------------------
Recibe como parametro un struct acciones
------------------------------------
Funcion que borra todos los dun de la lista de acciones
*/
void borrar_accall(acciones* listaAcc){
    listaAcc->posCurr = 0;
    listaAcc->curr = listaAcc->head;
    while (listaAcc->length > 0){
        borrar_dun(listaAcc, listaAcc->posCurr);
    }
}