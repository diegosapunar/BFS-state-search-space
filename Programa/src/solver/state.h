#pragma once
#include "arraylist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
// #include "queue.h"

/* Estructura de mi State */ 
struct state 
{
    ArrayList* arraylist;       // array, que es la matriz
    int position_cero;          // Posicion del cero, para mas facil los calculos
    struct state* father;       // Puntero al padre, para luego sacar la respuesta
    int parent_x;               // Posicion x de la ficha que se movio para crearlo
    int parent_y;               // Posicion y de la ficha que se movio para crearlo

    int hash;                   // Correspondiente al Hash value de el etado

    // int alocados;            // Quiere decir cuantos casilleros estan mal alocados
};

typedef struct state State;

//////////////////////////////////////////////////////////////////////////
//                             Funciones                                //
//////////////////////////////////////////////////////////////////////////

/* Creo un State vacio, retorno el puntero */ 
State* state_init(int n);

/* Printear el State de manera bonita */ 
void state_print(State* state, int n);

/* Inserto elemento a mi State */ 
void state_insert(State* state, int element, int position);

/* Comparo dos estados, retorno boolean */
bool state_compare(State* state1, State* state2, int n);

/* Veo si el estado es solucion, retorno boolean */
int state_is_solution(State* state, int n);

/* Genero el State up, retorno state */
State* state_son_up(State* state, int n, ArrayList** cubo);

/* Genero el State right, retorno state */
State* state_son_right(State* state, int n, ArrayList** cubo);

/* Genero el State down, retorno state */
State* state_son_down(State* state, int n, ArrayList** cubo);

/* Genero el State left, retorno state */
State* state_son_left(State* state, int n, ArrayList** cubo);

/*  A partir de una position, retornar x,y 
    La position a retonar es es x,y. */
void state_set_parent_position(int position, int n, State *state);

void state_destroy(State* state);

// /* Solo para el estado inicial, asignar cuantos alocados tiene */
// void state_initial_alocados(State* state, int n);

// /* Cambia alocado en base a los dos casilleros q cambiaron */
// void state_change_alocados(State* state, int pos1, int n); 