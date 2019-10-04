#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

#define MOD(a, b) ((((a) % (b)) + (b)) % (b))

//////////////////////////////////////////////////////////////////////////
//                             Funciones                                //
//////////////////////////////////////////////////////////////////////////

/* Creo un State vacio, retorno el puntero */
State* state_init(int n)
{
    // Asigno memoria a mi nuevo state
    State* state = malloc(sizeof(State));

    // Inizialiso los atributos
    state -> arraylist = arraylist_init(n);
    state ->father = NULL;

    state -> hash = 0;

    return state;
};

/* Printear el State de manera bonita, recibo el State a printear */
void state_print(State* state, int n)
{
    printf("HASH: %d\n", state -> hash);
    arraylist_print(state -> arraylist, n);
    printf("\n");
};

/* Inserto elemento a mi State en la posicion asignada */
void state_insert(State* state, int element, int position)
{
    // Veo si el elemento es cero, para asignar el atributo
    if (element == 0) {                    
        state -> position_cero = position;
    }
    arraylist_insert(state -> arraylist, element, position);
};

/* Comparo dos estados, retorno boolean */
bool state_compare(State* state1, State* state2, int n)
{
    for(int i = 0; i < n; i++)
    {
        if (state1 -> arraylist -> array[i] != state2 -> arraylist -> array[i]) {
            return false;
        }
    }
    return true;
};

