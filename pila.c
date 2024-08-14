#include "pila.h"

#include <stdlib.h>

#define TAM_MINIMO 10
#define CANT_INICIAL 0
#define FACTOR_REDIMENSION 2
#define FACTOR_CANT_MIN 4


/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
 
bool pila_redimensionar(pila_t *pila, size_t tam) {
	void **datos_nuevo = realloc(pila->datos, tam * sizeof(void*));
	if (datos_nuevo == NULL) {return false;}
	pila->datos = datos_nuevo;
	pila->capacidad = tam;
	return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void) {
	pila_t *pila = malloc(sizeof(pila_t));
	if (pila == NULL) {
		return NULL;
	}
	pila->datos = malloc(TAM_MINIMO * sizeof(void*));
	if (pila->datos == NULL) {
		free(pila);
		return NULL;
	}
	pila->cantidad = CANT_INICIAL;
	pila->capacidad = TAM_MINIMO;
	return pila;
}
 
void pila_destruir(pila_t *pila) {
	free(pila->datos);
	free(pila);
}
 
bool pila_esta_vacia(const pila_t *pila) {
	return pila->cantidad == 0;
}
 
bool pila_apilar(pila_t *pila, void *valor) {
	if (pila->cantidad == pila->capacidad) {
		if (!pila_redimensionar(pila, pila->capacidad * FACTOR_REDIMENSION)) {return false;}
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}
 
void *pila_ver_tope(const pila_t *pila) {
	if (pila_esta_vacia(pila)) {return NULL;}
	return pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila) {
	if (pila_esta_vacia(pila)) {return NULL;}
	pila->cantidad--;
	if (pila->cantidad * FACTOR_CANT_MIN <= pila->capacidad && pila->capacidad / FACTOR_REDIMENSION >= TAM_MINIMO) {
		pila_redimensionar(pila, pila->capacidad / FACTOR_REDIMENSION);
	}
	return pila->datos[pila->cantidad];
}
