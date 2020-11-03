#include "lista.h"
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

// funcion auxiliar
nodo_t *crear_nodo(void *valor) {
    nodo_t nodo = malloc(sizeof(nodo_t));
    if (!nodo) return null;
    nodo->dato = valor;
    nodo->siguiente_nodo = NULL;
    return nodo;
}
