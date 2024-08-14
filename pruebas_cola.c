#include "cola.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include "pila.h"

#define CANT_ELEM_PRUEBA 10000


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

void pila_destruir_wrapper(void* pila) {
	pila_destruir(pila);
}


/* ******************************************************************
 *                    PRUEBAS DE LA COLA
 * *****************************************************************/

void prueba_cola_vacia(void) {
	printf("--PRUEBA CON COLA VACIA--\n");
	cola_t* cola = cola_crear();
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	cola_destruir(cola, NULL);
}

void prueba_crear_destruir_cola(void) {
	printf("\n--PRUEBA DE CREAR Y DESTRUIR UNA COLA--\n");
	cola_t* cola = cola_crear();
	print_test("La cola se creo correctamente", cola != NULL);
	cola_destruir(cola, NULL);
	print_test("La cola se destruyo correctamente", true);
}

void prueba_encolar_desencolar(void) {
	printf("\n--PRUEBAS DE ENCOLAR Y DESENCOLAR DOS ELEMENTOS--\n");
	cola_t* cola = cola_crear();
	int uno = 1;
	int dos = 2;
	print_test("Encolo el 1", cola_encolar(cola, &uno));
	print_test("El primero es 1", cola_ver_primero(cola) == &uno);
	print_test("Me fijo si esta vacia", !cola_esta_vacia(cola));
	print_test("Encolo el 2", cola_encolar(cola, &dos));
	print_test("El primero es 1 todavia", cola_ver_primero(cola) == &uno);
	print_test("Me fijo si esta vacia", !cola_esta_vacia(cola));
	print_test("Desencolo el 1", cola_desencolar(cola) == &uno);
	print_test("El primero es 2", cola_ver_primero(cola) == &dos);
	print_test("Desencolo el 2", cola_desencolar(cola) == &dos);
	print_test("Me fijo si esta vacia", cola_esta_vacia(cola)); // Caso borde: desencole el elemento que era el primero y el ultimo a la vez
	print_test("Esta vacia, pero desencolo igual", cola_desencolar(cola) == NULL);
	print_test("Me fijo si esta vacia", cola_esta_vacia(cola));
	print_test("Encolo el 1 de nuevo", cola_encolar(cola, &uno));
	print_test("Ahora no esta vacia", cola_esta_vacia(cola) == false);
	print_test("Desencolo el 1", cola_desencolar(cola) == &uno);
	print_test("Ahora esta vacia", cola_esta_vacia(cola) == true);
	cola_destruir(cola, NULL);
}

void prueba_volumen(void) {
	printf("\n--PRUEBA DE VOLUMEN: SE ENCOLAN 10000 ELEMENTOS Y SE DESENCOLA HASTA QUE LA COLA ESTA VACIA--\n");
	cola_t* cola = cola_crear();
	int elem_prueba[CANT_ELEM_PRUEBA];
	bool encolar_ok = true;
	bool desencolar_ok = true;
	for (int i = 0; i < CANT_ELEM_PRUEBA; i++) {
		elem_prueba[i] = i;
		if (!cola_encolar(cola, &elem_prueba[i])) {encolar_ok = false;}
	}
	print_test("Encolar volumen de elementos es correcto", encolar_ok);
	for (int i = 0; i < CANT_ELEM_PRUEBA; i++) {
		if (cola_desencolar(cola) != &elem_prueba[i]) {desencolar_ok = false;}
	}
	print_test("Desencolar volumen de elementos es correcto", desencolar_ok);
	print_test("La cola esta vacia luego de la prueba de volumen", cola_esta_vacia(cola));
	print_test("Desencolar la cola vacia devuelve null", cola_desencolar(cola) == NULL);
	print_test("El primero de la cola vacia es null", cola_ver_primero(cola) == NULL);
	cola_destruir(cola, NULL);
}

void prueba_encolar_null(void) {
	printf("\n--PRUEBA PARA VER SI PUEDO ENCOLAR NULL--\n");
	cola_t* cola = cola_crear();
	print_test("Primer intento de encolar null es valido", cola_encolar(cola, NULL));
	print_test("Segundo intento de encolar null es valido", cola_encolar(cola, NULL));
	print_test("Tercer intento de encolar null es valido", cola_encolar(cola, NULL));
	print_test("El primero de la cola es null", cola_ver_primero(cola) == NULL);
	print_test("Primer intento de desencolar null devuelve null", cola_desencolar(cola) == NULL);
	print_test("Segundo intento de desencolar null devuelve null", cola_desencolar(cola) == NULL);
	print_test("Tercer intento de desencolar null devuelve null", cola_desencolar(cola) == NULL);
	print_test("La cola quedo vacia", cola_esta_vacia(cola));
	cola_destruir(cola, NULL);
}

