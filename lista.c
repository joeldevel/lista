#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

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
    // struct nodo **actual;
    // struct nodo **anterior;
    // struct nodo **primer_elemento_lista;
    // struct nodo **ultimo_elemento_lista;
    nodo_t *actual;
    nodo_t *anterior;
    lista_t *lista;
    // size_t *tam_lista;
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
        // lista->primer_elemento = nodo;
        lista->ultimo_elemento = nodo;
        // lista->largo++;
        // return true;
    } else {
      nodo->siguiente_nodo = lista->primer_elemento;
    }
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
        // lista->ultimo_elemento = NULL;
        lista->ultimo_elemento = lista->primer_elemento;
    }
    free(nodo_aux->siguiente_nodo);
    free(nodo_aux);
    return p;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = crear_nodo(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->primer_elemento = lista->ultimo_elemento = nodo;
        // lista->ultimo_elemento = nodo;
        // lista->largo++;
        // return true;
    } else {
       lista->ultimo_elemento->siguiente_nodo = nodo;
       lista->ultimo_elemento = lista->ultimo_elemento->siguiente_nodo;
    }
    lista->largo++;
    return true;
}
void *lista_ver_primero(const lista_t *lista) {
    // if (lista->primer_elemento == NULL) return NULL;
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
    // if (destruir_dato == NULL) {
       while (lista->primer_elemento) {
            if (destruir_dato) destruir_dato(lista->primer_elemento->dato);
           lista_borrar_primero(lista);
       }
    // }
    // else {
        // while (lista->primer_elemento) {
            // destruir_dato(lista->primer_elemento->dato);
	          // lista_borrar_primero(lista);
	      // }
    // }
  	// free(lista->primer_elemento);
  	// free(lista->ultimo_elemento);
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
    iter->lista = lista;
    iter->actual = lista->primer_elemento;
    iter->anterior = NULL;
    // iter->primer_elemento_lista = &lista->primer_elemento;
    // iter->ultimo_elemento_lista = &lista->ultimo_elemento;
    // iter->tam_lista = &lista->largo;
    // iter->anterior = NULL;
    // if (lista_esta_vacia(lista)) {
    //     iter->actual = &lista->primer_elemento;
    //     return iter;
    // }
    // iter->actual = &lista->primer_elemento;
    // printf("Se crea el iterador: %p==%p\n",iter->lista, lista );
    return iter;
}
size_t lista_iter_largo(const lista_iter_t * iter) {
    return (size_t)iter->lista->largo;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    //1 lista vacia
    if (lista_esta_vacia(iter->lista)) {
      printf("la lista esta vacia\n" );
      return NULL;
    }
    //2 al final de la lista
    if (lista_iter_al_final(iter)) return NULL;
    // printf("ver actual  no esta en el final\n");
    // 3 caso general
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    // tal vez esto es redundante
    if (lista_esta_vacia(iter->lista)) return true;
    // printf("lista_iter_al_final, iter->actual->dato =%lu\n", *(size_t*)iter->actual->dato);
    // if (iter->actual->dato==NULL && iter->anterior) return true;
    return iter->actual == NULL;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    // lista vacia o iterador al final, no puedo avanzar
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return false;
    //1 solo elemento, anterior es null
    if(iter->actual && !iter->anterior) {
        iter->anterior = iter->actual;
    } else {
      // caso general
        iter->anterior = iter->anterior->siguiente_nodo;
    }
    iter->actual = iter->actual->siguiente_nodo;
    return true;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
  nodo_t *nodo_a_insertar = crear_nodo(dato);
  if(!nodo_a_insertar) return false;
  // lista vacia
  if( lista_esta_vacia(iter->lista)) {
      printf("Se inserta en lista vacia: %p\n", dato);
      iter->lista->primer_elemento = iter->lista->ultimo_elemento =
      iter->actual = nodo_a_insertar;
      iter->lista->largo++;
      return true;
  }
  // insertar al final
  if( iter->actual == NULL ) {
    free(nodo_a_insertar);
    lista_insertar_ultimo(iter->lista, dato);
    iter->actual = iter->lista->ultimo_elemento;
    return true;
  }
  // insertar al principio
  if( iter->anterior==NULL && iter->actual!=NULL) {
      lista_insertar_primero(iter->lista, dato);
      return true;
  }
  // insertar en el medio
  if (!nodo_a_insertar) return false;
  nodo_a_insertar->siguiente_nodo = iter->actual;
  iter->anterior->siguiente_nodo = nodo_a_insertar;
  iter->actual = iter->actual->siguiente_nodo;
  iter->lista->largo++;
  return true;
}

/*
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
*/
