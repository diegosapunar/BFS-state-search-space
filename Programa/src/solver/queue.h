#pragma once
#include "state.h"

// Source: mi propio codigo, esta en mis repos publicos.

/* Estructura de un nodo de la lista */
struct node
{
    State* value;           // El valor del Nodo, que es un State
    struct node *next;      // Puntero al siguiente Nodo
};

typedef struct node Node;

/* Estructura de la lista ligada */
struct queue
{
    Node* first; // Puntero al primer Nodo
    Node* last;  // Puntero al ultimo Nodo
    int count;   // Cantidad de Nodos
};

typedef struct queue Queue;

//////////////////////////////////////////////////////////////////////////
//                             Funciones                                //
//////////////////////////////////////////////////////////////////////////

/* Crea un Cola vacia */
Queue* queue_init();

/* Agrega alfinal de la cola el elemento */
void queue_push(Queue* cola, State* state); 

/* Saco la cabeza de la cola, es decir, FIFO. Retorna puntero a State
    Tambien elimina el nodo de la cola
 */ 
State* queue_pop_left(Queue* cola);

void queue_destroy(Queue* queue);