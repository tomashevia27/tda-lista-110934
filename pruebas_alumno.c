#include "pa2m.h"
#include "src/lista.h"
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final; //consultar esto
	int cantidad_nodos;
};

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}

lista_t *prueba_crear_lista(){
	lista_t *lista_creada = lista_crear();
	pa2m_afirmar(lista_creada != NULL, "se creo la lista correctamente");
	pa2m_afirmar(lista_creada->nodo_final == NULL, "nodo_final apunta a NULL");
	pa2m_afirmar(lista_creada->nodo_inicio == NULL, "nodo_inicio apunta a NULL");
	pa2m_afirmar(lista_creada->cantidad_nodos == 0, "la cantidad de nodos de la lista es 0");
	if(lista_creada == NULL){
		return NULL;
	}
	return lista_creada;
}

void prueba_agregar_al_final(lista_t *lista_creada){
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 15;
	void* elemento1_void = elemento1;
	lista_creada = lista_insertar(lista_creada, elemento1_void);
	pa2m_afirmar(lista_creada != NULL, "lista_insertar devuelve una lista");
	pa2m_afirmar(lista_creada->cantidad_nodos == 1, "se aumento en 1 la cantidad de nodos");
	pa2m_afirmar(lista_creada->nodo_inicio != NULL, "hay un elemento");
	pa2m_afirmar(lista_creada->nodo_inicio == lista_creada->nodo_final, "nodo_inicio y nodo_final apuntan al mismo elemento");
	pa2m_afirmar(lista_creada->nodo_inicio->elemento == elemento1_void, "el elemento se agrego correctamente en el nodo");
	pa2m_afirmar(lista_creada->nodo_final->siguiente == NULL, "ultimo elemento agregado apunta a NULL");

	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 22;
	void* elemento2_void = elemento2;
	lista_creada = lista_insertar(lista_creada, elemento2_void);
	pa2m_afirmar(lista_creada->cantidad_nodos == 2, "la cantidad de nodos es igual a 2");
	pa2m_afirmar(lista_creada->nodo_inicio->siguiente == lista_creada->nodo_final, "el primer elemento apunta al segundo");
	pa2m_afirmar(lista_creada->nodo_final->siguiente == NULL, "ultimo elemento agregado apunta a NULL");

	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 30;
	void* elemento3_void = elemento3;
	lista_creada = lista_insertar(lista_creada, elemento3_void);
	pa2m_afirmar(lista_creada->cantidad_nodos == 3, "la cantidad de nodos es igual a 3");
	pa2m_afirmar(lista_creada->nodo_inicio->siguiente != NULL, "el primer elemento apunta al segundo");
	pa2m_afirmar(lista_creada->nodo_inicio->elemento == elemento1_void, "el elemento del primer nodo se inserto correctamente");
	pa2m_afirmar(lista_creada->nodo_inicio->siguiente->siguiente == lista_creada->nodo_final, "el segundo elemento apunta al tercero (y ultimo)");
	pa2m_afirmar(lista_creada->nodo_inicio->siguiente->elemento == elemento2_void, "el elemento del segundo nodo se inserto correctamente");
	pa2m_afirmar(lista_creada->nodo_final->siguiente == NULL, "ultimo elemento agregado apunta a NULL");
	pa2m_afirmar(lista_creada->nodo_final->elemento == elemento3_void, "el elemento del tercer y ultimo nodo se inserto correctamente");
}

void prueba_agregar_en_posicion(lista_t *lista){
	int *elemento1 = calloc(1, sizeof(int));
	*elemento1 = 1;
	void* elemento1_void = elemento1;
	lista = lista_insertar_en_posicion(lista, elemento1_void, 1);
	pa2m_afirmar(lista->cantidad_nodos == 4, "la cantidad de nodos es igual a 4");
	pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento1_void, "el elemento en posicion 1 se asigno correctamente");

	int *elemento2 = calloc(1, sizeof(int));
	*elemento2 = 4;
	void* elemento2_void = elemento2;
	lista = lista_insertar_en_posicion(lista, elemento2_void, 0);
	pa2m_afirmar(lista->cantidad_nodos == 5, "la cantidad de nodos es igual a 5");
	pa2m_afirmar(lista->nodo_inicio->elemento == elemento2_void, "se asigno correctamente en la posicion 0");

	int *elemento3= calloc(1, sizeof(int));
	*elemento3 = 4;
	void* elemento3_void = elemento3;
	lista = lista_insertar_en_posicion(lista, elemento3_void, 5);
	pa2m_afirmar(lista->cantidad_nodos == 6, "la cantidad de nodos es igual a 6");
	pa2m_afirmar(lista->nodo_final->elemento == elemento3_void, "se asigno correctamente al final");

	int *elemento4 = calloc(1, sizeof(int));
	*elemento4 = 13;
	void* elemento4_void = elemento4;
	lista = lista_insertar_en_posicion(lista, elemento4_void, 3);
	pa2m_afirmar(lista->cantidad_nodos == 7, "la cantidad de nodos es igual a 7");
	pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->siguiente->elemento == elemento4_void, "el elemento en posicion 3 se asigno correctamente");
}

