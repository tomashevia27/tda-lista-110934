#include "pila.h"

typedef struct nodo{
	void *elemento;
	void *nodo_anterior;
}nodo_t;

struct _pila_t{
	struct nodo *tope;
	size_t cantidad_nodos;
};

pila_t *pila_crear()
{
	pila_t *pila = calloc(1, sizeof(pila_t));
	if(pila == NULL){
	return NULL;
	}
	return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if(pila == NULL || elemento == NULL){
		return NULL;
	}

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if(nuevo_nodo == NULL){
		return NULL;
	}

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->nodo_anterior = pila->tope;
	pila->tope = nuevo_nodo;
	(pila->cantidad_nodos)++;

	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	if(pila == NULL){
		return NULL;
	}

	nodo_t *nodo_a_eliminar = pila->tope;
	pila->tope = nodo_a_eliminar->nodo_anterior;
	void *elemento_eliminado = nodo_a_eliminar->elemento;
	nodo_a_eliminar->nodo_anterior = NULL; //esto puede que no sirva
	free(nodo_a_eliminar);
	(pila->cantidad_nodos)--;

	return elemento_eliminado;
}

void *pila_tope(pila_t *pila)
{
	if(pila == NULL || pila->tope == NULL){
		return NULL;
	}
	return pila->tope->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	if(pila == NULL){
		return 0;
	}
	return pila->cantidad_nodos;
}

bool pila_vacia(pila_t *pila)
{
	return (pila->tope == NULL && pila->cantidad_nodos == 0);
}

void pila_destruir(pila_t *pila)
{
	if(pila != NULL){
		while(!pila_vacia(pila)){
			void* elemento_desapilado = pila_desapilar(pila);
			free(elemento_desapilado);
		}
	}
	free(pila);
}
