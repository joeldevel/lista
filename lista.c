#include "lista.h"
#include <stdio.h>
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

 /*
int main(int argc, char *argv[]) {
    printf("Compila!\n" );
    lista_t * lista = lista_crear();
    printf("La lista esta vacia?: %d\n", lista_esta_vacia(lista));
    // int *d = malloc(sizeof(int));
    int d = 33;
    int p = 987654;
    int u = 123456;
    lista_insertar_primero(lista, &d);
    lista_insertar_primero(lista, &d);
    lista_insertar_primero(lista, &p);
    lista_insertar_ultimo(lista, &u);
    // lista_insertar_primero(lista, &d);
    printf("La lista esta vacia?: %d\n", lista_esta_vacia(lista));
    printf("largo?: %lu\n", lista_largo(lista));
    printf("ver primero?: %d\n", *(int *)lista_ver_primero(lista));
    printf("ver ultimo?: %d\n", *(int *)lista_ver_ultimo(lista));
    lista_borrar_primero(lista);
    printf("ver primero?: %d\n", *(int *)lista_ver_primero(lista));
    lista_borrar_primero(lista);
    lista_borrar_primero(lista);
    lista_borrar_primero(lista);
    // int *p = (int*)lista_borrar_primero(lista);
    printf("largo?: %lu\n", lista_largo(lista));
    lista_destruir(lista, NULL);
    // free(lista->primer_elemento->dato);
    // free(lista->primer_elemento);
    // free(lista->primer_elemento);
    // free(lista->ultimo_elemento);
    // free(lista->ultimo_elemento);
    //free(lista);
    // free(p);
    return 0;
}
*/
