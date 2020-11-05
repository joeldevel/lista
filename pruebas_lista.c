#include "lista.h"
#include "testing.h"
#include "pila.h"
//#include "cola.h"
#include<stdio.h>


/* Pruebas para una lista vacía. */
static void prueba_lista_vacia(void) {
    printf("INICIO DE PRUEBAS LISTA VACIA\n");

    lista_t *lista = lista_crear();
    print_test("Prueba la lista est vacía: ", lista_esta_vacia(lista));
    print_test("Borrar primero es NULL",NULL==lista_borrar_primero(lista));
    print_test("Ver primero es NULL",NULL==lista_ver_primero(lista));
    print_test("Ver ultimo es NULL",NULL==lista_ver_ultimo(lista));
    lista_destruir(lista, NULL);
}
static void prueba_lista_ver_primero_vacia_es_invalido(void) {
    printf("INICIO DE PRUEBAS VER PRIMERO EN LISTA VACÍA ES INVÁLIDO\n");
    lista_t *lista = lista_crear();
    print_test("Prueba ver primero en lista vacia es invalido: ", lista_ver_primero(lista)== NULL);
    lista_destruir(lista, NULL);
}
static void prueba_lista_ver_ultimo_vacia_es_invalido(void) {
    printf("INICIO DE PRUEBAS VER ULTIMO EN LISTA VACIA ES INVÁLIDO\n");
    lista_t *lista = lista_crear();
    print_test("Prueba ver ultimo en lista vacia es invalido: ", lista_ver_ultimo(lista)== NULL);
    lista_destruir(lista, NULL);
}
static void prueba_lista_insertar_primero(void) {
    printf("INICIO DE PRUEBAS INSERTAR PRIMERO\n");
    lista_t *lista = lista_crear();
    char dato = 'z';
    bool ok = true;
    ok &= lista_insertar_primero(lista,&dato);
    ok &= 'z'==*(char*) lista_ver_primero(lista);
    print_test("Prueba lista insertar primero: ", ok);
    lista_destruir(lista, NULL);
}
static void prueba_lista_borrar_vacia_la_lista(void) {
    printf("INICIO DE PRUEBAS BORRAR PRIMERO VACÍA LA LISTA\n");
    lista_t *lista = lista_crear();
    int dato = 1234;
    lista_insertar_primero(lista, &dato);
    bool ok = true;
    ok &= (1234 == *(int*)lista_ver_primero(lista));
    ok &= 1234== *(int*)lista_borrar_primero(lista);
    ok &= (lista_esta_vacia(lista));
    print_test("Prueba lista borrar primero deja vacía la lista: ", ok);
    lista_destruir(lista, NULL);
}
static void prueba_lista_volumen(void) {
    printf("INICIO DE PRUEBAS VOLUMEN\n");
    lista_t *lista = lista_crear();
    int M = 1000;
    int e[M];
    bool ok = true;
    for (int i=0; i<M; i++) {
        e[i] = i;
        ok &= lista_insertar_primero(lista, &e[i]);
    }
    print_test("Se insertaron los elementos: ", ok);

    for (int i=0; i<M; i++) {
        ok &= ((M-1-i)== *(int*)lista_borrar_primero(lista));
    }
    print_test("Los elementos estan en orden correcto: ", ok);
    lista_destruir(lista,NULL);
}
static void prueba_lista_se_puede_insertar_null(void) {
    printf("INICIO DE PRUEBAS SE PUEDE INSERTAR NULL\n");

    lista_t *lista = lista_crear();
    bool ok = lista_insertar_ultimo(lista, NULL);
    print_test("Se inserto el elemento ", ok);
    print_test("La lista NO esta vacia despues de insertar NULL ",!lista_esta_vacia(lista));
    print_test("El elemeno es NULL ", NULL==lista_ver_ultimo(lista));
    lista_destruir(lista, NULL);

}
// wrapper
void pila_destruir_wrapper(void *elem) {
    pila_destruir(elem);
}
static void prueba_lista_de_pilas(void) {
    printf("INICIO DE PRUEBAS LISTA DE PILAS\n");

    lista_t *l = lista_crear();
    //crear tres pilas
    pila_t *pi1 = pila_crear();
    pila_t *pi2 = pila_crear();
    pila_t *pi3 = pila_crear();
    // llenarlas con algo
    int tam_nums = 4;
    int tam_chars = 3;
    int tam_bools = 4;
    int nums[] = {10,20,30,40};
    char chars[] = {'z','f','n'};
    bool bools[] = {true, true, false, true};
    bool ok = true;
    for (int i=0; i < tam_nums; i++) {
    	ok &= pila_apilar(pi1, &nums[i]);
    }
    print_test("Se insertaron en pi1 ", ok);
    for (int i=0; i < tam_chars; i++) {
    	ok &= pila_apilar(pi2, &chars[i]);
    }
    print_test("Se insertaron en pi2 ", ok);
    for (int i=0; i < tam_bools; i++) {
    	ok &= pila_apilar(pi3, &bools[i]);
    }
    print_test("Se insertaron en pi3 ", ok);
    // insertar 2 primero y una ultimo

    ok &= lista_insertar_primero(l, pi1);
    print_test("lista_insertar_primero pi1 ", ok);
    ok &= lista_insertar_primero(l, pi2);
    print_test("lista_insertar_primero pi2 ", ok);
    ok &= lista_insertar_ultimo(l, pi3);
    print_test("lista_insertar_ultimo pi3 ", ok);
    // sacarlas y ver si coinciden los datos
    pila_t *paux = lista_borrar_primero(l);
    for (int i=0; i < tam_chars; i++) {
    	 ok &= (chars[tam_chars-i-1]==*(char*)pila_ver_tope(paux));
	     pila_desapilar(paux);
    }
    print_test("lista_borrar_primero devuelve pi2", ok);
    pila_destruir(paux);
    paux = lista_borrar_primero(l);
    for (int i=0; i < tam_nums; i++) {
    	ok &= (nums[tam_nums-i-1]==*(int*)pila_ver_tope(paux));
	pila_desapilar(paux);
    }
    print_test("lista_borrar_primero devuelve pi1", ok);
    pila_destruir(paux);
    paux = lista_borrar_primero(l);
    for (int i=0; i < tam_bools; i++) {
    	ok &= (bools[tam_bools-i-1]==*(bool*)pila_ver_tope(paux));
	pila_desapilar(paux);
    }
    print_test("lista_borrar_primero devuelve pi3", ok);
    pila_destruir(paux);

    lista_destruir(l, NULL);

}
/*
static void prueba_lista_iterador_interno(void) {
    printf("INICIO DE PRUEBAS ITERADOR INTERNO\n");
    // bool imprimir_un_item(void *elemento, void *extra) {
    //     // Sabemos que ‘extra’ es un entero, por tanto le podemos hacer un cast.
    //     int *contador = extra;
    //     printf("%d. %s\n", ++(*contador), (char *) elemento);
    //     return true;  // seguir iterando
    // }
    bool imprimir_un_entero(void *elemento, void *extra) {
        // Sabemos que ‘extra’ es un entero, por tanto le podemos hacer un cast.
        int *contador = extra;
        printf("%d. %d\n", ++(*contador), *(int *) elemento);
        return true;  // seguir iterando
    }

    // void imprimir_iter_interno(lista_t *lista) {
    //     int num_items = 0;
    //     lista_iterar(lista, imprimir_un_item, &num_items);
    //     printf("Tengo que comprar %d ítems\n", num_items);
    // }
    void imprimir_iter_interno_numeros(lista_t *lista) {
        int num_items = 0;
        lista_iterar(lista, imprimir_un_entero, &num_items);
        printf("cantidad de elmentos en lista %d \n", num_items);
    }
    lista_t *super = lista_crear();

    lista_insertar_ultimo(super, "leche");
    lista_insertar_ultimo(super, "huevos");
    lista_insertar_ultimo(super, "pan");
    lista_insertar_ultimo(super, "mermelada");

    lista_t * nums = lista_crear();
    int n[] = {10,20,340,39};
    lista_insertar_ultimo(nums, &n[0]);
    lista_insertar_ultimo(nums, &n[1]);
    lista_insertar_ultimo(nums, &n[2]);
    lista_insertar_ultimo(nums, &n[3]);
    imprimir_iter_interno_numeros(nums);
    lista_destruir(nums, NULL);

    lista_destruir(super, NULL);

}
*/
static void prueba_lista_iterador_externo(void) {
/*
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO\n");
  lista_t * nums = lista_crear();

  int n[] = {10,20,340,39};
  // lista_insertar_ultimo(nums, &n[0]);
  // lista_insertar_ultimo(nums, &n[1]);
  // lista_insertar_ultimo(nums, &n[2]);
  // lista_insertar_ultimo(nums, &n[3]);
  lista_iter_t * iter = lista_iter_crear(nums);

  lista_iter_insertar(iter, &n[0]);
  lista_iter_insertar(iter, &n[1]);
  lista_iter_insertar(iter, &n[2]);
  lista_iter_insertar(iter, &n[3]);
  // printf("iter es %p\n", iter);
  bool ok = n[3] == *(int *)lista_iter_ver_actual(iter);
  print_test("El iter accede a primer elemento de lista ", ok);
  print_test("Lista iter NO al final, antes de ciclo ", !lista_iter_al_final(iter));
  int i = 3;
  while(!lista_iter_al_final(iter)) {
     ok = n[i] == *(int *)lista_iter_ver_actual(iter);
     print_test("El iter accede al elemento de la lista", ok);
     print_test("lista_iter_avanzar funciona ", lista_iter_avanzar(iter));
     i--;
  }
  // insertar al final
  int alfinal = 34;
  lista_iter_insertar(iter, &alfinal);
  ok = 34 == *(int *)lista_iter_ver_actual(iter);
  lista_iter_avanzar(iter);
  print_test("El iter accede al nuevo al final", ok);
  printf("Cantidad de elementos en la lista %lu", lista_largo(nums));
  // print_test("Cantidad de elementos en la lista ", 4==lista_largo(nums));
  print_test("Lista iter al final ", lista_iter_al_final(iter));
  lista_destruir(nums, NULL);
  lista_iter_destruir(iter);
  */
}