/* Veo si el estado es solucion, retorno boolean */
int state_is_solution(State* state, int n)
{
    // if (state->alocados) {
    //     return 0;
    // }
    // else
    // {
    //     return 1;
    // }
    
    if (n==3) {
        int myArr[9] = {1,2,3,4,5,6,7,8,0};

        for (int i = 0; i < n*n; i++)
        {
            if (state->arraylist->array[i] != myArr[i])
            {
                return 0;
            }
        }
        return 1;
    }
    else {
        int myArr[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

        for (int i = 0; i < n*n; i++)
        {
            if (state->arraylist->array[i] != myArr[i])
            {
                return false;
            }
        }
        return true;
    }

};

/* Genero el State up, retorno state */
State* state_son_up(State* state, int n, ArrayList** cubo)
{
    // Creo el estado del nuevo hijo
    State* state_new = state_init(n);

    int pos1 = state -> position_cero;  // Donde esta el cero
    int pos2 = MOD(pos1-n, n*n);        // Donde tiene que ir el cero

    // Primero le asigno el hash del padre, y le resto las dos posiciones en cuestion
    state_new -> hash = state -> hash;
    state_new -> hash = state_new -> hash ^ cubo[state -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos2] -> array[state->arraylist->array[pos2]];


    // Tengo q recorrer todo el padre, e ir asignando correctamente
    for(int i = 0; i < n*n; i++)
    {   
        if (i == pos1) {                // Poner en ese i al que esta en pos2
            state_new->arraylist->array[i] = state->arraylist->array[pos2];
        }
        else if(i == pos2) {            // Poner en ese al que esta en la pos1
            state_new->arraylist->array[i] = state->arraylist->array[pos1];
        }
        else {                          // Poner tal cual
            state_new->arraylist->array[i] = state->arraylist->array[i];
        }
    }
    // Asigno al padre
    state_new -> father = state;
    // Aisgno donde quedo el cero
    state_new -> position_cero = pos2;

    state_set_parent_position(pos2, n, state_new);

    // Voy a agregar los xor correspondientes
    state_new -> hash = state_new -> hash ^ cubo[state_new -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos1] -> array[state_new->arraylist->array[pos1]];

    return state_new;
};

/* Genero el State right, retorno state */
State* state_son_right(State* state, int n, ArrayList** cubo)
{
    State* state_new = state_init(n);

    // state_new->alocados = state->alocados;

    int pos1 = state->position_cero; // Donde esta el cero
    int pos2 = pos1 + 1;             // Donde tiene que ir el cero
    if ((MOD(pos2,n)) == 0) {
        pos2 = pos2 - n;
    }

    // Primero le asigno el hash del padre, y le resto las dos posiciones en cuestion
    state_new -> hash = state -> hash;
    state_new -> hash = state_new -> hash ^ cubo[state -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos2] -> array[state->arraylist->array[pos2]];

    for (int i = 0; i < n * n; i++)
    {
        if (i == pos1)
        { // Poner en ese i al que esta en pos2
            state_new->arraylist->array[i] = state->arraylist->array[pos2];
        }
        else if (i == pos2)
        { // Poner en ese al que esta en la pos1
            state_new->arraylist->array[i] = state->arraylist->array[pos1];
        }
        else
        { // Poner tal cual
            state_new->arraylist->array[i] = state->arraylist->array[i];
        }
    }
    state_new->father = state;
    state_new->position_cero = pos2;

    state_set_parent_position(pos2, n, state_new);

    // Voy a agregar los xor correspondientes
    state_new -> hash = state_new -> hash ^ cubo[state_new -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos1] -> array[state_new->arraylist->array[pos1]];

    return state_new;
};

/* Genero el State down, retorno state */
State* state_son_down(State* state, int n, ArrayList** cubo)
{
    State *state_new = state_init(n);

    // state_new->alocados = state->alocados;

    int pos1 = state->position_cero; // Donde esta el cero
    int pos2 = MOD(pos1 + n, n * n); // Donde tiene que ir el cero

    // Primero le asigno el hash del padre, y le resto las dos posiciones en cuestion
    state_new -> hash = state -> hash;
    state_new -> hash = state_new -> hash ^ cubo[state -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos2] -> array[state->arraylist->array[pos2]];

    for (int i = 0; i < n * n; i++)
    {
        if (i == pos1)
        { // Poner en ese i al que esta en pos2
            state_new->arraylist->array[i] = state->arraylist->array[pos2];
        }
        else if (i == pos2)
        { // Poner en ese al que esta en la pos1
            state_new->arraylist->array[i] = state->arraylist->array[pos1];
        }
        else
        { // Poner tal cual
            state_new->arraylist->array[i] = state->arraylist->array[i];
        }
    }
    state_new->father = state;
    state_new->position_cero = pos2;

    state_set_parent_position(pos2, n, state_new);

    // Voy a agregar los xor correspondientes
    state_new -> hash = state_new -> hash ^ cubo[state_new -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos1] -> array[state_new->arraylist->array[pos1]];

    return state_new;
};

/* Genero el State left, retorno state */
State* state_son_left(State* state, int n, ArrayList** cubo)
{
    State *state_new = state_init(n);

    // state_new->alocados = state->alocados;

    int pos1 = state->position_cero; // Donde esta el cero
    int pos2 = pos1 - 1;             // Donde tiene que ir el cero
    if ((MOD(pos1, n)) == 0)
    {
        pos2 = pos1 + n - 1;
    }

    // Primero le asigno el hash del padre, y le resto las dos posiciones en cuestion
    state_new -> hash = state -> hash;
    state_new -> hash = state_new -> hash ^ cubo[state -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos2] -> array[state->arraylist->array[pos2]];

    for (int i = 0; i < n * n; i++)
    {
        if (i == pos1)
        { // Poner en ese i al que esta en pos2
            state_new->arraylist->array[i] = state->arraylist->array[pos2];
        }
        else if (i == pos2)
        { // Poner en ese al que esta en la pos1
            state_new->arraylist->array[i] = state->arraylist->array[pos1];
        }
        else
        { // Poner tal cual
            state_new->arraylist->array[i] = state->arraylist->array[i];
        }
    }
    state_new->father = state;
    state_new->position_cero = pos2;

    state_set_parent_position(pos2, n, state_new);

    // Voy a agregar los xor correspondientes
    state_new -> hash = state_new -> hash ^ cubo[state_new -> position_cero] -> array[0];
    state_new -> hash = state_new -> hash ^ cubo[pos1] -> array[state_new->arraylist->array[pos1]];

    return state_new;
};

/*  A partir de una position, retornar x,y 
    La position a retonar es es x,y. */
void state_set_parent_position(int position, int n, State* state)
{

    if (n == 3) {
        if (position == 0) {
            state -> parent_x = 0;
            state->parent_y = 0;
        }
        else if (position == 1)
        {
            state -> parent_x = 1;
            state->parent_y = 0;
        }
        else if (position == 2)
        {
            state -> parent_x = 2;
            state->parent_y = 0;
        }
        else if (position == 3)
        {
            state -> parent_x = 0;
            state->parent_y = 1;
        }
        else if (position == 4)
        {
            state -> parent_x = 1;
            state->parent_y = 1;
        }
        else if (position == 5)
        {
            state -> parent_x = 2;
            state->parent_y = 1;
        }
        else if (position == 6)
        {
            state -> parent_x = 0;
            state->parent_y = 2;
        }
        else if (position == 7)
        {
            state -> parent_x = 1;
            state->parent_y = 2;
        }
        else {  // position = 8
            state -> parent_x = 2;
            state->parent_y = 2;
        }   
    }
    
    // n = 4
    else
    {
        if (position == 0)
        {
            state->parent_x = 0;
            state->parent_y = 0;
        }
        else if (position == 1)
        {
            state->parent_x = 1;
            state->parent_y = 0;
        }
        else if (position == 2)
        {
            state->parent_x = 2;
            state->parent_y = 0;
        }
        else if (position == 3)
        {
            state->parent_x = 3;
            state->parent_y = 0;
        }
        else if (position == 4)
        {
            state->parent_x = 0;
            state->parent_y = 1;
        }
        else if (position == 5)
        {
            state->parent_x = 1;
            state->parent_y = 1;
        }
        else if (position == 6)
        {
            state->parent_x = 2;
            state->parent_y = 1;
        }
        else if (position == 7)
        {
            state->parent_x = 3;
            state->parent_y = 1;
        }
        else if (position == 8)
        {
            state->parent_x = 0;
            state->parent_y = 2;
        }
        else if (position == 9)
        {
            state->parent_x = 1;
            state->parent_y = 2;
        }
        else if (position == 10)
        {
            state->parent_x = 2;
            state->parent_y = 2;
        }
        else if (position == 11)
        {
            state->parent_x = 3;
            state->parent_y = 2;
        }
        else if (position == 12)
        {
            state->parent_x = 0;
            state->parent_y = 3;
        }
        else if (position == 13)
        {
            state->parent_x = 1;
            state->parent_y = 3;
        }
        else if (position == 14)
        {
            state->parent_x = 2;
            state->parent_y = 3;
        }
        else // position = 15
        {
            state->parent_x = 3;
            state->parent_y = 3;
        }
    }
    
};

// /* Solo para el estado inicial, asignar cuantos alocados tiene */
// void state_initial_alocados(State* state, int n)
// {
//     // CASO BORDE: el cero, el for va solo hasta el penultimo
//     if (state->arraylist->array[n*n - 1] != 0)
//     {
//         state->alocados++;
//     }
//     for(int i = 0; i < (n*n) - 1; i++)
//     {

//         // En el caso que la casilla i este cn el numero incorrecto
//         if (state -> arraylist -> array[i] != i + 1) {
//             state -> alocados++;
//         }
//     }
// };

// /* Cambia alocado en base a los dos casilleros q cambiaron */
// void state_change_alocados(State *state, int pos1, int n)
// {
//     // state_print(state, n);
    

//     // pos1 posicion anterior del cero
//     // pos1 posicion actual del numero
//     // state -> position_cero: posicion actual del cero, y anterior del numero

//     // Vemos primero el caso del cero
//     // Estaba bien alocado? Pos1 era la ultima
//     if (pos1 == n*n - 1)
//     {
//         state->alocados++;
//     }
//     // El cero estaba mal alocado
//     else
//     {
//         // Quedo bien alocado
//         if (state->position_cero == n*n - 1)
//         {
//             state->alocados--;
//         }
//         // Quedo mal alocado
//         else {
//             /* code */
//         }
        
//     }

//     // Vemos el numero
//     // Estaba bien alocado? state -> position_cero es el numero + 1
//     if (state->arraylist->array[state->position_cero] == state->position_cero + 1)
//     {
//         state->alocados++;
//     }
//     // Estaba mal alocado
//     else
//     {
//         // Quedo bien alocado
//         if (state->arraylist->array[pos1] == pos1 + 1)
//         {
//             state->alocados--;
//         }
//         // Quedo mal alocado
//         else
//         {
//             /* code */
//         }
//     }
// };

void state_destroy(State *state) 
{
    arraylist_destroy(state->arraylist);
    free(state);
};