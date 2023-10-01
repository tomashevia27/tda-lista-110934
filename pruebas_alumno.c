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

struct lista_iterador {
	struct nodo *nodo_actual;
	lista_t *lista;
};

lista_t *prueba_crear_lista()
{
	lista_t *lista_creada = lista_crear();
	pa2m_afirmar(lista_creada != NULL, "se creo la lista correctamente");
	pa2m_afirmar(lista_creada->nodo_final == NULL,
		     "nodo_final apunta a NULL");
	pa2m_afirmar(lista_creada->nodo_inicio == NULL,
		     "nodo_inicio apunta a NULL");
	pa2m_afirmar(lista_creada->cantidad_nodos == 0,
		     "la cantidad de elementos de la lista es 0");
	if (lista_creada == NULL) {
		return NULL;
	}
	return lista_creada;
}

void prueba_agregar_al_final(lista_t *lista_creada)
{
	int *elemento = malloc(sizeof(int));
	*elemento = 15;
	void *elemento_void = elemento;

	lista_t *lista_nula = NULL;
	lista_nula = lista_insertar(lista_nula, elemento_void);
	pa2m_afirmar(lista_nula == NULL,
		     "insertar elemento en lista nula devuelve lista nula");

	lista_creada = lista_insertar(lista_creada, elemento_void);
	pa2m_afirmar(
		lista_creada != NULL && !lista_vacia(lista_creada),
		"lista_insertar en lista nula devuelve la lista con un elemento");
	pa2m_afirmar(lista_creada->cantidad_nodos == 1,
		     "la cantidad de elementos es 1");
	pa2m_afirmar(lista_creada->nodo_inicio != NULL,
		     "el nodo inicio apunta al primer elemento");
	pa2m_afirmar(lista_creada->nodo_inicio == lista_creada->nodo_final,
		     "nodo_inicio y nodo_final apuntan al mismo elemento");
	pa2m_afirmar(lista_creada->nodo_inicio->elemento == elemento_void,
		     "el elemento se agrego correctamente en el nodo");
	pa2m_afirmar(lista_creada->nodo_final->siguiente == NULL,
		     "ultimo elemento agregado apunta a NULL");

	*elemento = 22;
	elemento_void = elemento;
	lista_creada = lista_insertar(lista_creada, elemento_void);
	pa2m_afirmar(lista_creada->cantidad_nodos == 2,
		     "la cantidad de elementos es 2");
	pa2m_afirmar(lista_creada->nodo_inicio->siguiente ==
			     lista_creada->nodo_final,
		     "el primer elemento apunta al segundo");
	pa2m_afirmar(lista_creada->nodo_final->elemento == elemento_void,
		     "el elemento se agrego correctamente en el nodo");
	pa2m_afirmar(lista_creada->nodo_final->siguiente == NULL,
		     "ultimo elemento agregado apunta a NULL");

	elemento_void = NULL;
	lista_creada = lista_insertar(lista_creada, elemento_void);
	pa2m_afirmar(lista_creada != NULL &&
			     lista_creada->nodo_final->elemento == NULL,
		     "se pudo agregar un elemento NULL");
	pa2m_afirmar(lista_creada->cantidad_nodos == 3,
		     "la cantidad de elementos es igual a 3");
	pa2m_afirmar(lista_creada->nodo_inicio->siguiente->siguiente ==
			     lista_creada->nodo_final,
		     "el segundo elemento apunta al tercero (y ultimo)");
	pa2m_afirmar(
		lista_creada->nodo_final->elemento == elemento_void,
		"el elemento del tercer y ultimo nodo se inserto correctamente");
	pa2m_afirmar(lista_creada->nodo_final->siguiente == NULL,
		     "ultimo elemento agregado apunta a NULL");
}

