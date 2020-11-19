#include "lista.h"
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *siguiente;
} nodo_t;

typedef struct lista {
    struct nodo *primero;
    struct nodo *ultimo;
    size_t largo;
} lista_t;

typedef struct lista_iter {
    struct nodo **actual;
    struct nodo **anterior;
    struct nodo **primero_lista;
    struct nodo **ultimo_lista;
    size_t *tam_lista;
} lista_iter_t;

// funcion auxiliar
nodo_t *crear_nodo(void *valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = valor;
    nodo->siguiente = NULL;
    return nodo;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t *lista_crear(void) {
    lista_t *lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t *nodo = crear_nodo(dato);
    if (!nodo) return false;
    // if (cola_esta_vacia(cola)) {
    //     cola->primero = nodo;
    // } else {
    //     cola->ultimo->siguiente_nodo = nodo;
    // }
    // cola->ultimo = nodo;
    // return true;
    if (lista_esta_vacia(lista)) {
        // lista->primero = nodo;
        lista->ultimo = nodo;
        // lista->largo++;
        // return true;
    }
    else {
      nodo->siguiente = lista->primero;

    }
    lista->primero = nodo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    // nodo_t *nodo_aux = crear_nodo(NULL);
    nodo_t *nodo_aux = lista->primero;
    // nodo_aux->siguiente = lista->primero;
    // void *p = nodo_aux->siguiente->dato;
    void *p = nodo_aux->dato;
    lista->primero = lista->primero->siguiente;
    lista->largo--;
    if (lista_esta_vacia(lista)) {
        lista->ultimo = NULL;
    }
    // free(nodo_aux->siguiente);
    free(nodo_aux);
    return p;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = crear_nodo(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->primero = nodo;
        lista->ultimo = nodo;
        // lista->largo++;
        // return true;
    }
    else {
        lista->ultimo->siguiente = nodo;
        lista->ultimo = lista->ultimo->siguiente;
    }
    lista->largo++;
    return true;
}

void *lista_ver_primero(const lista_t *lista) {
    // if (lista->primero== NULL) return NULL;
    // if (lista_esta_vacia(lista)) return NULL;
    // return lista->primero->dato;
    return lista_esta_vacia(lista) ? NULL : lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
  while (!lista_esta_vacia(lista)) {
      if (!(destruir_dato == NULL)) {
          destruir_dato(lista->primero->dato);
      }
      lista_borrar_primero(lista);

  }
    //
    // if (destruir_dato == NULL) {
    //    while (lista->primero != NULL) {
    //        lista_borrar_primero(lista);
    //    }
    // }
    // else {
    //     while (lista->primero) {
    //         destruir_dato(lista->primero->dato);
	  //         lista_borrar_primero(lista);
	  //     }
    // }
  	// free(lista->primero);
  	// free(lista->ultimo);
  	free(lista);
}

// El iterador
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t *n = lista->primero;
    // bool seguir = true;
    while (n && visitar(n->dato,extra)) {
        n = n->siguiente;
    }
    // free(n);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/
lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->primero_lista = &lista->primero;
    iter->ultimo_lista = &lista->ultimo;
    iter->tam_lista = &lista->largo;
    iter->anterior = NULL;
    if (lista_esta_vacia(lista)) {
        iter->actual = &lista->primero;
        return iter;
    }
    iter->actual = &lista->primero;
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
    if ((void*)(*(iter->actual))->siguiente == NULL) {
        iter->actual = NULL;
        return true;
    }
    iter->actual = &(*(iter->actual))->siguiente;
    return true;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    if (lista_iter_largo(iter) == 0) return true;
    return iter->actual == NULL ? true : *iter->actual == NULL;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t *nodo_a_insertar = crear_nodo(dato);
    if (!nodo_a_insertar) return false;
    if ( iter->anterior == NULL || lista_iter_largo(iter)==0) {
        // insertar al principio
        if (iter->anterior == NULL ) nodo_a_insertar->siguiente = *iter->primero_lista;
        *iter->primero_lista = nodo_a_insertar; // R
        iter->actual = iter->primero_lista; // R
        // lista vacia
        if ( lista_iter_largo(iter)==0)  *iter->ultimo_lista = nodo_a_insertar;
    } else if (iter->actual != NULL && iter->anterior != NULL) { // insertar en el medio
        nodo_a_insertar->siguiente = *iter->actual;
        ((*iter->anterior)->siguiente) = nodo_a_insertar;
        *iter->actual = nodo_a_insertar;
      }
      else  { // insertar al final
        ((*iter->ultimo_lista)->siguiente) = nodo_a_insertar;
        *iter->ultimo_lista = nodo_a_insertar;
        iter->actual = iter->ultimo_lista;
      }
    *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if ((*(iter->actual)) == NULL) return false;
    if (lista_iter_largo(iter) == 0) return NULL;

    nodo_t *nodo_a_borrar = (*(iter->actual));
    void *dato_a_devolver = (*(iter->actual))->dato;
    if (lista_iter_largo(iter) == 1) {
        if ((*(iter->actual)) == NULL) return false;
        *iter->primero_lista = NULL;
        *iter->ultimo_lista = NULL;
        iter->actual = iter->primero_lista;
    }
    // borrar al principio
    else if (iter->anterior == NULL || (*iter->anterior) == NULL) {

        *iter->primero_lista = (*iter->primero_lista)->siguiente;
        iter->actual = iter->primero_lista;
    }
    // borrar al final
    else if (((*iter->actual)->siguiente) == NULL && !(iter->anterior == NULL)) {
        *iter->ultimo_lista = *iter->anterior;
        (*iter->ultimo_lista)->siguiente = NULL;
    }
    else {
      // borrar en el medio
      (*iter->anterior)->siguiente= (*iter->actual)->siguiente;
      iter->actual = &(*iter->anterior)->siguiente;
    }
    *(iter->tam_lista) = (*(size_t*)iter->tam_lista)-1;
    free(nodo_a_borrar);
    return dato_a_devolver;

}
