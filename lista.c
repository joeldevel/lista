#include "lista.h"
#include <stdlib.h>

typedef struct nodo {
    void * dato;
    struct nodo * siguiente_nodo;
} nodo_t;

typedef struct lista {
    struct nodo * primer_elemento;
    struct nodo * ultimo_elemento;
    size_t largo;
} lista_t;

typedef struct lista_iter {
    nodo_t * actual;
    nodo_t * anterior;
    lista_t * lista;
} lista_iter_t;

// funcion auxiliar
nodo_t * crear_nodo(void * valor) {
    nodo_t * nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = valor;
    nodo->siguiente_nodo = NULL;
    return nodo;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t * lista_crear(void) {
    lista_t * lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;
    lista->primer_elemento = NULL;
    lista->ultimo_elemento = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t * lista) {
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t * lista, void * dato) {
    nodo_t * nodo = crear_nodo(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->ultimo_elemento = nodo;
    } else {
        nodo->siguiente_nodo = lista->primer_elemento;
    }
    lista->primer_elemento = nodo;
    lista->largo++;
    return true;
}

void * lista_borrar_primero(lista_t * lista) {
    if (lista_esta_vacia(lista)) return NULL;
    nodo_t * nodo_aux = crear_nodo(NULL);
    nodo_aux->siguiente_nodo = lista->primer_elemento;
    void * p = nodo_aux->siguiente_nodo->dato;
    lista->primer_elemento = lista->primer_elemento->siguiente_nodo;
    lista->largo--;
    if (lista_esta_vacia(lista)) {
        lista->ultimo_elemento = lista->primer_elemento;
    }
    free(nodo_aux->siguiente_nodo);
    free(nodo_aux);
    return p;
}

bool lista_insertar_ultimo(lista_t * lista, void * dato) {
    nodo_t * nodo = crear_nodo(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->primer_elemento = lista->ultimo_elemento = nodo;
    } else {
        lista->ultimo_elemento->siguiente_nodo = nodo;
        lista->ultimo_elemento = lista->ultimo_elemento->siguiente_nodo;
    }
    lista->largo++;
    return true;
}

void * lista_ver_primero(const lista_t * lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->primer_elemento -> dato;
}

void * lista_ver_ultimo(const lista_t * lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ultimo_elemento -> dato;
}

size_t lista_largo(const lista_t * lista) {
    return lista->largo;
}

void lista_destruir(lista_t * lista, void( * destruir_dato)(void * )) {
    // if (destruir_dato == NULL) {
    while (lista->primer_elemento) {
        if (destruir_dato) {
            destruir_dato(lista->primer_elemento->dato);
        }
        lista_borrar_primero(lista);
    }
    free(lista);
}

// El iterador
void lista_iterar(lista_t * lista, bool visitar(void * dato, void * extra), void * extra) {
    nodo_t * n = lista->primer_elemento;
    bool seguir = true;
    while (n && seguir) {
        seguir = visitar(n->dato, extra);
        n = n->siguiente_nodo;
    }
    // free(n);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t * lista_iter_crear(lista_t * lista) {
    lista_iter_t * iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->lista = lista;
    iter->actual = iter->lista->primer_elemento;
    iter->anterior = NULL;

    return iter;
}
size_t lista_iter_largo(const lista_iter_t * iter) {
    return (size_t) iter->lista->largo;
}

void lista_iter_destruir(lista_iter_t * iter) {
    free(iter);
}

void * lista_iter_ver_actual(const lista_iter_t * iter) {
    //1 lista vacia
    if (lista_esta_vacia(iter->lista)) {
        return NULL;
    }
    //2 al final de la lista
    if (lista_iter_al_final(iter)) return NULL;
    // 3 caso general
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t * iter) {
    return iter->actual == NULL;
}

bool lista_iter_avanzar(lista_iter_t * iter) {
    // lista vacia o iterador al final, no puedo avanzar
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return false;
    //1 solo elemento, anterior es null
    if (iter->actual && !iter->anterior) {
        iter->anterior = iter->actual;
    } else {
        // caso general
        iter->anterior = iter->anterior->siguiente_nodo;
    }
    iter->actual = iter->actual->siguiente_nodo;
    return true;
}

bool lista_iter_insertar(lista_iter_t * iter, void * dato) {
    // lista vacia
    if (lista_esta_vacia(iter->lista)) {
        lista_insertar_primero(iter->lista, dato);
        iter->actual = iter->lista->primer_elemento;
        return true;
    }
    // insertar al final --lista no vacia
    if (iter->actual == NULL) {
        lista_insertar_ultimo(iter->lista, dato);
        iter->actual = iter->lista->ultimo_elemento;
        return true;
    }
    // insertar al principio --lista no vacia
    if (iter->anterior == NULL && iter->actual != NULL) {
        lista_insertar_primero(iter->lista, dato);
        iter->actual = iter->lista->primer_elemento;
        return true;
    }
    // caso general
    nodo_t * nodo_a_insertar = crear_nodo(dato);
    if (!nodo_a_insertar) return false;
    nodo_a_insertar->siguiente_nodo = iter->actual;
    iter->anterior->siguiente_nodo = nodo_a_insertar;
    iter->actual = iter->actual->siguiente_nodo;
    iter->lista->largo++;
    return true;
}

// /*
void * lista_iter_borrar(lista_iter_t * iter) {
    // borrar cuando el iterador est al final o lista vacia
    if (iter->actual == NULL) return NULL;

    // lista con 1 elemento
    if (lista_iter_largo(iter) == 1) {
        void * dato_a_devolver = lista_borrar_primero(iter->lista);
        iter->actual = iter->lista->primer_elemento;
        return dato_a_devolver;
    }

    // borrar el ultimo elemento
    if (iter->actual == iter->lista->ultimo_elemento &&
        iter->lista->ultimo_elemento != iter->lista->primer_elemento) {
        nodo_t * nodo_aux = crear_nodo(NULL);
        void * dato_a_devolver = iter->actual->dato;
        nodo_aux->siguiente_nodo = iter->lista->ultimo_elemento;
        free(nodo_aux->siguiente_nodo);
        iter->lista->ultimo_elemento = iter->anterior;
        iter->actual = iter->lista->ultimo_elemento;
        iter->lista->ultimo_elemento->siguiente_nodo = NULL;
        iter->lista->largo--;

        free(nodo_aux);
        return dato_a_devolver;
    } else {
        // caso general
        nodo_t * nodo_aux = crear_nodo(NULL);
        void * dato_a_devolver = iter->actual->dato;
        nodo_aux->siguiente_nodo = iter->actual;
        if (iter->anterior) {
            iter->anterior->siguiente_nodo = iter->actual->siguiente_nodo;
        } else {
            // reacomodar la lista
            iter->lista->primer_elemento = iter->actual->siguiente_nodo;
        }
        iter->actual = iter->actual->siguiente_nodo;

        free(nodo_aux->siguiente_nodo);
        free(nodo_aux);
        iter->lista->largo--;
        return dato_a_devolver;
    }

    return NULL;
}