void prueba_agregar_en_posicion(lista_t *lista)
{
	int *elemento = calloc(1, sizeof(int));
	*elemento = 1;
	void *elemento_void = elemento;

	lista_t *lista_nula = NULL;
	lista_nula = lista_insertar(lista_nula, elemento_void);
	pa2m_afirmar(lista_nula == NULL,
		     "insertar elemento en lista nula devuelve lista nula");

	lista = lista_insertar_en_posicion(lista, elemento_void, 1);
	pa2m_afirmar(
		lista != NULL && !lista_vacia(lista),
		"se insertar un elemento en el medio y se devuelve una lista que no esta vacia");
	pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento_void,
		     "el elemento en posicion 1 se asigno correctamente");
	pa2m_afirmar(lista->cantidad_nodos == 4,
		     "la cantidad de elementos es igual a 4");

	*elemento = 4;
	lista = lista_insertar_en_posicion(lista, elemento_void, 0);
	pa2m_afirmar(
		lista != NULL,
		"insertar elemento en la primer posicion devuelve la lista");
	pa2m_afirmar(lista->nodo_inicio->elemento == elemento_void,
		     "se asigno correctamente en la posicion 0");
	pa2m_afirmar(lista->cantidad_nodos == 5,
		     "la cantidad de elementos es igual a 5");

	lista = lista_insertar_en_posicion(lista, elemento_void, 0);
	pa2m_afirmar(lista->nodo_inicio->elemento == elemento_void,
		     "se puede insertar un elemento repetido");
	pa2m_afirmar(lista->cantidad_nodos == 6,
		     "la cantidad de elementos es igual a 6");

	*elemento = 8;
	lista = lista_insertar_en_posicion(lista, elemento_void, 50);
	pa2m_afirmar(
		lista != NULL,
		"insertar elemento en la ultima posicion devuelve la lista");
	pa2m_afirmar(lista->nodo_final->elemento == elemento_void,
		     "se asigno correctamente al final de la lista");
	pa2m_afirmar(lista->cantidad_nodos == 7,
		     "la cantidad de elementos es igual a 7");

	elemento_void = NULL;
	lista = lista_insertar_en_posicion(lista, elemento_void, 3);
	pa2m_afirmar(lista != NULL, "insertar elemento nulo devuelve la lista");
	pa2m_afirmar(
		lista->nodo_inicio->siguiente->siguiente->siguiente->elemento ==
			elemento_void,
		"el elemento en posicion 3 se asigno correctamente siendo NULL");
	pa2m_afirmar(lista->cantidad_nodos == 8,
		     "la cantidad de elementos es igual a 8");
}

void prueba_eliminar_ultimo_nodo(lista_t *lista)
{
	int *elemento = calloc(1, sizeof(int));
	*elemento = 1;
	void *elemento_void = elemento;

	lista_t *lista_nula = NULL;
	lista_nula = lista_quitar(lista_nula);
	pa2m_afirmar(lista_nula == NULL,
		     "quitar elemento en lista nula devuelve lista nula");

	lista_t *lista_sin_elementos = lista_crear();
	void *elemento_eliminado = lista_quitar(lista_sin_elementos);
	pa2m_afirmar(
		elemento_eliminado == NULL && lista_vacia(lista_sin_elementos),
		"al intentar eliminar un elemento en una lista vacia, se devuelve NULL y la lista queda vacia");

	lista = lista_insertar(lista, elemento_void);
	elemento_eliminado = lista_quitar(lista);
	pa2m_afirmar(elemento_eliminado == elemento_void,
		     "se elimino correctamente el elemento final de la lista");
	pa2m_afirmar(lista != NULL && !lista_vacia(lista),
		     "lista_quitar devuelve una lista que no esta vacia");
	pa2m_afirmar(
		lista->cantidad_nodos == 8,
		"la cantidad de nodos luego de agregar y quitar es igual que antes");

	lista_t *lista_un_elemento = lista_crear();
	*elemento = 1;
	lista = lista_insertar_en_posicion(lista_un_elemento, elemento_void, 0);
	elemento_eliminado = lista_quitar(lista_un_elemento);
	pa2m_afirmar(
		lista != NULL && lista_vacia(lista),
		"aplicar lista_quitar en una lista de un elemento devuelve una lista vacia");
	pa2m_afirmar(elemento_eliminado == elemento_void,
		     "se elimino el elemento correcto");
	pa2m_afirmar(lista_un_elemento->cantidad_nodos == 0,
		     "la cantidad de nodos es 0");
	pa2m_afirmar(lista_un_elemento->nodo_inicio == NULL &&
			     lista_un_elemento->nodo_final == NULL,
		     "los nodos inicio y final apuntan a NULL");
}

