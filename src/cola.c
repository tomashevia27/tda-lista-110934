#include "cola.h"

typedef struct nodo{
	void *elemento;
	void *nodo_siguiente;
}nodo_t;

struct _cola_t{
	struct nodo *principio;
	struct nodo *final;
};

cola_t *cola_crear()
{
	cola_t *cola = malloc(sizeof(cola_t));
	if (cola != NULL){
		return cola;
	} else{
		return NULL;
	} // CHEQUEAR ESTO!
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if(cola == NULL || elemento == NULL){
		return NULL;
	}

	nodo_t *nuevo_nodo = calloc(1, sizeof(struct nodo));
	nuevo_nodo->elemento = elemento;
	cola->final->nodo_siguiente = nuevo_nodo;
	cola->final = nuevo_nodo;

	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	if(cola == NULL){
		return NULL;
	}

	nodo_t *primer_nodo = cola->principio;
	if(cola->principio == cola->final){
		cola->principio = NULL;
		cola->final = NULL;
	} else{
		cola->principio = cola->principio->nodo_siguiente;
	}
	void *elemento_desencolado = primer_nodo->elemento;
	primer_nodo->nodo_siguiente = NULL;
	free(primer_nodo);

	return elemento_desencolado;
}

void *cola_frente(cola_t *cola)
{
	if(cola == NULL || cola->principio == NULL){
		return NULL;
	}

	return cola->principio->elemento;
}

size_t cola_tamanio(cola_t *cola) // complejidad O(n) podria probar usar un int cantidad en cola_t !!!!
{
	if(cola == NULL || cola->principio == NULL){
		return 0;
	}
	nodo_t *nodo_actual = cola->principio;
	size_t nodos_recorridos = 1;
	while(nodo_actual == cola->final){
		nodo_actual = nodo_actual->nodo_siguiente;
		nodos_recorridos++;
	}
	
	return nodos_recorridos;
}

bool cola_vacia(cola_t *cola)
{
	return(cola->principio == NULL && cola->final == NULL);
}

void cola_destruir(cola_t *cola)
{
	if(cola != NULL){
		while(!cola_vacia(cola)){
			void* elemento_desencolado = cola_desencolar(cola);
			free(elemento_desencolado);
		}
		free(cola);
	}
}
