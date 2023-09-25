#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

struct nodo {
	void *elemento;
	struct nodo *siguiente;
};

struct lista {
	struct nodo *nodo_inicio;
	struct nodo *nodo_final; //consultar esto
	size_t cantidad_nodos;
};

struct lista_iterador {
	struct nodo *nodo_actual;
};

void iterador_interno(lista_t *lista){

}

lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	if(lista == NULL){
		return NULL;
	}
	return lista;
}

bool lista_vacia(lista_t *lista)
{
	return (lista == NULL || lista->nodo_inicio == NULL);
}

struct nodo *obtener_nodo_en_posicion(lista_t *lista, size_t posicion){
	struct nodo *nodo_en_posicion = lista->nodo_inicio;
	size_t posicion_nodo = 0;
	while(nodo_en_posicion->siguiente != NULL && posicion_nodo < posicion){
		nodo_en_posicion = nodo_en_posicion->siguiente;
		posicion_nodo++;
	}
	return nodo_en_posicion;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(lista == NULL || elemento == NULL){
		return NULL;
	}

	struct nodo *nodo_a_insertar = calloc(1, sizeof(struct nodo));
	if(nodo_a_insertar == NULL){
		return NULL;
	}
	nodo_a_insertar->elemento = elemento;

	if(lista_vacia(lista)){
		lista->nodo_inicio = nodo_a_insertar;
		lista->nodo_final = nodo_a_insertar;
	} else{
		lista->nodo_final->siguiente = nodo_a_insertar;
		lista->nodo_final = nodo_a_insertar;
	}

	(lista->cantidad_nodos)++;
	return lista;
}






/*
lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(lista == NULL || elemento == NULL){
		return NULL;
	}

	struct nodo *nuevo_nodo = calloc(1, sizeof(struct nodo));
	if(nuevo_nodo == NULL){
		return NULL;
	}
	nuevo_nodo->elemento = elemento;
	
	lista->nodo_final = nuevo_nodo;
	if(lista_vacia(lista)){
		lista->nodo_inicio = nuevo_nodo;
	} else if(lista->cantidad_nodos == 1){
		lista->nodo_inicio->siguiente = nuevo_nodo;
	} else{
		struct nodo *anteultimo_nodo = obtener_nodo_en_posicion(lista, (lista->cantidad_nodos)-1);	
		anteultimo_nodo->siguiente = nuevo_nodo;
	}
	(lista->cantidad_nodos)++;
	return lista;
}
*/

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(lista == NULL || elemento == NULL){ 
		return NULL;
	}

	if(posicion >= lista->cantidad_nodos){
		lista = lista_insertar(lista, elemento);
		if (lista == NULL){
			return NULL;
		}
		return lista;
	}

	struct nodo *nuevo_nodo = calloc(1, sizeof(struct nodo));
	if(nuevo_nodo == NULL){
		return NULL;	
	}
	nuevo_nodo->elemento = elemento;

	if(posicion == 0){
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		(lista->cantidad_nodos)++;
		return lista;
	}

	struct nodo *nodo_posicion_anterior = obtener_nodo_en_posicion(lista, posicion-1);
	nuevo_nodo->siguiente = nodo_posicion_anterior->siguiente;
	nodo_posicion_anterior->siguiente = nuevo_nodo;
	(lista->cantidad_nodos)++;
	
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if(lista == NULL || lista_vacia(lista)){
		return NULL;
	}

	if(lista->nodo_inicio == lista->nodo_final){
		struct nodo *nodo_a_eliminar = lista->nodo_inicio;
		void *elemento_eliminado = nodo_a_eliminar->elemento;
		lista->nodo_inicio = NULL;
		lista->nodo_final = NULL;
		lista->cantidad_nodos = 0;
		free(nodo_a_eliminar);
		return elemento_eliminado;
	}

	struct nodo *anteultimo_nodo = lista->nodo_inicio;
	while(anteultimo_nodo->siguiente != lista->nodo_final){
		anteultimo_nodo = anteultimo_nodo->siguiente;
	}
	struct nodo *nodo_a_eliminar = anteultimo_nodo->siguiente;
	void *elemento_eliminado = nodo_a_eliminar->elemento;
	lista->nodo_final = anteultimo_nodo;
	(lista->cantidad_nodos)--;
	free(nodo_a_eliminar);
	anteultimo_nodo = NULL;
	free(anteultimo_nodo);
	return elemento_eliminado;

}


void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL || lista_vacia(lista)){
		return NULL;
	}

	void *elemento_retirado;

	if(posicion > lista->cantidad_nodos){
		elemento_retirado = lista_quitar(lista);
		if (elemento_retirado == NULL){
			return NULL;
		}
		return elemento_retirado;
	}

	struct nodo *nodo_a_eliminar;
	if(posicion == 0){
		nodo_a_eliminar = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
	} else{
		struct nodo *nodo_anterior = obtener_nodo_en_posicion(lista, posicion-1);
		nodo_a_eliminar = nodo_anterior->siguiente;
		if(nodo_a_eliminar->siguiente == lista->nodo_final){
			lista->nodo_final = nodo_anterior;
		} else{
			struct nodo *nodo_siguiente = nodo_a_eliminar->siguiente;
			nodo_anterior->siguiente = nodo_siguiente;
		}
	}

	nodo_a_eliminar->siguiente = NULL;
	elemento_retirado = nodo_a_eliminar->elemento;
	(lista->cantidad_nodos)--;
	free(nodo_a_eliminar);
	return elemento_retirado;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL){
		return NULL;
	}

	if(posicion >= lista->cantidad_nodos){
		return NULL;
	}

	struct nodo *nodo_en_posicion = obtener_nodo_en_posicion(lista, posicion);
	if(nodo_en_posicion == NULL){
		return NULL;
	}

	return nodo_en_posicion->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_final->elemento;
}


size_t lista_tamanio(lista_t *lista)
{
	if(lista_vacia(lista)){
		return 0;
	}
	return lista->cantidad_nodos;
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if(lista == NULL){
		return NULL;
	}

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if(iterador == NULL){
		return NULL;
	}
	iterador->nodo_actual = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(iterador->nodo_actual->siguiente != NULL){
		return true;
	}
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(iterador->nodo_actual->siguiente != NULL){
		iterador->nodo_actual = iterador->nodo_actual->siguiente;
		return true;
	} else{
		return false;
	}
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(iterador->nodo_actual == NULL){
		return NULL;
	}
	return iterador->nodo_actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	iterador->nodo_actual = NULL;
	free(iterador);
}

void lista_destruir(lista_t *lista)
{
	if(lista != NULL){
		while(!lista_vacia(lista)){
			void* elemento_eliminado = lista_quitar(lista);
			free(elemento_eliminado);
		}
		free(lista);
	}
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(funcion != NULL){
		for(lista_iterador_t *iterador = lista_iterador_crear(lista); lista_iterador_tiene_siguiente(iterador); lista_iterador_avanzar(iterador)){
			funcion(iterador->nodo_actual->elemento);
		}
	}
	if(lista != NULL){
		lista_destruir(lista);
	}
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if(lista == NULL || funcion == NULL || contexto == NULL){
		return 0;
	}

	struct nodo *nodo_actual = lista->nodo_final;
	size_t nodos_recorridos = 1;
	while(nodo_actual->siguiente != NULL && funcion(nodo_actual, contexto)){
		nodo_actual = nodo_actual->siguiente;
		nodos_recorridos++;
	}

	return nodos_recorridos;
}