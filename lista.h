#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

typedef struct lista lista_t;
typedef struct nodo nodo_t;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos enlistados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento al principio de la lista
// Pre: la lista fue creada
// Post: la lista contiene el elemento pasado como argumento al principio
// retorna true si se pudo insertar, caso contrario false
bool lista_insertar_primero(lista_t *lista, void *dato);

// Inserta   un elemento al final de la lista
// Pre: la lista fue creada
// Post: la lista contiene el elemento pasado como argumento al final
// retorna true si se pudo insertar, caso contrario false
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del último, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el tamaño de la lista
// Pre: la lista fue creada
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Recorre la lista y aplica visitar a cada dato de la misma
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador para la lista pasada como argumento
// Pre: la lista fue creada.
// Post: se devuelve un iterador para la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza al siguiente elemento de la lista.
// Pre: el iterador iter fue creado.
// Post: se devuelve true si se pudo avanzar, en caso contrario false.
bool lista_iter_avanzar(lista_iter_t *iter);

// Permite ver el elemento actual al que apunte el iterador.
// Pre: el iterador iter fue creado.
// Post: devuelve un puntero generico al elemento actual.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Permite saber si el iterador se encuentra al final de la lista.
// Pre: el iterador iter fue creado.
// Post: devuelve true si el elemento actual está al final de la lista.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador iter fue creado.
// Post: se libera la memoria que el iterador utilizaba.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta el dato en la posicion actual del iterador.
// Pre: el iterador iter fue creado.
// Post: devuelve true si pudo insertar el dato, en caso contrario false.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el dato en la posicion actual del iterador.
// Pre: el iterador iter fue creado.
// Post: devuelve el dato si pudo borrar el dato, en caso contrario NULL.
void *lista_iter_borrar(lista_iter_t *iter);

// Devuelve el largo de la lista sobre la que el iterador trabaja.
// Pre: el iterador iter fue creado.
// Post: devuelve la cantidad de elementos que tiene la lista sobre la que el iterador trabaja.
size_t lista_iter_largo(const lista_iter_t * iter);
/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_cola.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en cola.h
// (esto es, las pruebas no pueden acceder a los miembros del struct cola).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_cola_estudiante(void);

#endif  // LISTA_H
