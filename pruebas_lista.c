#include "lista.h"
#include "testing.h"
#include "pila.h"
#include<stdio.h>

// para el iterador interno
const int CANT_ITEMS = 3;
const int SUMA_ITEMS = 210;

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
    for (int i = 0; i < M; i++) {
        e[i] = i;
        ok &= lista_insertar_primero(lista, &e[i]);
    }
    print_test("Se insertaron los elementos: ", ok);

    for (int i = 0; i < M; i++) {
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

static void prueba_lista_imprimir_iter_externo(void) {
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO\n");

    lista_t *super = lista_crear();
    lista_iter_t * iter = lista_iter_crear(super);
    int items[] = {10,20,340,39};

    lista_iter_insertar(iter, &items[0]);
    if(lista_iter_insertar(iter, &items[1])) printf("\t\tinsecion oK\n");
    lista_iter_insertar(iter, &items[2]);
    lista_iter_insertar(iter, &items[3]);

    lista_destruir(super, NULL);
    lista_iter_destruir(iter);
}

// Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.
static void prueba_iter_externo_insertar_al_ser_creado(void) {
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO INSERTAR AL SER CREADO\n");

    lista_t *lista = lista_crear();
    lista_iter_t * iter = lista_iter_crear(lista);
    int items[] = {10,20,340,39};

    lista_iter_insertar(iter, &items[0]);
    bool ok = lista_iter_ver_actual(iter)==lista_ver_primero(lista);
    print_test("Insertar al ser creado inserta al principio", ok);

    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
}
// Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.
static void prueba_iter_externo_insertar_al_final(void) {
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO INSERTAR AL FINAL\n");

    lista_t *lista = lista_crear();
    lista_iter_t * iter = lista_iter_crear(lista);
    int items[] = {10,20,340,39};

    lista_iter_insertar(iter, &items[0]);
    lista_iter_insertar(iter, &items[1]);
    lista_iter_insertar(iter, &items[2]);
    bool ok = lista_iter_ver_actual(iter)==lista_ver_primero(lista);
    print_test("Insertar al ser creado inserta al principio", ok);
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    lista_iter_insertar(iter, &items[3]);
    ok = lista_iter_ver_actual(iter)==lista_ver_ultimo(lista);

    print_test("Insertar al final,", ok);
    print_test("Actual NO esta al final ", !lista_iter_al_final(iter));
    lista_iter_avanzar(iter);
    print_test("Actual es al final ", lista_iter_al_final(iter));
    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
}
// Insertar un elemento en el medio se hace en la posición correcta.
static void prueba_iter_externo_insertar_medio(void) {
  printf("INICIO DE PRUEBAS ITERADOR EXTERNO INSERTAR EN MEDIO\n");

  lista_t *lista = lista_crear();
  lista_iter_t * iter = lista_iter_crear(lista);
  int items[] = {10,20,340,39};

  lista_iter_insertar(iter, &items[0]);
  lista_iter_insertar(iter, &items[1]);
  lista_iter_insertar(iter, &items[2]);

  // voy a la segunda posicion
  lista_iter_avanzar(iter);
  lista_iter_insertar(iter, &items[3]);
  bool ok = items[2]==*(int*)lista_borrar_primero(lista);
  print_test("El primero sigue siendo el primero ",ok);
   ok = lista_ver_primero(lista)== &items[3];
  print_test("se inserto en la posicion correcta ",ok);

  lista_destruir(lista, NULL);
  lista_iter_destruir(iter);
}
// Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista.
static void prueba_iter_externo_borrar_al_crear(void) {
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO BORRAR AL CREAR\n");

    lista_t *lista = lista_crear();
    lista_iter_t * iter = lista_iter_crear(lista);
    int items[] = {10,20,340,39};

    lista_iter_insertar(iter, &items[0]);
    lista_iter_insertar(iter, &items[1]);
    lista_iter_insertar(iter, &items[2]);
    lista_iter_insertar(iter, &items[3]);
    bool ok = lista_iter_ver_actual(iter)==lista_ver_primero(lista);
    print_test("Insertar al ser creado inserta al principio", ok);
    lista_iter_borrar(iter);
    ok = *(int*)lista_ver_primero(lista)==items[2];
    print_test("Borrar al principio,", ok);

    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
}
// Remover el último elemento con el iterador cambia el último de la lista.
static void prueba_iter_externo_borrar_al_final(void) {
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO BORRAR AL FINAL\n");

    lista_t *lista = lista_crear();
    lista_iter_t * iter = lista_iter_crear(lista);
    int items[] = {10,20,340,39};

    lista_iter_insertar(iter, &items[0]);
    lista_iter_insertar(iter, &items[1]);
    lista_iter_insertar(iter, &items[2]);
    lista_iter_insertar(iter, &items[3]);
    bool ok = lista_iter_ver_actual(iter)==lista_ver_primero(lista);
    print_test("Insertar al ser creado inserta al principio", ok);
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    ok = lista_iter_ver_actual(iter)==lista_ver_ultimo(lista);
    print_test("Insertar al final,", ok);

    int * borrado = (int*)lista_iter_borrar(iter);
    ok = *borrado == items[0];
    print_test("devuelve el del final,", ok);
    ok = *(int*)lista_ver_ultimo(lista)==items[1];
    print_test("Borrar al final,", ok);

    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
}
// Verificar que al remover un elemento del medio, este no está.
static void prueba_iter_externo_borrar_medio(void) {
  printf("INICIO DE PRUEBAS ITERADOR EXTERNO BORRAR EN MEDIO\n");

  lista_t *lista = lista_crear();
  lista_iter_t * iter = lista_iter_crear(lista);
  int items[] = {10,20,340,39};

  lista_iter_insertar(iter, &items[0]);//pos 3
  lista_iter_insertar(iter, &items[1]);//pos 2
  lista_iter_insertar(iter, &items[2]);//pos 1
  lista_iter_insertar(iter, &items[3]);//pos 0

  // voy a la segunda posicion, pos 1
  lista_iter_avanzar(iter);
  lista_iter_borrar(iter);

  bool ok = *(int*)lista_iter_ver_actual(iter) == items[1];
  lista_borrar_primero(lista);
  ok &= *(int*)lista_ver_primero(lista) == items[1];
  print_test("actual apunta al elemento correcto ",ok);

  lista_destruir(lista, NULL);
  lista_iter_destruir(iter);
}
static void prueba_iter_externo_borrar(void) {
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO BORRAR\n");

    lista_t *lista = lista_crear();
    lista_iter_t * iter = lista_iter_crear(lista);
    int items[] = {10,20,340};
    lista_iter_insertar(iter, &items[0]);
    lista_iter_insertar(iter, &items[1]);
    lista_iter_insertar(iter, &items[2]);
    lista_iter_avanzar(iter);
    lista_iter_borrar(iter);
    lista_iter_borrar(iter);
    print_test("lista al final " ,lista_iter_al_final(iter));
    print_test("la lista no esta vacia ", !lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
}
//  funciones para probar el iterador interno
// funcion con corte
bool imprimir_hasta_tres_items(void *elemento, void *extra) {
    int *contador = extra;
    printf("%d. %d\n", ++(*contador), *(int *) elemento);
    if ( *contador == CANT_ITEMS) return false;
    return true;  // seguir iterando
}
// funcion sin corte
bool sumar_los_items(void *elemento, void *extra) {
    int *sumatoria = extra;
    *sumatoria += *(int *)elemento;
    return true;  // seguir iterando
}
bool imprimir_iter_interno(lista_t *lista) {
    int num_items = 0;
    lista_iterar(lista, imprimir_hasta_tres_items, &num_items);
    print_test("se imprimieron 3 items ", num_items==CANT_ITEMS);
    return num_items == CANT_ITEMS;
}
bool imprimir_suma(lista_t *lista) {
    int suma = 0;
    lista_iterar(lista, sumar_los_items, &suma);
    // printf("suma=%d\n", suma);
    print_test("Se sumaron los item ", suma == SUMA_ITEMS);
    return suma == SUMA_ITEMS;
}
static void prueba_iter_interno(void) {
    printf("INICIO DE PRUEBAS ITERADOR INTERNO\n");

    lista_t *lista = lista_crear();
    int items[] = {10, 20, 30, 40, 50, 60};

    lista_insertar_ultimo(lista, &items[0]);
    lista_insertar_ultimo(lista, &items[1]);
    lista_insertar_ultimo(lista, &items[2]);
    lista_insertar_ultimo(lista, &items[3]);
    lista_insertar_ultimo(lista, &items[4]);
    lista_insertar_ultimo(lista, &items[5]);


    print_test("iterador interno sin corte", imprimir_suma(lista));
    print_test("iterador interno con corte", imprimir_iter_interno(lista));
    print_test("Aplicar dos veces el iterador", imprimir_iter_interno(lista));
    lista_destruir(lista, NULL);
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
    prueba_lista_imprimir_iter_externo();
    prueba_iter_externo_insertar_al_ser_creado();
    prueba_iter_externo_insertar_al_final();
    prueba_iter_externo_borrar_al_final();
    prueba_iter_externo_borrar_al_crear();
    prueba_iter_externo_insertar_medio();
    prueba_iter_externo_borrar_medio();
    prueba_iter_externo_borrar();
    prueba_iter_interno();
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