void prueba_eliminar_ultimo_nodo(lista_t *lista){
	int *elemento1 = calloc(1, sizeof(int));
	*elemento1 = 1;
	void* elemento1_void = elemento1;
	lista = lista_insertar_en_posicion(lista, elemento1_void, 6);
	void* elemento1_eliminado = lista_quitar(lista);
	pa2m_afirmar(lista->cantidad_nodos == 7, "la cantidad de nodos disminuyo 1");
	pa2m_afirmar(elemento1_eliminado == elemento1_void, "se obtuvo el elemento correcto");

	lista_t *lista_un_elemento = lista_crear();
	int *elemento2 = calloc(1, sizeof(int));
	*elemento2 = 1;
	void* elemento2_void = elemento2;
	lista = lista_insertar_en_posicion(lista_un_elemento, elemento2_void, 0);
	void* elemento2_eliminado = lista_quitar(lista_un_elemento);
	pa2m_afirmar(lista_un_elemento->cantidad_nodos == 0, "la cantidad de nodos es 0");
	pa2m_afirmar(lista_un_elemento->nodo_inicio == NULL, "nodo_inicio apunta a NULL");
	pa2m_afirmar(lista_un_elemento->nodo_final == NULL, "nodo_final apunta a NULL");
	pa2m_afirmar(elemento2_eliminado == elemento2_void, "se obtuvo el elemento correcto");
}

void prueba_eliminar_cualquier_nodo(lista_t *lista){
	int *elemento1 = calloc(1, sizeof(int));
	*elemento1 = 10;
	void* elemento1_void = elemento1;
	lista = lista_insertar_en_posicion(lista, elemento1_void, 1);
	void *elemento1_eliminado = lista_quitar_de_posicion(lista, 1);
	pa2m_afirmar(lista->cantidad_nodos == 7, "la cantidad de nodos luego de agregar 1 y eliminar 1 es 7");
	pa2m_afirmar(elemento1_eliminado == elemento1_void, "se agrega elemento en posicion 1 y luego se lo elimina");

	int *elemento2 = calloc(1, sizeof(int));
	*elemento2 = 10;
	void* elemento2_void = elemento2;
	lista = lista_insertar_en_posicion(lista, elemento2_void, 10);
	void *elemento2_eliminado = lista_quitar_de_posicion(lista, 10);
	pa2m_afirmar(lista->cantidad_nodos == 7, "la cantidad de nodos luego de agregar 1 y eliminar 1 es 7");
	pa2m_afirmar(elemento2_eliminado == elemento2_void, "se agrega elemento en la ultima posicion y luego se lo elimina");

	int *elemento3 = calloc(1, sizeof(int));
	*elemento3 = 10;
	void* elemento3_void = elemento3;
	lista = lista_insertar_en_posicion(lista, elemento3_void, 2);
	pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->elemento == elemento3_void, "se asigna elemento en posicion 2");
	void *elemento3_eliminado = lista_quitar_de_posicion(lista, 2);
	pa2m_afirmar(lista->cantidad_nodos == 7, "la cantidad de nodos luego de agregar 1 y eliminar 1 es 7");
	pa2m_afirmar(elemento3_eliminado == elemento3_void, "se agrega elemento en la posicion 2 y luego se lo elimina");

	int *elemento4 = calloc(1, sizeof(int));
	*elemento4 = 10;
	void* elemento4_void = elemento4;
	lista = lista_insertar_en_posicion(lista, elemento4_void, 0);
	pa2m_afirmar(lista->nodo_inicio->elemento == elemento4_void, "se agrego elemento en posicion 0");
	void *elemento4_eliminado = lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(lista->cantidad_nodos == 7, "la cantidad de nodos luego de agregar 1 y eliminar 1 es 7");
	pa2m_afirmar(elemento4_eliminado == elemento4_void, "se agrega elemento en la posicion 0 y luego se lo elimina");
}