void prueba_eliminar_cualquier_nodo(lista_t *lista)
{
	int *elemento = calloc(1, sizeof(int));
	*elemento = 10;
	void *elemento_void = elemento;

	lista_t *lista_nula = NULL;
	void *elemento_eliminado = lista_quitar_de_posicion(lista_nula, 4);
	pa2m_afirmar(elemento_eliminado == NULL && lista_nula == NULL,
		     "quitar elemento en lista nula devuelve lista nula");

	lista_t *lista_sin_elementos = lista_crear();
	elemento_eliminado = lista_quitar_de_posicion(lista_sin_elementos, 2);
	pa2m_afirmar(
		elemento_eliminado == NULL && lista_vacia(lista_sin_elementos),
		"al intentar eliminar un elemento en una lista vacia, se devuelve NULL y la lista queda vacia");

	lista = lista_insertar_en_posicion(lista, elemento_void, 1);
	elemento_eliminado = lista_quitar_de_posicion(lista, 1);
	pa2m_afirmar(elemento_eliminado == elemento_void,
		     "eliminar elemento en posicion 1 y luego se lo elimina");

	*elemento = 20;
	lista = lista_insertar_en_posicion(lista, elemento_void, 10);
	elemento_eliminado = lista_quitar_de_posicion(lista, 10);
	pa2m_afirmar(
		elemento_eliminado == elemento_void,
		"eliminar en una posicion mayor a la cantidad de elementos funciona");

	*elemento = 30;
	lista = lista_insertar_en_posicion(lista, elemento_void, 0);
	elemento_eliminado = lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(elemento_eliminado == elemento_void,
		     "se puede eliminar elemento en la posicion 0");

	elemento_void = NULL;
	lista = lista_insertar_en_posicion(lista, elemento_void, 2);
	elemento_eliminado = lista_quitar_de_posicion(lista, 2);
	pa2m_afirmar(
		elemento_eliminado == elemento_void,
		"se agrega un elemento NULL en la posicion 2 y luego se elimina correctamente");
}

void prueba_elemento_en_posicion()
{
	int *elemento = calloc(1, sizeof(int));
	void *elemento_void = elemento;
	void *elemento_en_posicion;

	lista_t *lista = NULL;
	elemento_en_posicion = lista_elemento_en_posicion(lista, 2);
	pa2m_afirmar(elemento_en_posicion == NULL,
		     "no se puede obtener un elemento de una lista nula");

	lista = lista_crear();
	elemento_en_posicion = lista_elemento_en_posicion(lista, 2);
	pa2m_afirmar(elemento_en_posicion == NULL,
		     "no se puede obtener un elemento de una lista vacia");

	for (int i = 0; i < 3; i++) {
		*elemento = i;
		lista_insertar(lista, elemento_void);

		elemento_en_posicion = lista_elemento_en_posicion(lista, 0);
		printf("se busco elemento en posicion %i\n", i);
		pa2m_afirmar(elemento_en_posicion == elemento_void,
			     "se obtiene el elemento correcto");
	}

	elemento_en_posicion = lista_elemento_en_posicion(lista, 10);
	pa2m_afirmar(
		elemento_en_posicion == NULL,
		"no se puede entender un elemento de una posicion inexistente");

	free(elemento_void);
}

int comparador(void *e1, void *e2)
{
	if (e1 == e2) {
		return 0;
	}
	return 1;
}

void prueba_buscar_elemento()
{
	void *contexto = (void *)30;
	pa2m_afirmar(lista_buscar_elemento(NULL, comparador, contexto) == NULL,
		     "No se puede buscar elementos en lista nula");

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_buscar_elemento(lista, comparador, contexto) == NULL,
		     "No se puede buscar elementos en lista vacia");
	int *elemento1 = (int *)10;
	void *void_elemento1 = elemento1;
	lista = lista_insertar(lista, void_elemento1);
	int *elemento2 = (int *)20;
	void *void_elemento2 = elemento2;
	lista = lista_insertar(lista, void_elemento2);
	int *elemento3 = (int *)30;
	void *void_elemento3 = elemento3;
	lista = lista_insertar(lista, void_elemento3);
	pa2m_afirmar(lista_buscar_elemento(lista, comparador, NULL) == NULL,
		     "No se puede buscar con un contexto nulo");

	pa2m_afirmar(lista_buscar_elemento(lista, NULL, contexto) == NULL,
		     "No se puede buscar con un comparador nulo");

	int (*comparador_valido)(void *, void *) = comparador;
	pa2m_afirmar(
		lista_buscar_elemento(lista, comparador_valido,
				      void_elemento1) == void_elemento1,
		"se encuentra un elemento que existe en la lista, se puede buscar con contexto no nulo");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_valido,
					   (void *)1) == NULL,
		     "no se encuentra un elemento no que existe en la lista");

	lista = lista_insertar(lista, void_elemento1);
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_valido,
					   void_elemento1) == void_elemento1,
		     "se encuentra un elemento que esta duplicado en la lista");
}

