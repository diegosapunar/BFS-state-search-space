#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//       Creamos un array list para representar nuestro array dentro del State.             //
//       Esto se debe a que el largo de nuestra matrix no es fija, puede ser de 3x3 o 4x4.  //
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Estructura de mi ArrayList */
struct ArrayList
{
    int* array;         // Arreglo
    int size;           // Largo del arreglo, para mas facil manejor
};

typedef struct ArrayList ArrayList;

//////////////////////////////////////////////////////////////////////////
//                             Funciones                                //
//////////////////////////////////////////////////////////////////////////

/* Creo un ArrayList vacio, retorno el puntero */
ArrayList* arraylist_init(int n); 

/* Inserto en la posicion el elemento correspondiente */ 
void arraylist_insert(ArrayList* arraylist, int element, int position);

/* Obtengo el elemento de una posicion */ 
int arraylist_get(ArrayList* arraylist, int position);

/* Printear el ArrayList de manera bonita */ 
void arraylist_print(ArrayList* arraylist, int n);

/* Liberar memoria ArrayList */
void arraylist_destroy(ArrayList* arraylist);