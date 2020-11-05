#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct lista {
    struct nodo *primer_elemento;
    struct nodo *ultimo_elemento;
    size_t largo;
} lista_t;

// funcion auxiliar
nodo_t *crear_nodo(void *valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = valor;
    nodo->siguiente_nodo = NULL;
    return nodo;
};
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
    if(lista_esta_vacia(lista)) {
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
    nodo_t *nodo_aux = crear_nodo(0);
    nodo_aux->siguiente_nodo = lista->primer_elemento;
    void *p = nodo_aux->siguiente_nodo->dato;
    // printf("(valor de p) %d\n",*(int*)p );
    lista->primer_elemento = lista->primer_elemento->siguiente_nodo;
    lista->largo--;
    if (lista_esta_vacia(lista)) lista->ultimo_elemento = NULL;
    free(nodo_aux->siguiente_nodo);
    free(nodo_aux);
    return p;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
  nodo_t *nodo = crear_nodo(dato);
  if (!nodo) return false;
  if(lista_esta_vacia(lista)) {
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
       while (lista->primer_elemento) {
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
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *alpha) {
    nodo_t * n = lista->primer_elemento;
    while (n) {
      visitar(n->dato,alpha);
      n = n->siguiente_nodo;
    }
    free(n);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/
lista_iter_t *lista_iter_crear(lista_t *lista) {
    // printf("Entrando a lista_iter_crear\n");
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->actual = lista->primer_elemento;
    iter->anterior = NULL;
    // printf("Iter apunta a %d\n", *(int *)iter->actual->dato);
    return iter;
}
void *lista_iter_ver_actual(const lista_iter_t *iter) {
  return iter->actual->dato;
}
void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}
bool lista_iter_avanzar(lista_iter_t *iter) {
    if (iter->actual == NULL) return false;
    iter->anterior = iter->actual;
    iter->actual = iter->actual->siguiente_nodo;
    return true;
}
bool lista_iter_al_final(const lista_iter_t *iter) {
  return iter->actual == NULL;
}
/*
int main() {
  printf("compila\n");


  printf("INICIO DE PRUEBAS ITERADOR EXTERNO\n");

  lista_t * nums = lista_crear();
  int n[] = {10,20,340,39};
  lista_insertar_ultimo(nums, &n[0]);
  lista_insertar_ultimo(nums, &n[1]);
  lista_insertar_ultimo(nums, &n[2]);
  lista_insertar_ultimo(nums, &n[3]);

  lista_iter_t *iter = lista_iter_crear(nums);
  // printf("iter es %p\n", iter);
  int ok = n[0] == *(int *)iter->actual->dato;
  printf("iter->actual->dato= %d\n", *(int *)iter->actual->dato);
  printf("El iter accede a primer elemento de lista %d\n", ok);
  lista_destruir(nums, NULL);
  return 0;
}
*/
