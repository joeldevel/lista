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
    //pila_destruir(paux);
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
/* Pruebas para tope lista vacía es inválido. */
// static void prueba_lista_ver_tope_creada_es_invalido(void) {
//
//     printf("INICIO DE PRUEBAS VER TOPE EN LISTA VACÍA ES INVÁLIDO\n");
//
//     lista_t *lista = lista_crear();
//     print_test("Prueba lista ver tope en lista recién creada es inválido: ", lista_ver_tope(lista)==NULL);
//     lista_destruir(lista);
// }

/* Pruebas para alistar un elemento. */
// static void prueba_alistar_un_elemento(void) {
//
//     printf("INICIO DE PRUEBAS ALISTAR UN ELEMENTO\n");
//
//     lista_t *lista = lista_crear();
//
//     char elemento = 'A';
//
//     bool ok = lista_alistar(lista, &elemento);
//     print_test("Se puede alistar un elemento", ok);
//
//     int tope = *(char*)lista_ver_tope(lista);
//     printf("lo que vuelve de lista_ver_tope= %c\n", tope );
//
//     lista_destruir(lista);
// }

/* Pruebas para alistar pocos elementos. */
// static void prueba_alistar_pocos_elementos(void) {
//
//     printf("INICIO DE PRUEBAS ALISTAR POCOS ELEMENTOS\n");
//
//     lista_t *lista = lista_crear();
//     char elementos[] = {'A','b','c', 'F','X'};
//     int tam = 5;
//     bool ok = true;
//     for(int i=0; i < tam; i++) {
//         lista_alistar(lista, &elementos[i]);
//         ok &= (elementos[i]==*(char*)lista_ver_tope(lista));
//     }
//
//     print_test("se pudieron alistar todos los elementos", ok);
//
//     lista_destruir(lista);
// }

/*Se pueden desalistar los elementos y se cumple FIFO*/
// static void prueba_lista_desalistar(void) {
//
//     printf("INICIO DE PRUEBAS DESALISTAR\n");
//
//     lista_t *lista = lista_crear();
//     int valores[] = {11,22,33,44,55,66,77,88,99};
//     int tam = 9;
//     for (int i = 0; i < tam; i++) {
//         lista_alistar(lista, &valores[i]);
//     }
//
//     bool ok = true;
//     for (int i = 0; i < tam; i++) {
//       ok &= (valores[tam-i-1]==*(int*)lista_desalistar(lista));
//     }
//     print_test("se pudieron desalistar todos los elementos", ok);
//
//     lista_destruir(lista);
// }

/* Pruebas de la lista al trabajar con un volumen grande de elementos */
// static void prueba_lista_volumen(void) {
//
//     printf("INICIO DE PRUEBAS VOLUMEN\n");
//
//     lista_t *lista = lista_crear();
//
//     int tam = 1000;
//     int el[tam];
//     for (int i = 0; i< tam; i++) {
//       el[i] = i;
//     }
//     bool ok = true;
//     for (int i = 0; i < tam; i++) {
//         // Si algun elemento no se pudo guardar correctamente, ok sera false
//         ok &= lista_alistar(lista, &el[i]);
//     }
//     print_test("se pudieron alistar todos los elementos", ok);
//
//     // desalistarlos
//     ok = true;
//     for (int i = 0; i < tam; i++) {
//         ok &= (tam-i-1==*(int*)lista_desalistar(lista));
//     }
//     print_test("se pudieron desalistar todos los elementos", ok);
//
//     lista_destruir(lista);
// }
// static void prueba_lista_desalistar_vacia_es_invalido(void) {
//
//     printf("INICIO DE PRUEBAS DESALISTAR LISTA VACÍA ES INVÁLIDO\n");
//
//     lista_t *lista = lista_crear();
//     print_test("Prueba lista vacía: ", lista_esta_vacia(lista));
//     print_test("Prueba desalistar vacía es inválido", lista_desalistar(lista)==NULL);
//     lista_destruir(lista);
// }
//
// static void prueba_lista_desalistar_despues_de_alistar_y_desalistar_es_invalido(void) {
//
//     printf("INICIO DE PRUEBAS DESALISTAR DESPUES DE DESALISTAR INVÁLIDO\n");
//
//     lista_t *lista = lista_crear();
//     int valores[] = {11,22,33,44,55,66,77,88,99};
//     int cant_valores = 9;
//     for(int i = 0; i< cant_valores; i++) {
//         lista_alistar(lista, &valores[i]);
//     }
//     for( int i = 0; i< cant_valores;i++) {
//         lista_desalistar(lista);
//     }
//     print_test("Prueba desalistar despues de alistar y vaciar es inválido", lista_desalistar(lista)==NULL);
//
//     lista_destruir(lista);
// }
//
//
// static void prueba_lista_ver_tope_despues_de_alistar_y_desalistar_es_invalido(void) {
//
//     printf("INICIO DE PRUEBAS VER TOPE DESPUES DE DESALISTAR INVÁLIDO\n");
//
//     lista_t *lista = lista_crear();
//     int valores[] = {11,22,33,44,55,66,77,88,99};
//     int cant_valores = 9;
//     for(int i = 0; i< cant_valores; i++) {
//       lista_alistar(lista, &valores[i]);
//     }
//     for( int i = 0; i< cant_valores;i++) {
//         lista_desalistar(lista);
//     }
//     print_test("Prueba ver tope despues de alistar y vaciar es invalido", lista_desalistar(lista)==NULL);
//
//     lista_destruir(lista);
// }

/* Se puede alistar NULL */
// static void prueba_lista_alistar_null() {
//
//     printf("INICIO DE PRUEBAS ALISTAR NULL ES VÁLIDO\n");
//
//     lista_t *lista = lista_crear();
//     print_test("Prueba se puede alistar NULL", lista_alistar(lista, NULL));
//     lista_destruir(lista);
// }

void pruebas_lista_estudiante() {
    prueba_lista_vacia();
    prueba_lista_ver_primero_vacia_es_invalido();
    prueba_lista_ver_ultimo_vacia_es_invalido();
    prueba_lista_insertar_primero();
    prueba_lista_borrar_vacia_la_lista();
    prueba_lista_volumen();
    prueba_lista_se_puede_insertar_null();
    prueba_lista_de_pilas();
    // prueba_alistar_un_elemento();
    // prueba_lista_ver_tope_creada_es_invalido();
    // prueba_alistar_pocos_elementos();
    // prueba_lista_desalistar();
    // prueba_lista_volumen();
    // prueba_lista_desalistar_vacia_es_invalido();
    // prueba_lista_desalistar_despues_de_alistar_y_desalistar_es_invalido();
    // prueba_lista_ver_tope_despues_de_alistar_y_desalistar_es_invalido();
    // prueba_lista_alistar_null();
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
