#include "escenario.h"

#ifndef _ACCIONES_H_
#define _ACCIONES_H_


typedef struct dun{
    void (*funcion)();
    int identificador;
    struct dun* next;
} dun;
typedef struct acciones{
    struct dun* curr;
    struct dun* head;
    struct dun* tail;
    int length;
    int posCurr;
} acciones;

#endif

dun* CrearDun();
acciones* CrearAcciones();
void DestruirDun(dun* algo);
void borrar_dun(acciones* acc, int eliminado);
void anadir_piso(escenario *esc, int i);
void eliminar_delista(acciones* listaAcc, int eliminado);
int en_lista(acciones* listaAcc, int identificador);
void saltar_encima(escenario* esc, int i);
void rushear(escenario* esc);
void caminar_en(escenario* esc);
void taclear_al_frente(escenario *esc);
void ver_plata(escenario* esc);
acciones* fun_iniciales(acciones *acc);
void anadir_fun(acciones *listaAcc, int i);
void casos(acciones* listaAcc, escenario *esc);
void choice( int accion, acciones* listaAcc, escenario* esc);
void borrar_accall(acciones* listaAcc);
