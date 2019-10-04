#include "hash.h"
#include <stdlib.h>
#define MOD(a, b) ((((a) % (b)) + (b)) % (b))

/* Crear Nodo con el valor pointer al lista ligada, y retorna un puntero al nodo. */
HashNode* hashnode_init()
{
    HashNode* hashnode = malloc(sizeof(HashNode)); // Creo el Nodo asignandole espacio de memoria
    Queue *colisiones = queue_init();

    hashnode -> free = true;
    hashnode -> colisiones = colisiones;

    return hashnode;                        // Retorno el Nodo
}

/* Inizializo mi HashTable del tamano de n. Parte bacia, es decir todos free */ 
HashTable* hashtable_init(int n)
{
    // Creo la tabla asigandole es espacio de memoria
    HashTable* hashtable = malloc(sizeof(HashTable));

    // Inizializo los atributos, con base al input n
    hashtable->size = n;
    hashtable->count = 0;
    hashtable -> array = malloc(sizeof(HashNode) * hashtable -> size);

    // Inizializamos cada uno de los nodos de la tabla, en modo free
    
    for(int i = 0; i < hashtable -> size; i++)
    {
        HashNode* node = hashnode_init();
        hashtable->array[i] = node;
    }

    return hashtable;
};

bool hashtable_insert(HashTable* hashtable, State *state, int n)
{
    

    int position = MOD(state->hash, hashtable->size);

    // SI ESTA
    // Primero veo si la casilla esta free o no.
    if (hashtable -> array[position]->free) {
        // printf("LA CASILLA ESTA LIBRE CTM!! Insertando...\n\n");
        hashtable->array[position]->free = false;
        queue_push(hashtable->array[position]->colisiones, state);
        hashtable->count++;
        return true;
        }
    // La primera casilla ya estaba ocupada, hay que buscar en su lista ligada
    else{
        bool esta = false;
        int contador = 0;
        // printf("LA CASILLA ESTA OCUPADA!!, busquemos en su lista de colisiones\n\n");

        Node * nodo_actual = hashtable->array[position]->colisiones->first;

        if (state_compare(nodo_actual->value, state, n)){esta = true;}
            // printf("Colision numero: %d\n", contador);
            // state_print(nodo_actual->value, 3);

            contador++;
            while (nodo_actual->next)
            {
                // printf("entre al while de colisiones\n");
                // printf("Colision numero: %d\n", contador);
                // state_print(nodo_actual->value, 3);
                if (state_compare(nodo_actual->value, state, n))
                {
                    esta = true;
                    break;
                }

                nodo_actual = nodo_actual->next;
                contador++;
            }
            if (esta)
            {
                // printf("ya estaba\n");
                return false;
            }
            else
            {
                // printf("no  estaba, insertando...\n");
                queue_push(hashtable->array[position]->colisiones, state);
                hashtable -> count++;
                return true;
            }

            // state_print(hashtable->array[position]->colisiones->first->value, 3);
    }
    
};

HashTable* hashtable_rehash(HashTable *hashtable_antigua, int n)
{
    // printf("ESTOY REHASHEANDO! de %llu a %llu\n", hashtable_antigua->size, hashtable_antigua->size * 2);
    // int a = 0;
    HashTable* hashtable = hashtable_init(hashtable_antigua->size * 2);

    // Momento de traspasar todo lo antiguo a mi nueva tabla!
    // Iteremos sobre mi tabla.
    for (int i = 0; i < hashtable_antigua->size; i++)
    {
        if (!hashtable_antigua->array[i]->free)
        {
            // printf("ESOTY OCUPADO\n");
            Node *nodo_actual = hashtable_antigua->array[i]->colisiones->first;
            hashtable_insert(hashtable, nodo_actual->value, n);
            // state_print(nodo_actual->value, n);
            // a++;

            while (nodo_actual->next)
            {
                // state_print(nodo_actual->value, n);
                nodo_actual = nodo_actual->next;
                hashtable_insert(hashtable, nodo_actual->value, n);
                // a ++;
            }
        }
        
    }
    // printf("a: %d\n", a);
    // printf("COUNT: %d\n", hashtable_antigua->count);
    return hashtable;
    
};

void hashtable_destroy_node(HashNode* node)
{
    queue_destroy(node->colisiones);
    free(node);
};

void hashtable_destroy(HashTable *hashtable)
{
    for(int i = 0; i < hashtable->size; i++)
    {
        hashtable_destroy_node(hashtable->array[i]);
    }
    
    free(hashtable->array);
    free(hashtable);
};