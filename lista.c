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
    nodo_aux = lista->primer_elemento;
    void *p = nodo_aux->dato;
    printf("(valor de p) %d\n",*(int*)p );
    lista->primer_elemento = lista->primer_elemento->siguiente_nodo;
    lista->largo--;
    if (lista_esta_vacia(lista)) lista->ultimo_elemento = NULL;
    free( nodo_aux);
    return p;
}



 //
int main(int argc, char *argv[]) {
    printf("Compila!\n" );
    lista_t * lista = lista_crear();
    printf("La lista esta vacia?: %d\n", lista_esta_vacia(lista));
    int *d = malloc(sizeof(int));
    d = 33;
    lista_insertar_primero(lista, d);
    lista_insertar_primero(lista, d);
    lista_insertar_primero(lista, d);
    // lista_insertar_primero(lista, &d);
    printf("La lista esta vacia?: %d\n", lista_esta_vacia(lista));
    printf("largo?: %d\n", lista->largo);
    lista_borrar_primero(lista);
    // free(lista->primer_elemento->dato);

    free(lista->primer_elemento);
    // free(lista->primer_elemento);
    free(lista->ultimo_elemento);
    // free(lista->ultimo_elemento);
    free(lista);
    // free(d);
    return 0;
}
