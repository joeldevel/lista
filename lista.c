#include "lista.h"
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *siguiente_nodo;
} nodo_t;

typedef struct lista {
    struct nodo *primer_elemento;
    struct nodo *ultimo_elemento;
    size_t largo;
} lista_t;

typedef struct lista_iter {
    struct nodo **actual;
    struct nodo **anterior;
    struct nodo **primer_elemento_lista;
    struct nodo **ultimo_elemento_lista;
    size_t *tam_lista;
} lista_iter_t;

// funcion auxiliar
nodo_t *crear_nodo(void *valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = valor;
    nodo->siguiente_nodo = NULL;
    return nodo;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t *lista_crear(void) {
    lista_t *lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;
    lista->primer_elemento = NULL;
    lista->ultimo_elemento = NULL;
    lista->largo = 0;
    return lista;
}
bool lista_esta_vacia(const lista_t *lista) {
    return lista->largo == 0;
}
bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t *nodo = crear_nodo(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->primer_elemento = nodo;
        lista->ultimo_elemento = nodo;
        lista->largo++;
        return true;
    }
    nodo->siguiente_nodo = lista->primer_elemento;
    lista->primer_elemento = nodo;
    lista->largo++;
    return true;
}
void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    nodo_t *nodo_aux = crear_nodo(NULL);
    nodo_aux->siguiente_nodo = lista->primer_elemento;
    void *p = nodo_aux->siguiente_nodo->dato;
    lista->primer_elemento = lista->primer_elemento->siguiente_nodo;
    lista->largo--;
    if (lista_esta_vacia(lista)) {
        lista->ultimo_elemento = NULL;
    }
    free(nodo_aux->siguiente_nodo);
    free(nodo_aux);
    return p;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = crear_nodo(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->primer_elemento = nodo;
        lista->ultimo_elemento = nodo;
        lista->largo++;
        return true;
    }
    lista->ultimo_elemento->siguiente_nodo = nodo;
    lista->ultimo_elemento = lista->ultimo_elemento->siguiente_nodo;
    lista->largo++;
    return true;
}
void *lista_ver_primero(const lista_t *lista) {
    if (lista->primer_elemento== NULL) return NULL;
    if (lista_esta_vacia(lista)) return NULL;
    return lista->primer_elemento->dato;
}
void *lista_ver_ultimo(const lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ultimo_elemento->dato;
}
size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    if (destruir_dato == NULL) {
       while (lista->primer_elemento != NULL) {
           lista_borrar_primero(lista);
       }
    }
    else {
        while (lista->primer_elemento) {
            destruir_dato(lista->primer_elemento->dato);
	          lista_borrar_primero(lista);
	      }
    }
  	free(lista->primer_elemento);
  	free(lista->ultimo_elemento);
  	free(lista);
}

// El iterador
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t *n = lista->primer_elemento;
    bool seguir = true;
    while (n && seguir) {
        seguir = visitar(n->dato,extra);
        n = n->siguiente_nodo;
    }
    // free(n);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/
lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->primer_elemento_lista = &lista->primer_elemento;
    iter->ultimo_elemento_lista = &lista->ultimo_elemento;
    iter->tam_lista = &lista->largo;
    iter->anterior = NULL;
    if (lista_esta_vacia(lista)) {
        iter->actual = &lista->primer_elemento;
        return iter;
    }
    iter->actual = &lista->primer_elemento;
    return iter;
}
size_t lista_iter_largo(const lista_iter_t * iter) {
    return *(size_t*)iter->tam_lista;
}
void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (lista_iter_largo(iter) == 0) return NULL;
    if (lista_iter_al_final(iter)) return NULL;
    return (*iter->actual)->dato;
}
void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}
bool lista_iter_avanzar(lista_iter_t *iter) {
    if (lista_iter_largo(iter) == 0) return false;
    if (iter->actual == NULL || *iter->actual==NULL) {
        return false;
    }
    iter->anterior = iter->actual;
    if ((void*)(*(iter->actual))->siguiente_nodo == NULL) {
        iter->actual = NULL;
        return true;
    }
    iter->actual = &(*(iter->actual))->siguiente_nodo;
    return true;
}
bool lista_iter_al_final(const lista_iter_t *iter) {
    if (lista_iter_largo(iter) == 0) return true;
    if (iter->actual == NULL) return true;
    return *iter->actual == NULL;
}
bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t *nodo_a_insertar = crear_nodo(dato);
    if (!nodo_a_insertar) return false;
    // lista vacia
    if (lista_iter_largo(iter) == 0) {
        *iter->primer_elemento_lista = nodo_a_insertar;
        *iter->ultimo_elemento_lista = nodo_a_insertar;
        iter->actual = iter->primer_elemento_lista;
        iter->anterior = NULL;
        *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
        return true;
    }
    // insertar al principio
    if (iter->anterior == NULL) {
        nodo_a_insertar->siguiente_nodo = *iter->primer_elemento_lista;
        *iter->primer_elemento_lista = nodo_a_insertar;
        iter->actual = iter->primer_elemento_lista;
        *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
        return true;
    }
    // insertar en el medio
    if (iter->actual != NULL && iter->anterior != NULL) {
        nodo_a_insertar->siguiente_nodo = *iter->actual;
        ((*iter->anterior)->siguiente_nodo) = nodo_a_insertar;
        *iter->actual = nodo_a_insertar;
        *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
        return true;
    }
    // insertar al final
    ((*iter->ultimo_elemento_lista)->siguiente_nodo) = nodo_a_insertar;
    *iter->ultimo_elemento_lista = nodo_a_insertar;
    iter->actual = iter->ultimo_elemento_lista;
    *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
    return true;
}
void *lista_iter_borrar(lista_iter_t *iter) {
    if ((*(iter->actual)) == NULL) return false;
    if (lista_iter_largo(iter) == 0) {
        return NULL;
    }
    if (lista_iter_largo(iter) == 1) {
        if ((*(iter->actual)) == NULL) return false;
        nodo_t *nodo_a_borrar = (*(iter->actual));
        void *dato_a_devolver = (*(iter->actual))->dato;
        *iter->primer_elemento_lista = NULL;
        *iter->ultimo_elemento_lista = NULL;
        iter->actual = iter->primer_elemento_lista;
        *(iter->tam_lista) = (*(size_t*)iter->tam_lista)-1;
        free(nodo_a_borrar);
        return dato_a_devolver;
    }
    // borrar al principio
    if (iter->anterior == NULL || (*iter->anterior) == NULL) {
        nodo_t *nodo_a_borrar = (*(iter->actual));
        void *dato_a_devolver = (*(iter->actual))->dato;

        *iter->primer_elemento_lista = (*iter->primer_elemento_lista)->siguiente_nodo;
        iter->actual = iter->primer_elemento_lista;
        *(iter->tam_lista)=(*(size_t*)iter->tam_lista)-1;
        free(nodo_a_borrar);
        return dato_a_devolver;
    }
    // borrar al final
    if (((*iter->actual)->siguiente_nodo) == NULL && !(iter->anterior == NULL)) {
        nodo_t *nodo_a_borrar = (*(iter->actual));
        void *dato_a_devolver = (*(iter->actual))->dato;
        *iter->ultimo_elemento_lista = *iter->anterior;
        (*iter->ultimo_elemento_lista)->siguiente_nodo = NULL;
        *(iter->tam_lista)=(*(size_t*)iter->tam_lista)-1;
        free(nodo_a_borrar);
        return dato_a_devolver;
    }
    // borrar en el medio
    // if (iter->anterior != NULL && ((*iter->actual)->siguiente_nodo) != NULL) {
        nodo_t *nodo_a_borrar = (*(iter->actual));
        void *dato_a_devolver = (*(iter->actual))->dato;
        (*iter->anterior)->siguiente_nodo= (*iter->actual)->siguiente_nodo;
        free( nodo_a_borrar);
        iter->actual = &(*iter->anterior)->siguiente_nodo;
        *(iter->tam_lista)=(*(size_t*)iter->tam_lista)-1;
        return dato_a_devolver;
    // }

    // return NULL;
}
