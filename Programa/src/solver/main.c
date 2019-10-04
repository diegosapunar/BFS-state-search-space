#include <stdio.h>
#include <stdlib.h>
#include "state.h"
#include "queue.h"
#include "../random/pcg_basic.h"
#include "hash.h"
#include <time.h>

void answer(State *state, int contador, FILE *output_file)
{
	if (state->father)
	{
		contador ++;
		answer(state->father, contador, output_file);
		fprintf(output_file, "%d,%d\n", state->parent_x, state->parent_y);
	}
	else
	{
		fprintf(output_file, "%d\n", contador);
	}
	
};

void get_sons(Queue* cola, int n, State* state, ArrayList** cubo){
  queue_push(cola, state_son_up(state, n, cubo));
  queue_push(cola, state_son_right(state, n, cubo));
  queue_push(cola, state_son_down(state, n, cubo));
  queue_push(cola, state_son_left(state, n, cubo));

};

void bfs(State *state, int n, ArrayList **cubo, HashTable *hashtable, FILE *output_file)
{
	Queue* cola = queue_init();
	Queue* operations = queue_init();

	// Parto con el estado unicial en la cola
	queue_push(cola, state);

	while(cola -> count){

		// Saco al siguiente a revisar
		State* current_state = queue_pop_left(cola);
		
		// Veo si es solucion
		if (state_is_solution(current_state, n))
		{
			answer(current_state, 0, output_file);
			break;
		}

		// Toca agregar a los hijos, ya q no es solucion el current_state
		else{

			// Obtengo los hijos, agregandolos a operations
			get_sons(operations, n, current_state, cubo);

			State* nodo_actual = NULL;

			// Agrego cada hijo de operations a mi cola
			while(operations -> count){
				nodo_actual = queue_pop_left(operations);

				if ((hashtable->count) > (hashtable->size)*0.8)
				{
					HashTable *hashtable_aux = hashtable_rehash(hashtable, n);
					hashtable = hashtable_aux;
				}
				
				if (hashtable_insert(hashtable, nodo_actual,n)) {
						queue_push(cola, nodo_actual);
				}		
				// else
				// {
				// 	state_destroy(nodo_actual);
				// }
				
			};
		}

	}    
	// printf("NUMERO DE ESTADOS: %d\n", hashtable->count);
	// queue_destroy(cola);
	// queue_destroy(operations);
};

int main(int argc, char *argv[])
{
	// clock_t begin = clock();
	if (argc != 3)
  {
	printf("Modo de uso: ./solver [test.txt] [output.txt]\n");
	printf("Donde:\n");
	printf("\t[test.txt] es el archivo de input\n");
	printf("\t[output.txt] es el nombre del archivo a escribir con el output\n");
  }

  /* Abrimos el archivo input en modo de lectura */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo output en modo de escritura */
  FILE *output_file = fopen("output.txt", "w");

  /* Revisa que el archivo fue abierto correctamente */
  if (!input_file || !output_file)
  {
	printf("¡Error abriendo los archivos!");
	return 2;
  }

  /* Definimos y asignamos las constantes del problema */
  int n;
  fscanf(input_file, "%d", &n);

  /* Creamos el estado inicial, que es el input */ 
  State* state = state_init(n);

  int contador = 0;

  /* Cargamos el estado inical */ 
  for(int i = 0; i < n; i++)
  {
	if (n==4) {
	  int a; int b; int c;int d;
	  /* Leemos cada linea del archivo */
	  fscanf(input_file, "%d,%d,%d,%d", &a, &b, &c, &d);
	  
	  state_insert(state, a, contador);
	  contador++;
	  state_insert(state, b, contador);
	  contador++;
	  state_insert(state, c, contador);
	  contador++;
	  state_insert(state, d, contador);
	  contador++;
	}
	else 
	{
	  int a; int b; int c;
	  /* Leemos cada linea del archivo */
	  fscanf(input_file, "%d,%d,%d", &a, &b, &c);

	  state_insert(state, a, contador);
	  contador++;
	  state_insert(state, b, contador);
	  contador++;
	  state_insert(state, c, contador);
	  contador++;
	}

  }

	ArrayList** cubo = malloc(n * n * sizeof(ArrayList *));
	for (int i = 0; i < n * n; i++)
	{
		cubo[i] = arraylist_init(n);
		for (int j = 0; j < n * n; j++)
		{
			int a = pcg32_boundedrand(999999999);
			arraylist_insert(cubo[i], a, j);
		}	
	}
	
	for (int i = 0; i < n * n; i++)
	{
		state -> hash = state -> hash ^ cubo[i] -> array[state->arraylist->array[i]];
	}

	HashTable *hashtable = hashtable_init(1132463);

	bfs(state, n, cubo, hashtable, output_file);

	//////////////////////////////////////////////////////////////////////////
  //                             Limpiamos memoria                        //
  //////////////////////////////////////////////////////////////////////////

  /* Cerramos los archivos correctamente */
  fclose(input_file);
  fclose(output_file);

	// Liberamos mi cubo
	// for(int i = 0; i < n*n; i++)
	// {
	// 	arraylist_destroy(cubo[i]);
	// }
	// free(cubo);

	// liberamos la hashtable
	// hashtable_destroy(hashtable);
	// clock_t end = clock();

	// double time_spent_total = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("TIME SPENT in total: %lf seconds (s)\n", time_spent_total);
	return 0;
}
