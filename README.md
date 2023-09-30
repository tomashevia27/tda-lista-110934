<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# NOMBRE TP/TDA

## Repositorio de (Nombre Apellido) - (Padrón) - (Mail)

- Para compilar:

```bash
make pruebas_chanutron
```

- Para ejecutar:

```bash
./pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron
```
---
##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>






# AGREGAR AL FINAL
<div align="center">
<img width="70%" src="img/agregar_final.jpg">
</div>

# AGREGAR EN CUALQUIER POSICION
<div align="center">
<img width="70%" src="img/agregar_cualquiera.jpg">
</div>

# ELIMINAR AL FINAL
<div align="center">
<img width="70%" src="img/eliminar_final.jpg">
</div>

# ELIMINAR AL FINAL
<div align="center">
<img width="70%" src="img/eliminar_cualquiera.jpg">
</div>

---

## Respuestas a las preguntas teóricas

# EXPLICACION DE LISTA, PILA y COLA
Tanto la lista, como la pila y la cola, son TDAs que sirven para agrupar elementos. son similares en algunos aspectos pero diferentes en otros.
La lista agrupa los elementos desde un elemento que es el inicial, hasta el elemento final, todos los elementos tienen un elemento anterior (salvo el inicial) y un sucesor (salvo el final), en la lista se puede acceder a todos los elementos de la misma, se pueden quitar, agregar y obtener elementos en cualquier posicion de la lista.
En pila y cola no se puede acceder a todos los elementos de ellas.
La cola se caracteriza por utilizar la politica FIFO (el primero que entra, es el primero que sale). Solo se puede acceder al primer elemento de la cola, y se puede agregar solo al inicio y eliminar el primer elemento (si quisiera eliminar el ultimo elemento, primero se deben eliminar todos los anteriores)
La pila, usa la politica LIFO (ultimo que entra, primer que sale), al contrario que en la cola, solo se puede acceder al ultimo elemento, se puede insertar solo al final y eliminar el ultimo (mismo caso, si quiero obtener el primer elemento que se agrego, primero debo quitar todo los elementos posteriores)

para los 3 tdas en este programa se uso la misma estructura lista_t, donde para pila y cola solo se usaron las funciones necesarias para que cumplan con las caracteristicas antes mencionadas (agregar, quitar y obtener en el ultimo elemento para la pila y en el primero para la cola)

DIAGRAMA DE MEMORIA USADO PARA LISTA, PILA y COLA:
<div align="center">
<img width="70%" src="img/diagrama_memoria.jpg">
</div>


# COMPLEJIDAD LISTA SIMPLEMENTE ENLAZADA
  - como al primer nodo se puede acceder directamente, tanto insertar, como obtener y eliminar al inicio son O(1)
  - como en mi implementacion use una referencia al nodo final, puedo acceder directamente a ese nodo, entonces insertar y obtener al final son O(1), eliminar al final en cambio es O(n) ya que debe recorrer todos los nodos de la lista hasta obtener el anteultimo nodo.
  - tanto insertar, como obtener y eliminar al medio son O(n) ya que deberia recorrer los nodos anteriores de la lista hasta llegar al nodo en la posicion requerida (obtener) o al nodo anterior (insertar y eliminar)

## COMPLEJIDAD LISTA DOBLEMENTE ENLAZADA
 - las operaciones al inicio y final tienen la misma complejidad que la simplemente enlazada, la que se modifica es la de eliminar al final, en esta implementacion esta operacion es O(1) ya que desde el nodo final puedo acceder directamente al anteultimo nodo y asi eliminar el nodo final.
 - tanto insertar, como obtener y eliminar en el medio siguen siendo O(n), ya que por mas que arranquemos a recorrer en el inicio o el final, deberiamos recorrer una cantidad de nodos del vector, en el peor de los casos podriamos llegar a recorrer todo el vector.

## COMPLEJIDAD LISTA CON VECTOR DINAMICO
  - tanto para insertar como para eliminar al inicio se debe recorrer el vector para reacomodar los elementos, por lo tanto son O(n). obtener al inicio es O(1)
  - para insertar al final pueden ocurrir dos cosas, que el vector tenga lugar para insertar,ahi seria O(1), o que se haya llenado el vector y se deba agrandar usando realloc, aca seria O(n). obtener y eliminar al final son O(1) si se tiene una referencia al ultimo elemento. 
  - insertar, obtener y eliminar en el medio son O(n)