void prueba_elemento_en_posicion(){
	lista_t *lista = lista_crear();
	
	int *elemento = calloc(1, sizeof(int));
	void *elemento_void;
	void *elemento_en_posicion;
	for (int i = 0; i < 3; i++){
		*elemento = i;
		elemento_void = elemento;
		lista_insertar(lista, elemento_void);

		elemento_en_posicion = lista_elemento_en_posicion(lista, 0);
		printf("se busco elemento en posicion %i\n", i);
		pa2m_afirmar(elemento_en_posicion == elemento_void, "se obtiene el elemento correcto");
	}

	elemento_en_posicion = lista_elemento_en_posicion(lista, 10);
	pa2m_afirmar(elemento_en_posicion == NULL, "devuelve NULL si la posicion no existe");


	free(elemento_void);
}

void prueba_lista_vacia(lista_t *lista){
	pa2m_afirmar(!lista_vacia(lista), "devuelve false cuando la lista tiene elementos");
	lista_t *lista_sin_elementos = NULL;
	pa2m_afirmar(lista_vacia(lista_sin_elementos), "devuelve true cuando la lista es NULL");
	lista_sin_elementos = lista_crear(lista_sin_elementos);
	pa2m_afirmar(lista_vacia(lista_sin_elementos), "devuelve true cuando la lista esta creada pero no tiene elementos");
}

void prueba_primer_ultimo_elemento(lista_t *lista){
	lista_t *lista_nueva = lista_crear();
	void* primer_elemento = lista_primero(lista_nueva);
	pa2m_afirmar(primer_elemento == NULL, "lista_primero() devuelve NULL cuando la lista esta vacia");
	void* ultimo_elemento = lista_ultimo(lista_nueva);
	pa2m_afirmar(ultimo_elemento == NULL, "lista_ultimo() devuelve NULL cuando la lista esta vacia");

	primer_elemento = lista_primero(lista);
	pa2m_afirmar(primer_elemento == lista->nodo_inicio->elemento, "lista_primero() devuelve elemento correcto");
	
	int *elemento = calloc(1, sizeof(int));
	*elemento = 10;
	void* elemento_void = elemento;
	lista = lista_insertar_en_posicion(lista, elemento_void, 0);
	primer_elemento = lista_primero(lista);
	pa2m_afirmar((primer_elemento == elemento_void) && (primer_elemento == lista->nodo_inicio->elemento), "luego de insertar elemento al principio, lista_primero() devuelve elemento correcto");
	
	
	ultimo_elemento = lista_ultimo(lista);
	pa2m_afirmar(ultimo_elemento == lista->nodo_final->elemento, "lista_ultimo() devuelve elemento correcto");

	*elemento = 15;
	elemento_void = elemento;
	lista = lista_insertar(lista, elemento_void);
	ultimo_elemento = lista_ultimo(lista);
	pa2m_afirmar((ultimo_elemento == elemento_void) && (ultimo_elemento == lista->nodo_final->elemento), "luego de insertar elemento al final, lista_ultimo() devuelve elemento correcto");
}


int main()
{
	pa2m_nuevo_grupo(
		"\n======================== CREAR LISTA ========================");
	//prueba_simple();
	lista_t *lista = prueba_crear_lista();
	pa2m_nuevo_grupo(
		"\n======================== AGREGAR AL FINAL ========================");
	prueba_agregar_al_final(lista);
	pa2m_nuevo_grupo(
		"\n======================== AGREGAR EN CUALQUIER POSICION ========================");
	prueba_agregar_en_posicion(lista);
	pa2m_nuevo_grupo(
		"\n======================== ELIMINAR ULTIMO NODO ========================");
	prueba_eliminar_ultimo_nodo(lista);
	pa2m_nuevo_grupo(
		"\n======================== ELIMINAR CUALQUIER NODO ========================");
	prueba_eliminar_cualquier_nodo(lista);
		pa2m_nuevo_grupo(
		"\n======================== OBTENER ELEMENTO EN POSICION ========================");
	prueba_elemento_en_posicion();
	pa2m_nuevo_grupo(
		"\n======================== ESTA VACIA LA LISTA ========================");
	prueba_lista_vacia(lista);
	pa2m_nuevo_grupo(
		"\n======================== PRIMER y ULTIMO ELEMENTO ========================");
	prueba_primer_ultimo_elemento(lista);
	
	return pa2m_mostrar_reporte();
}
