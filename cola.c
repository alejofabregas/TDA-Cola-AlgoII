#include "cola.h"

#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct nodo {
	void* dato;
	struct nodo* prox;
} nodo_t;

typedef struct cola {
	nodo_t* prim;
	nodo_t* ult;
} cola_t;


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* nodo_crear(void* valor) {
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) {return NULL;}
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}

void nodo_destruir(nodo_t* nodo, cola_t* cola) {
	cola->prim = nodo->prox;
	free(nodo);
}


/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t *cola_crear(void) {
	cola_t* cola = malloc(sizeof(cola_t));
	if (!cola) {return NULL;}
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}


void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
	if (!destruir_dato) {
		while (!cola_esta_vacia(cola)) {
			nodo_destruir(cola->prim, cola);
		}
	}
	else {
		while (!cola_esta_vacia(cola)) {
			destruir_dato(cola->prim->dato);
			nodo_destruir(cola->prim, cola);
		}
	}
	free(cola);
}


bool cola_esta_vacia(const cola_t *cola) {
	return !cola->prim;
}


bool cola_encolar(cola_t *cola, void *valor) {
	nodo_t* nodo = nodo_crear(valor);
	if (!nodo) {return false;}
	if (!cola->prim) {cola->prim = nodo;}
	if (!cola->ult) {cola->ult = nodo;}
	else {
		cola->ult->prox = nodo;
		cola->ult = nodo;
	}
	return true;
}


void *cola_ver_primero(const cola_t *cola) {
	if (cola_esta_vacia(cola)) {return NULL;}
	return cola->prim->dato;
}


void *cola_desencolar(cola_t *cola) {
	if (cola_esta_vacia(cola)) {return NULL;}
	bool primero_es_ultimo = false;
	if (cola->prim == cola->ult) {primero_es_ultimo = true;}
	void* valor = cola->prim->dato;
	nodo_destruir(cola->prim, cola);
	if (primero_es_ultimo) {cola->ult = NULL;}
	return valor;
}

