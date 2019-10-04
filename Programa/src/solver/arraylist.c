#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>

/*  Tomado de mis Tareas anteriores, sobre todo mi base en mi Stack de la A0 
    En terminos de diseno, se utiliza esta estructura, porque avecemos tenemos
    tableros de largo 3, y aveces de largo 4, siendo entonces variables. Para
    unificarlo creamos esto. 
 */

//////////////////////////////////////////////////////////////////////////
//                             Funciones                                //
//////////////////////////////////////////////////////////////////////////

/* Creo un ArrayList vacio, de largo n, retorno el puntero */
ArrayList *arraylist_init(int n)
{
    // Creo el Stack asignandole espacio de memoria
    ArrayList* arraylist = malloc(sizeof(ArrayList));

    // Inizializo los atributos, con base al input n
    arraylist -> size = n*n;
    arraylist -> array = malloc(sizeof(int) * arraylist -> size);

    return arraylist;
};

/* Inserto en la posicion el elemento correspondiente */
void arraylist_insert(ArrayList* arraylist, int element, int position)
{
    // printf("Estoy insertando: %d en la pos: %d\n", element, position);
    arraylist -> array[position] = element;
};

/* Obtengo el elemento de una posicion */
int arraylist_get(ArrayList* arraylist, int position)
{
    return arraylist -> array[position];
};

/* Printear el ArrayList de manera bonita, recibo el array */
void arraylist_print(ArrayList* arraylist, int n)
{
    int contador = 0;
    for(int i = 0; i < n; i++)
    {
        if (n==3) {
            printf("%d - %d - %d\n", arraylist->array[contador], arraylist->array[contador + 1], arraylist->array[contador + 2]);
        }
        else {
            printf("%d - %d - %d - %d\n", arraylist->array[contador], arraylist->array[contador + 1], arraylist->array[contador + 2], arraylist->array[contador + 3]);
        }
        
        contador = contador + n;
    }
};

/* Liberar memoria ArrayList */
void arraylist_destroy(ArrayList* arraylist)
{
    /* Primero el arreglo, y luego la estrcutura */ 
    free(arraylist -> array);
    free(arraylist);
};