#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_

typedef struct elemento{ 
    void* caracteristica1;
    void* caracteristica2;
    void* caracteristica3;
} elemento;

typedef struct casilla{ //nodo
    struct elemento* cosa;
    int tipo; //1 personaje, 2 objeto, 3 enemigo, 4 bloque, 5 suelo
    struct casilla* next;
} casilla;

typedef struct escenario{ //lista
    struct casilla* curr;
    struct casilla* head;
    struct casilla* tail;
    int length;
    int posCurr;
    int largo_inicial;
    int pos_pj;
} escenario;

#endif

casilla* CrearCasilla();
escenario* CrearEscenario();
void DestruirCasilla(casilla* nodo);
void DestruirLista(escenario* esc);
void mostrar(escenario* esc, int i);
void mostrar_todo(escenario* esc);
void anadir_elemento(escenario* esc, elemento* ele, int i, int tipe);
void personaje(escenario* esc);
elemento* objeto();
elemento* enemigo();
elemento* suelo();
elemento* bloque();
void borrar_elemento(escenario* esc, int i);
void borrar_todo(escenario* esc);
escenario* crear_niveles(escenario *esc, int cant);