static void prueba_lista_imprimir_iter_externo(void) {
  printf("INICIO DE PRUEBAS ITERADOR EXTERNO\n");
  // printf("sizeof_size_t= %lu\n", sizeof(size_t));
  // void imprimir_iter_externo(lista_t *lista) {
  //     lista_iter_t *iter = lista_iter_crear(lista);
  //     int num_items = 0;
  //
  //     while (!lista_iter_al_final(iter)) {
  //         char *elemento = lista_iter_ver_actual(iter);
  //         printf("%d. %s\n", ++num_items, elemento);
  //
  //         lista_iter_avanzar(iter);
  //     }
  //     printf("Tengo que comprar %d ítems\n", num_items);
  //     lista_iter_destruir(iter);
  // }
  lista_t *super = lista_crear();

  // lista_insertar_ultimo(super, "leche");
  // printf("Cantidad de elemento en lista %lu\n", lista_largo(super));
  //
  // lista_insertar_ultimo(super, "huevos");
  // printf("Cantidad de elemento en lista %lu\n", lista_largo(super));
  //
  // lista_insertar_ultimo(super, "pan");
  //
  // lista_insertar_ultimo(super, "mermelada");
  lista_iter_t * iter = lista_iter_crear(super);
  int items[] = {10,20,340,39};
  lista_iter_insertar(iter, &items[0]);
  printf("Cantidad de elemento en lista %lu\n", lista_largo(super));
  lista_iter_insertar(iter, &items[1]);
  printf("Cantidad de elemento en lista %lu\n", lista_largo(super));
  lista_iter_insertar(iter, &items[2]);
  printf("Cantidad de elemento en lista %lu\n", lista_largo(super));
  lista_iter_insertar(iter, &items[3]);
  // printf("Cantidad de elemento en lista %lu\n", );
  // imprimir_iter_externo(super);
  // printf("ver list primero %d\n",*(int*)lista_ver_primero(super) );
  if (lista_esta_vacia(super)) printf("La lista esta vacia\n");

  while(!lista_iter_al_final(iter)) {
     // ok = n[i] == *(int *)lista_iter_ver_actual(iter);
     printf("%d\n",*(int*)lista_iter_ver_actual(iter));
     // print_test("El iter accede al elemento de la lista", ok);
     print_test("lista_iter_avanzar funciona ", lista_iter_avanzar(iter));
  }
  // bool son_iguales = lista_iter_largo(iter)==lista_largo(super);
  // printf("lista_largo==lista_iter_largo? %d \n",);
  lista_destruir(super, NULL);
  lista_iter_destruir(iter);
}
void pruebas_lista_estudiante() {
    prueba_lista_vacia();
    prueba_lista_ver_primero_vacia_es_invalido();
    prueba_lista_ver_ultimo_vacia_es_invalido();
    prueba_lista_insertar_primero();
    prueba_lista_borrar_vacia_la_lista();
    prueba_lista_volumen();
    prueba_lista_se_puede_insertar_null();
    prueba_lista_de_pilas();
    // prueba_lista_iterador_interno();
    prueba_lista_iterador_externo();
    prueba_lista_imprimir_iter_externo();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
