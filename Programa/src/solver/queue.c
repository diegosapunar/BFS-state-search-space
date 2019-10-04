#include "queue.h" // Estructuras de Queue
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
//                             Funciones                                //
//////////////////////////////////////////////////////////////////////////

/* Crear Nodo con el valor pointer al state, y retorna un puntero al nodo. */
Node* node_init(State* state)
{
    Node* node = malloc(sizeof(Node)); // Creo el Nodo asignandole espacio de memoria

    node -> value = state; // Le asigno state al atributo value
    node -> next = NULL;   // Le asigno next como NULL

    return node; // Retorno el Nodo
}

/* Crea un cola vacia */
Queue* queue_init()
{
    Queue* cola = malloc(sizeof(Queue)); // Creo el Nodo asignandole espacio de memoria

    cola -> first = NULL;       // Le asigno al atributo first NULL
    cola -> last = NULL;        // Le asigno al atributo last NULL
    cola -> count = 0;          // Le asigno al atributo count como 0

    return cola;
}

/* Agrega alfinal de la cola el elemento */
void queue_push(Queue *cola, State *state)
{
    Node* node = node_init(state); // Creo el Nodo a apendear

    if (cola -> count == 0)
    {   // Si la lista esta vacia
        cola -> first = node; // El Nodo que ingresa es el primero
    }
    else
    {
        cola -> last -> next = node; // El Nodo que ingresa es el despues del ultimo
    }

    cola -> last = node; // El Nodo que ingresa es el ultimo

    cola -> count++; // Se aumenta la cuenta de la lista
};

/*  Saco la cabeza de la cola, es decir, FIFO. Retorna puntero a State
    Tambien elimina el nodo de la cola. */
State* queue_pop_left(Queue* cola)
{
    State* state = NULL;                       // Valor a retornar

    if (cola -> count) {                    // No esta vacia
        state = cola -> first -> value;     // El valor a retornar toma el valor de la cabeza de la lista

        Node* node = cola->first;           // Guardo el Nodo a eliminar
        cola -> first = node -> next;

        free(node);                         // Libero memoria del Nodo a eliminar

        cola -> count--;                    // Disminuyo la cuenta de la lista
    }
    
    return state;
};

void queue_destroy(Queue *queue)
{
    while (queue->count)
    {
        queue_pop_left(queue);
    }
    free(queue);
};