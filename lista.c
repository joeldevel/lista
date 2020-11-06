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
    printf("lista->largo=%lu\n",lista->largo);

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
  printf("Entrando a lista borran primero\n" );

    if (lista_esta_vacia(lista)) return NULL;
    nodo_t *nodo_aux = crear_nodo(NULL);
    nodo_aux->siguiente_nodo = lista->primer_elemento;
    void *p = nodo_aux->siguiente_nodo->dato;
    // printf("(valor de p) %d\n",*(int*)p );
    lista->primer_elemento = lista->primer_elemento->siguiente_nodo;
    lista->largo--;
    if (lista_esta_vacia(lista)) {
        lista->ultimo_elemento = NULL;
    }
    printf("Borrando %p\n", nodo_aux->siguiente_nodo);
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
    if (lista->primer_elemento== NULL) return NULL;
    if (lista_esta_vacia(lista)) return NULL;
    return lista->primer_elemento->dato;
}
void *lista_ver_ultimo(const lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ultimo_elemento->dato;
}
size_t lista_largo(const lista_t *lista) {
    // return (size_t)lista->largo/(sizeof(size_t));
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    printf("Entrando a lista destruir\n" );
    if (destruir_dato == NULL) {
      printf("Lista_destruir, NULL...\n");
       while (lista->primer_elemento) {
           lista_borrar_primero(lista);
       }
    }
    else {
        while (lista->primer_elemento) {
            printf("Lista_destruir borrando, destruir_dato\n");

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
    printf("Entrando a lista_iter_crear\n");
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->actual = &lista->primer_elemento;
    iter->anterior = NULL;
    // printf("Iter apunta a %d\n", *(int *)iter->actual->dato);
    iter->tam_lista = &lista->largo;
    printf("tam->lista=%p, lista->largo=%p", iter->tam_lista, &lista->largo);
    // printf("###tam y largo son iguales %d\n",iter->tam_lista==lista->largo);
    printf("FIN  lista_iter_crear\n");
    return iter;
}
size_t lista_iter_largo(const lista_iter_t * iter) {
    return (size_t)iter->tam_lista/(sizeof(size_t));
}
void *lista_iter_ver_actual(const lista_iter_t *iter) {
    return (*(iter->actual))->dato;
}
void lista_iter_destruir(lista_iter_t *iter) {
    // free(iter->actual);
    // free(iter->anterior);
    // free(iter->tam_lista);
    free(iter);
}
bool lista_iter_avanzar(lista_iter_t *iter) {
    if ((void*)iter->actual == NULL) {
      printf("#@@@@@@@@@@@@@Iter actual == NULL\n" );
      return false;
    }
    // primer elemento;
    if ((void*)iter->anterior==NULL) {
        iter->anterior = iter->actual;
        (*(iter->actual)) = (*(iter->actual))->siguiente_nodo;
        return true;
    }
    (*(iter->anterior)) = (*(iter->anterior))->siguiente_nodo;
    iter->actual = &(*(iter->actual))->siguiente_nodo;
    return true;
}
bool lista_iter_al_final(const lista_iter_t *iter) {
  if ((*(iter->actual)) == NULL)  {
    printf("$$$$$$$$$$$$$$$lista iter al final\n");
  }
  return (*(iter->actual)) == NULL;
}
bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
  printf("Entrando a lista_iter_insertar\n");

    nodo_t * nodo_aux = crear_nodo(dato);
    // lista vacia
    if (*(size_t*)iter->tam_lista == 0) {
          printf("\n\tinsertando en lista vacia\n" );
          (*(iter->actual)) = nodo_aux;
          *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
          // printf("\tpuntero tam->lista=%p\n", iter->tam_lista);
          // printf("iter->tam_lista %lu\n", lista_iter_largo(iter));
          return true;
    }
    // un solo elemento en lista, es como lista insertar al principio
    if ((void*)iter->actual != NULL && (void*)iter->anterior==NULL) {
      printf("\tinsertando en lista 1 elemento en lista\n" );
      nodo_aux->siguiente_nodo = (*(iter->actual));
      (*(iter->actual)) = nodo_aux;
      // iter->actual=iter->actual->siguiente_nodo;
      *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
      // printf("\tpuntero tam->lista=%p\n", iter->tam_lista);
      return true;
    }
    // iter al final
    if ((void*)iter->actual== NULL && (void*)iter->anterior != NULL) {
      printf("\tinsertando en lista al final\n" );

      (*(iter->anterior))->siguiente_nodo = nodo_aux;
      (*(iter->actual))= nodo_aux;
      // iter->actual=iter->actual->siguiente_nodo;
      *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
      // printf("\tpuntero tam->lista=%p\n", iter->tam_lista);
      return true;
    }
    printf("\tcaso general\n" );
    (*(iter->anterior))->siguiente_nodo = nodo_aux;
    nodo_aux->siguiente_nodo = *iter->actual;
    (*(iter->actual)) = (*(iter->anterior))->siguiente_nodo;
    *(iter->tam_lista)=(*(size_t*)iter->tam_lista)+1;
    printf("\tpuntero tam->lista=%p\n", iter->tam_lista);
    return true;
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