void prueba_cantidad_elementos_y_lista_vacia()
{
	lista_t *lista = NULL;
	pa2m_afirmar(lista_vacia(lista),
		     "lista_vacia devuelve true cuando la lista es NULL");
	size_t cantidad_elementos = lista_tamanio(lista);
	pa2m_afirmar(cantidad_elementos == 0,
		     "la cantidad de elementos de una lista nula es 0");

	lista = lista_crear(lista);
	pa2m_afirmar(lista_vacia(lista),
		     "lista_vacia devuelve true cuando la lista esta vacia");
	cantidad_elementos = lista_tamanio(lista);
	pa2m_afirmar(cantidad_elementos == 0,
		     "la cantidad de elementos de una lista vacia es 0");

	int *elemento = calloc(1, sizeof(int));
	*elemento = 0;
	void *elemento_void = elemento;
	while (lista->cantidad_nodos < 3) {
		lista = lista_insertar(lista, elemento_void);
	}
	pa2m_afirmar(
		!lista_vacia(lista),
		"lista_vacia devuelve false cuando la lista tiene elementos");
	cantidad_elementos = lista_tamanio(lista);
	pa2m_afirmar(
		cantidad_elementos == 3,
		"se verifica correctamente que la lista tiene 3 elementos");
}

void prueba_primer_ultimo_elemento(lista_t *lista)
{
	lista_t *lista_nueva = NULL;
	void *primer_elemento = lista_primero(lista_nueva);
	pa2m_afirmar(primer_elemento == NULL,
		     "lista_primero() devuelve NULL cuando la lista es nula");
	void *ultimo_elemento = lista_ultimo(lista_nueva);
	pa2m_afirmar(ultimo_elemento == NULL,
		     "lista_ultimo() devuelve NULL cuando la lista es nula");

	lista_nueva = lista_crear();
	primer_elemento = lista_primero(lista_nueva);
	pa2m_afirmar(
		primer_elemento == NULL,
		"lista_primero() devuelve NULL cuando la lista esta vacia");
	ultimo_elemento = lista_ultimo(lista_nueva);
	pa2m_afirmar(ultimo_elemento == NULL,
		     "lista_ultimo() devuelve NULL cuando la lista esta vacia");

	primer_elemento = lista_primero(lista);
	pa2m_afirmar(primer_elemento == lista->nodo_inicio->elemento,
		     "lista_primero() devuelve elemento correcto");

	int *elemento = calloc(1, sizeof(int));
	*elemento = 10;
	void *elemento_void = elemento;
	lista = lista_insertar_en_posicion(lista, elemento_void, 0);
	primer_elemento = lista_primero(lista);
	pa2m_afirmar(
		(primer_elemento == elemento_void) &&
			(primer_elemento == lista->nodo_inicio->elemento),
		"luego de insertar elemento al principio, lista_primero() devuelve elemento correcto");

	ultimo_elemento = lista_ultimo(lista);
	pa2m_afirmar(ultimo_elemento == lista->nodo_final->elemento,
		     "lista_ultimo() devuelve elemento correcto");

	*elemento = 15;
	elemento_void = elemento;
	lista = lista_insertar(lista, elemento_void);
	ultimo_elemento = lista_ultimo(lista);
	pa2m_afirmar(
		(ultimo_elemento == elemento_void) &&
			(ultimo_elemento == lista->nodo_final->elemento),
		"luego de insertar elemento al final, lista_ultimo() devuelve elemento correcto");
}

