#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "escenario.h"

/*
casilla* CrearCasilla()
-----------------------------------
No recibe ningun parametro
------------------------------------
Funcion constructora de una casilla
*/
casilla* CrearCasilla(){
    casilla* nome;
    nome = (casilla*)malloc(sizeof(casilla));
    nome->cosa= (elemento*)malloc(sizeof(elemento));
    nome->cosa->caracteristica1 = nome->cosa->caracteristica2 = nome->cosa->caracteristica3 = NULL;
    nome->tipo = 0;
    nome->next = (casilla*)malloc(sizeof(casilla));
    return nome;
    }
/*
escenario* CrearEscenario()
-----------------------------------
No recibe ningun parametro
------------------------------------
Funcion constructora de un escenario
*/
escenario* CrearEscenario(){
    escenario *esc;
    esc = (escenario*)malloc(sizeof(escenario));
    esc->head = esc->curr = esc->tail = (casilla*)malloc(sizeof(casilla));
    esc->head = esc->tail = esc->curr = NULL;
    esc->length =  esc->posCurr = esc->largo_inicial = esc->pos_pj = 0;
    return esc;
}

//funcion destructora de una casilla
void DestruirCasilla(casilla* nodo){
    free(nodo);
}
void DestruirElemento(elemento* ele){
    free(ele);
}
//funcion destructora de un escenario
void DestruirLista(escenario* esc){
    free(esc);
}
/*
void mostrar                                 -FUNCION PEDIDA EN ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario y un entero i
------------------------------------
Muestra el contenido de una casilla, cuya posicion es i
*/
void mostrar(escenario* esc, int i){
    esc->curr= esc->head;
    esc->posCurr= 0;
    if (i >= esc->length){ //si no hay lista
        if (i > esc->length){
            printf("--------------\n");
            printf("Invalido. Tu juego solo tiene %i niveles. No existe el %i.\n", esc->length, i);
            printf("--------------\n");
        }
        else{
            printf("--------------\n");
            printf("Posicion invalida. %i es el largo del juego, cuya posicion en niveles es el %i.\n", esc->length, esc->length-1);
            printf("--------------\n");
        }
    }
    else{
        while (i > esc->posCurr){
            esc->curr = esc->curr->next;
            esc->posCurr++;
        }
    
        printf("--------------\n");
        if (esc->curr->tipo == 1){ //si es un personaje
            int estado=0;
            printf("Personaje\n");
            printf("Nombre: %s\n", ((char*)esc->curr->cosa->caracteristica1));
            estado = (*(int*)esc->curr->cosa->caracteristica2);
            if (estado == 1){
                printf("Estado: Normal\n");
            }
            else if (estado == 2){
                printf("Estado: Brillante\n");
            }
            else if (estado == 3){
                printf("Estado: Mareado\n");
            }
            else{
                printf("Estado: Wario\n");
            }
            printf("Cantidad de monedas: %i\n", (*(int*)esc->curr->cosa->caracteristica3));
        }
        else if (esc->curr->tipo == 2){ //si es objeto
            int estado= 0;
            printf("Objeto\n");
            printf("Nombre: %s\n", ((char*)esc->curr->cosa->caracteristica1));
            estado= (*(int*)esc->curr->cosa->caracteristica2);
            if (estado == 1){
                printf("Estado: Health\n");
            }
            else if (estado == 2){
                printf("Estado: Mareado\n");
            }   
            else if (estado == 3){
                printf("Estado: Wario\n");
            }
            else{
                printf("Estado: Brillante\n");
            }
        }
        else if (esc->curr->tipo == 3){ //si es un enemigo
            printf("Enemigo\n");
            printf("Nombre: %s\n", ((char*)esc->curr->cosa->caracteristica1));
        }
        else if (esc->curr->tipo == 4){ //si es un bloque
            printf("Bloque\n");  
            if ((*(int*)esc->curr->cosa->caracteristica2) == 0){
                printf("Cantidad de monedas: %i\n", (*(int*)esc->curr->cosa->caracteristica1));
            }
            else{
                printf("Nombre: %s\n", ((char*)esc->curr->cosa->caracteristica1));
                if ((*(int*)esc->curr->cosa->caracteristica2) == 1){
                    printf("Estado: Health\n");
                }
                else if ((*(int*)esc->curr->cosa->caracteristica2) == 2){
                    printf("Estado: Mareado\n");
                }   
                else{
                    printf("Estado: Wario\n");
                }
            }
        }
        else if (esc->curr->tipo == 5){ //es suelo
            //int piso;
            //piso = (*(int*)esc->curr->cosa->caracteristica1);
            printf("Suelo\n");
            if ((esc->curr->cosa->caracteristica1 == 0) || (*(int*)esc->curr->cosa->caracteristica1 == 0)){
                printf("Piso firme\n");
            }
            else{
                printf("Agujero infinito\n");
            }
        }
        printf("--------------\n");
    }
}   
/*
void mostrar_todo                              -FUNCION PEDIDA EN ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario 
------------------------------------
Muestra el contenido de todas las casillas existentes en el escenario
*/
void mostrar_todo(escenario* esc){
    esc->curr = esc->head;
    esc->posCurr = 0;
    if (esc->length == 0){
        printf("--------------\n");
        printf("No hay lista\n");
        printf("--------------\n");
    }
    while (esc->posCurr < esc->length){
        mostrar(esc, esc->posCurr);
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
}
/*
void anadir_elemento                                -FUNCION PEDIDA EN ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario, un struct elemento, un entero i que indica posicion y un entero tipe que indica tipo de elemento.
------------------------------------
Anade un elemento (ele) de tipo (tipe) en la posicion i del escenario 
*/
void anadir_elemento(escenario* esc, elemento* ele, int i, int tipe){
    casilla* agregada;
    agregada = CrearCasilla();
    agregada->tipo = tipe;
    agregada->cosa = ele;
    agregada->next = NULL;
    if (i > esc->largo_inicial){
        printf("--------------\n");
        printf("Numero ingresado es mayor a la cantidad de niveles.\n");
        printf("--------------\n");
        return;
    }
    else if ( esc->largo_inicial == esc->length){
        printf("--------------\n");
        printf("No se puede agregar niveles. Elimine uno primero.\n");
        printf("--------------\n");
        return;
    }
    
    else{
        if ( i == 0){ //si se quiere agregar en la cabeza
            agregada->next=esc->head;
            esc->head = esc->curr = agregada;
        }
        else{ //se quiere agregar en otra posicion
            esc->curr = esc->head;
            esc->posCurr = 0;
            while (esc->posCurr < i){
                esc->curr = esc->curr->next;
                esc->posCurr++;
            }
            agregada->next = esc-> curr;
            esc->curr = esc->head;
            esc->posCurr = 0;
            while (esc->posCurr < i-1){
                esc->curr = esc->curr->next;
                esc->posCurr++;
            }
            esc->curr->next = agregada;
        }
    }
    while (esc->tail->next != NULL){
        esc->curr = esc->tail;
        esc->tail = esc->tail->next;
    }
    esc->length++;
     return;   
}

/*
void personaje
-----------------------------------
Recibe como parametro un struct escenario 
------------------------------------
Funcion auxiliar que ayuda a la creacion de nuestro personaje
*/
void personaje(escenario* esc){
    printf("¿Como desea nombrar a su personaje?\n");
    printf("Nombre: ");
    esc->head->cosa->caracteristica1 = (char*)malloc(sizeof(char)*100);
    esc->head->cosa->caracteristica2 = (int*)malloc(sizeof(int));
    esc->head->cosa->caracteristica3 = (int*)malloc(sizeof(int));
    scanf("%s", (char*)esc->head->cosa->caracteristica1);
    esc->head->tipo = 1;
    (*(int*)esc->head->cosa->caracteristica2) = 1; //iniciar personaje como normal
    (*(int*)esc->head->cosa->caracteristica3) = 0;
    esc->curr = esc->curr->next;
}

/*
elemento* objeto
-----------------------------------
No recibe parametro
------------------------------------
Funcion auxiliar que ayuda a la creacion de un elemento "objeto" y lo retorna para poder anadirlo
*/
elemento* objeto(){
    elemento *auxi;
    auxi = (elemento*)malloc(sizeof(elemento));
    int estado;
    printf("¿Como desea nombrar al objeto?: ");
    auxi->caracteristica1 = (char*)malloc(sizeof(char)*100);
    scanf("%s",(char*)auxi->caracteristica1);
    printf("¿Que estado otorgara este objeto?\n");
    printf("1. Health.\n");
    printf("2. Mareado.\n");
    printf("3. Wario.\n");
    printf("4. Brillante.\n");
    printf("Ingrese una opcion: ");
    scanf("%i",&estado);
    auxi->caracteristica2 = (int*)malloc(sizeof(int));
    (*(int*)auxi->caracteristica2) = estado;
    auxi->caracteristica3 = NULL;
    return auxi;
}
/*
elemento* enemigo
-----------------------------------
No recibe parametro
------------------------------------
Funcion auxiliar que ayuda a la creacion de un elemento "enemigo" y lo retorna para poder anadirlo
*/
elemento* enemigo(){
    elemento *auxi;
    auxi = (elemento*)malloc(sizeof(elemento));
    printf("¿Cual sera el nombre del malvado enemigo?: ");
    auxi->caracteristica1 = (char*)malloc(sizeof(char)*100);
    scanf("%s",(char*)auxi->caracteristica1);
    auxi->caracteristica2 = NULL;
    auxi->caracteristica3 = NULL;
    return auxi;
}
/*
elemento* suelo
-----------------------------------
No recibe parametro
------------------------------------
Funcion auxiliar que ayuda a la creacion de un elemento "suelo" y lo retorna para poder anadirlo
*/
elemento* suelo(){
    elemento *auxi;
    auxi = (elemento*)malloc(sizeof(elemento));
    int suelo;
    printf("Que tipo de suelo tendra este nivel?\n");
    printf("1. Piso firme.\n");
    printf("2. Agujero infinito!!!\n");
    printf("Ingrese una opcion:");
    scanf("%i",&suelo);
    if (suelo == 1){ //piso firme
        auxi->caracteristica1 = (int*)malloc(sizeof(int));
        (*(int*)auxi->caracteristica1) = 0;
        auxi->caracteristica2 = NULL;
        auxi->caracteristica3 = NULL;
    }
    else{ //agujero infinito
        auxi->caracteristica1 = (int*)malloc(sizeof(int));
        (*(int*)auxi->caracteristica1) = 1;
        auxi->caracteristica2 = NULL;
        auxi->caracteristica3 = NULL;
    }
    return auxi;
}
/*
elemento* bloque
-----------------------------------
No recibe parametro
------------------------------------
Funcion auxiliar que ayuda a la creacion de un elemento "bloque" y lo retorna para poder anadirlo
*/
elemento* bloque(){
    elemento *auxi;
    auxi = (elemento*)malloc(sizeof(elemento));
    int tipo;
    int cant;
    printf("¿Que tipo de bloque desea agregar?\n");
    printf("1. MONEDAS!\n");
    printf("2. Objeto.\n");
    printf("Ingrese una opcion:");
    scanf("%i", &tipo);
    if (tipo == 1){
    printf("¿Cuantas monedas?:");
    scanf("%i", &cant);
    auxi->caracteristica1 = (int*)malloc(sizeof(int));
    auxi->caracteristica2 = (int*)malloc(sizeof(int));
    (*(int*)auxi->caracteristica1) = cant;
    (*(int*)auxi->caracteristica2) = 0;
    auxi->caracteristica3 = NULL;
    } 
    else{ //obj
        int estado;
        printf("¿Como desea nombrar al objeto?: ");
        auxi->caracteristica1 = (char*)malloc(sizeof(char)*100);
        scanf("%s",(char*)auxi->caracteristica1);
        printf("¿Que estado otorgar a este objeto?\n");
        printf("1. Health.\n");
        printf("2. Mareado.\n");
        printf("3. Wario.\n");
        printf("4. Brillante.\n");
        printf("Ingrese una opcion: ");
        scanf("%i",&estado);
        auxi->caracteristica2 = (int*)malloc(sizeof(int));
        auxi->caracteristica3 = (int*)malloc(sizeof(int));
        (*(int*)auxi->caracteristica3) = estado;
        (*(int*)auxi->caracteristica2) = 1;
    } 
    return auxi;
}
/*
void borrar_elemento              -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario y un entero i
------------------------------------
Funcion que borra un elemento del escenario ubicado en la posicion i
*/
void borrar_elemento(escenario* esc, int i){
    int cont;
    if (i >= esc->length){
        printf("No existe posicion.\n");
        return;
    }
    esc->posCurr = 0;
    esc->curr = esc->head;
    casilla* auxiliar;
    auxiliar= (casilla*)malloc(sizeof(casilla));
    if (i == 0){ //si se quiere eliminar la cabeza
        auxiliar = esc->head;
        esc->head = esc->curr->next;
        esc->curr = esc->head;
    }
    else{ //de otro lugar
        for(cont=0; cont<i-1; cont++){ //termina en el anterior a la posicion que quiero borrar
            esc->curr = esc->curr->next;
            esc->posCurr++;
        }
        if (esc->curr->next == esc->tail){
            auxiliar = esc->tail;
        }
        else{
            auxiliar= esc->curr->next;
            esc->curr->next = auxiliar->next;
        }
    }
    esc->length--;
    DestruirElemento(auxiliar->cosa);
    DestruirCasilla(auxiliar);
}
/*
void borrar_todo                    -FUNCION PEDIDA POR ENUNCIADO
-----------------------------------
Recibe como parametro un struct escenario
------------------------------------
Borra toda casilla y elemento del escenario.
*/
void borrar_todo(escenario* esc){
    esc->posCurr = 0;
    esc->curr = esc->head;
    while (esc->length > 0){
        borrar_elemento(esc, esc->posCurr);
    }
}
/*
escenario* crear_niveles
-----------------------------------
Recibe como parametro un struct escenario y un entero cant
------------------------------------
Funcion auxiliar que ayuda a la creacion de un escenario basico, cuyas casillas seran todas de tipo suelo firme
*/
escenario* crear_niveles(escenario *esc, int cant){ //inicia "cant" niveles como piso firme
    casilla* creadora;
    esc->posCurr = 0;
    esc->curr = esc->head;
    creadora = CrearCasilla();
    esc->curr = esc->head = esc->tail = creadora;
    esc->curr->tipo = 5;
    esc->curr->cosa->caracteristica1 = (int*)malloc(sizeof(int));
    esc->curr->cosa->caracteristica1 = 0;
    esc->curr->cosa->caracteristica2 = esc->curr->cosa->caracteristica3 = NULL;
    esc->curr->next = NULL;
    while (esc->posCurr < cant){
        creadora = CrearCasilla();
        esc->curr->next = creadora;
        creadora->tipo = 5;
        esc->curr->cosa->caracteristica1 = (int*)malloc(sizeof(int));
        creadora->cosa->caracteristica1 = 0;
        creadora->cosa->caracteristica2 = creadora->cosa->caracteristica3 = NULL;
        esc->curr = esc->curr->next;
        esc->posCurr++;
    }
    esc->tail = esc->curr; //el ultimo elemento del while sera la cola
    esc->curr->next = NULL;
    free(creadora);
    return esc;
}

