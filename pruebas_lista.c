#include "lista.h"
#include "testing.h"
#include<stdio.h>

/* Pruebas para una lista vacía. */
static void prueba_lista_vacia(void) {

    printf("INICIO DE PRUEBAS CREAR LISTA VACIA\n");

    lista_t *lista = lista_crear();
    print_test("Prueba lista vacía: ", lista_esta_vacia(lista));
    lista_destruir(lista);
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