void pruebas_iterador_externo()
{
	lista_t *lista = NULL;
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(
		iterador == NULL,
		"al crear iterador con una lista nula, el iterador es nulo");
	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador),
		     "un iterador nulo no tiene siguiente");
	pa2m_afirmar(!lista_iterador_avanzar(iterador),
		     "no se puede avanzar en un iterador nulo");
	pa2m_afirmar(
		!lista_iterador_elemento_actual(iterador),
		"al buscar un elemento en el iterador nulo, se devuelve NULL");

	lista = lista_crear();
	iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL && iterador->nodo_actual == NULL &&
			     iterador->lista->nodo_inicio == NULL,
		     "se puede crear iterador de una lista vacia");
	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador),
		     "un iterador de lista vacia no tiene siguiente");
	pa2m_afirmar(!lista_iterador_avanzar(iterador),
		     "no se puede avanzar en un iterador de lista vacia");
	pa2m_afirmar(
		!lista_iterador_elemento_actual(iterador),
		"al buscar un elemento en el iterador de lista vacia, se devuelve NULL");

	int *elemento = malloc(sizeof(int));
	*elemento = 1;
	void *elemento_void = elemento;
	while ((*elemento) < 3) {
		lista = lista_insertar(lista, elemento_void);
		(*elemento)++;
	}

	iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL && iterador->nodo_actual != NULL &&
			     iterador->lista->nodo_inicio != NULL,
		     "se puede crear iterador de una lista con elementos");
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador),
		"se podria avanzar en un iterador que todavia tiene elementos para iterar");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) != NULL,
		"al buscar un elemento en el iterador de lista vacia, se devuelve el elemento");
	pa2m_afirmar(
		iterador->nodo_actual->siguiente != NULL,
		"se verifica que el iterador tiene mas elementos por iterar");
	pa2m_afirmar(lista_iterador_avanzar(iterador),
		     "se avanza en un iterador que tiene elementos por iterar");
	while (lista_iterador_tiene_siguiente(iterador)) {
		lista_iterador_avanzar(iterador);
	}
	pa2m_afirmar(
		!lista_iterador_tiene_siguiente(iterador),
		"NO se podria avanzar en un iterador que NO tiene elementos para iterar");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == NULL,
		"al buscar un elemento en el iterador de lista que no tiene elementos por obtener, se devuelve NULL");
	pa2m_afirmar(
		iterador->nodo_actual == NULL,
		"se verifica que el iterador no tiene mas elementos por iterar");
	pa2m_afirmar(
		!lista_iterador_avanzar(iterador),
		"no se avanza en un iterador que no tiene elementos por iterar");

	free(elemento);
	free(iterador);
	free(lista);
}

bool funcion1(void *elemento, void *auxiliar)
{
	return *(int *)elemento >= 0;
}

bool funcion2(void *elemento, void *auxiliar)
{
	int *aux = auxiliar;
	*aux += *(int *)elemento;

	return *aux < 3;
}

void pruebas_iterador_interno()
{
	int numeros[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int sumador = 0;
	pa2m_afirmar(lista_con_cada_elemento(NULL, funcion2, &sumador) == 0,
		     "Se prueba iterar una lista nula");

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion2, &sumador) == 0,
		     "Se prueba iterar una lista vacía");

	for (int i = 0; i < 10; i++) {
		lista_insertar(lista, numeros + i);
	}

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &sumador) == 0,
		     "Se prueba iterar una lista con una función nula");
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion1, NULL) == 10,
		     "Se prueba iterar una lista con un auxiliar nulo");
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion1, &sumador) == 10,
		     "Se prueba iterar una lista en su totalidad");
	sumador = 0;
	pa2m_afirmar(
		lista_con_cada_elemento(lista, funcion2, &sumador) == 3,
		"Se prueba iterar una lista deteniéndose antes de terminar de visitar todos los elementos");

	lista_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== CREAR LISTA ========================");
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
		"\n======================== BUSCAR ELEMENTO ========================");
	prueba_buscar_elemento(lista);
	pa2m_nuevo_grupo(
		"\n======================== CANTIDAD ELEMENTOS y LISTA VACIA ========================");
	prueba_cantidad_elementos_y_lista_vacia();
	pa2m_nuevo_grupo(
		"\n======================== PRIMER y ULTIMO ELEMENTO ========================");
	prueba_primer_ultimo_elemento(lista);
	pa2m_nuevo_grupo(
		"\n======================== ITERADOR EXTERNO ========================");
	pruebas_iterador_externo(lista);
	pa2m_nuevo_grupo(
		"\n======================== ITERADOR INTERNO ========================");
	pruebas_iterador_interno(lista);

	return pa2m_mostrar_reporte();
}
