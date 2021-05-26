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
            if (destruir_dato) {
                printf("en destruir dato\n" );
                destruir_dato(lista->primer_elemento->dato);
            }
            printf("fuera del if destruir dato\n" );
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
  printf("entrando a iteravanzar...\n" );
    // lista vacia o iterador al final, no puedo avanzar
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return false;
    //1 solo elemento, anterior es null
    if(iter->actual && !iter->anterior) {
      printf("if es true...\n" );
        iter->anterior = iter->actual;
    } else {
      // caso general
      printf("if es false...\n" );
        iter->anterior = iter->anterior->siguiente_nodo;
    }
    iter->actual = iter->actual->siguiente_nodo;
    return true;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
  // lista vacia
  if( lista_esta_vacia(iter->lista)) {
      // printf("Se inserta en lista vacia: %p\n", dato);
      lista_insertar_primero(iter->lista, dato);
      // iter->lista->primer_elemento = iter->lista->ultimo_elemento =
      // iter->actual = nodo_a_insertar;
      // iter->lista->largo++;
      iter->actual = iter->lista->primer_elemento;
      // free(nodo_a_insertar);
      return true;
  }
  // insertar al final --lista no vacia
  if( iter->actual == NULL ) {
      // free(nodo_a_insertar);
      lista_insertar_ultimo(iter->lista, dato);
      iter->actual = iter->lista->ultimo_elemento;
      return true;
  }
  // insertar al principio --lista no vacia
  if( iter->anterior==NULL && iter->actual!=NULL) {
      lista_insertar_primero(iter->lista, dato);
      iter->actual = iter->lista->primer_elemento;
      return true;
  }
  // caso general
  nodo_t *nodo_a_insertar = crear_nodo(dato);
  if(!nodo_a_insertar) return false;
  nodo_a_insertar->siguiente_nodo = iter->actual;
  iter->anterior->siguiente_nodo = nodo_a_insertar;
  iter->actual = iter->actual->siguiente_nodo;
  iter->lista->largo++;
  return true;
}

// /*
void *lista_iter_borrar(lista_iter_t *iter) {
    printf("entrndo a iter borrar\n" );
    // borrar cuando el iterador est al final o lista vacia
    if (iter->actual == NULL) return NULL;

    // lista con 1 elemento
    if (lista_iter_largo(iter) == 1) {
      printf("caso 1\n" );
        void *dato_a_devolver = lista_borrar_primero(iter->lista);
        iter->actual = iter->lista->primer_elemento;
        return dato_a_devolver;
    }

    // borrar el ultimo elemento
    if (iter->actual==iter->lista->ultimo_elemento &&
        iter->lista->ultimo_elemento!=iter->lista->primer_elemento) {
          printf("caso 2\n" );
          // printf("entrando al if de borrar el ultmo\n");
          nodo_t *nodo_aux = crear_nodo(NULL);
          void *dato_a_devolver = iter->actual->dato;
          nodo_aux->siguiente_nodo = iter->lista->ultimo_elemento;
          free(nodo_aux->siguiente_nodo);
          iter->lista->ultimo_elemento = iter->anterior;
          iter->actual = iter->lista->ultimo_elemento;
          iter->lista->ultimo_elemento->siguiente_nodo = NULL;
          // lista->primer_elemento = lista->primer_elemento->siguiente_nodo;
          iter->lista->largo--;
          // if (lista_esta_vacia(lista)) {
          //     lista->ultimo_elemento = lista->primer_elemento;
          // }
          free(nodo_aux);
        return dato_a_devolver;
    }
     else {
        printf("caso 3\n" );
        // return NULL;
        // caso general
        nodo_t *nodo_aux = crear_nodo(NULL);
        void *dato_a_devolver = iter->actual->dato;
        nodo_aux->siguiente_nodo = iter->actual;
        if( iter->anterior) {
            iter->anterior->siguiente_nodo = iter->actual->siguiente_nodo;
        }
        iter->lista->primer_elemento = iter->actual->siguiente_nodo;
        iter->actual = iter->actual->siguiente_nodo;
        // iter->lista->ultimo_elemento->siguiente_nodo = NULL;
        // lista->primer_elemento = lista->primer_elemento->siguiente_nodo;
        // if (lista_esta_vacia(lista)) {
        //     lista->ultimo_elemento = lista->primer_elemento;
        free(nodo_aux->siguiente_nodo);
        free(nodo_aux);
        // }
        iter->lista->largo--;
      return dato_a_devolver;
    }

    return NULL;
}
// */