void prueba_cola_vaciada(void) {
	printf("\n--PRUEBAS PARA VER SI UNA COLA VACIADA ES IGUAL A UNA RECIEN CREADA--\n");
	cola_t* cola = cola_crear();
	int uno = 1;
	int dos = 2;
	cola_encolar(cola, &uno);
	cola_encolar(cola, &dos);
	cola_encolar(cola, &uno);
	cola_desencolar(cola);
	cola_desencolar(cola);
	cola_desencolar(cola);
	print_test("La cola vaciada esta vacia", cola_esta_vacia(cola));
	print_test("Desencolar la cola vaciada devuelve null", cola_desencolar(cola) == NULL);
	print_test("El primero de la cola vaciada es null", cola_ver_primero(cola) == NULL);
	cola_destruir(cola, NULL);
}

void prueba_cola_recien_creada(void) {
	printf("\n--PRUEBAS DE DESENCOLAR Y VER PRIMERO DE UNA COLA RECIEN CREADA--\n");
	cola_t* cola = cola_crear();
	print_test("Desencolar una cola recien creada devuelve null", cola_desencolar(cola) == NULL);
	print_test("El primero de una cola recien creada es null", cola_ver_primero(cola) == NULL);
	cola_destruir(cola, NULL);
}

void prueba_recien_creada_esta_vacia(void){
	printf("\n--PRUEBA PARA VER SI UNA COLA RECIEN CREADA ESTA VACIA--\n");
	cola_t* cola = cola_crear();
	print_test("Una cola recien creada esta vacia", cola_esta_vacia(cola));
	cola_destruir(cola, NULL);
}

void prueba_encolar_desencolar_hasta_vacia(void) {
	printf("\n--PRUEBAS DE DESENCOLAR Y VER PRIMERO DE UNA COLA ENCOLADA Y DESENCOLADA HASTA ESTAR VACIA--\n");
	cola_t* cola = cola_crear();
	int uno = 1;
	int dos = 2;
	int tres = 3;
	cola_encolar(cola, &uno);
	cola_encolar(cola, &dos);
	cola_encolar(cola, &tres);
	cola_desencolar(cola);
	cola_desencolar(cola);
	cola_desencolar(cola);
	print_test("Desencolar la cola vacia devuelve null", cola_desencolar(cola) == NULL);
	print_test("El primero de una cola vacia es null", cola_ver_primero(cola) == NULL);
	cola_destruir(cola, NULL);
}

void prueba_destruir_cola_punteros(void) {
	printf("\n--PRUEBA DE DESTRUIR UNA COLA DE PUNTEROS A MEMORIA DINAMICA--\n");
	cola_t* cola = cola_crear();
	int* punt1 = malloc(sizeof(int));
	int* punt2 = malloc(sizeof(int));
	int* punt3 = malloc(sizeof(int));
	print_test("Encolo el puntero a entero 1", cola_encolar(cola, punt1));
	print_test("Encolo el puntero a entero 2", cola_encolar(cola, punt2));
	print_test("Encolo el puntero a entero 3", cola_encolar(cola, punt3));
	cola_destruir(cola, free);
	print_test("La cola de punteros a enteros se destruyo correctamente", true);
}

void prueba_destuir_cola_pilas(void) {
	printf("\n--PRUEBA DE DESTRUIR UNA COLA DE PILAS--\n");
	cola_t* cola = cola_crear();
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* pila3 = pila_crear();
	print_test("Encolo la pila 1", cola_encolar(cola, pila1));
	print_test("Encolo la pila 2", cola_encolar(cola, pila2));
	print_test("Encolo la pila 3", cola_encolar(cola, pila3));
	cola_destruir(cola, pila_destruir_wrapper);
	print_test("La cola de pilas se destruyo correctamente", true);
}


void pruebas_cola_estudiante() {
	prueba_cola_vacia();
	prueba_crear_destruir_cola();
	prueba_encolar_desencolar();
	prueba_volumen();
	prueba_encolar_null();
	prueba_cola_vaciada();
	prueba_cola_recien_creada();
	prueba_recien_creada_esta_vacia();
	prueba_encolar_desencolar_hasta_vacia();
	prueba_destruir_cola_punteros();
	prueba_destuir_cola_pilas();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
