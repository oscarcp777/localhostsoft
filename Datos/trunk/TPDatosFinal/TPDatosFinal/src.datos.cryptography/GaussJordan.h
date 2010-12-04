/*
 * GaussJordan.h
 *
 *  Created on: 18/11/2010
 *      Author: richy
 */

#ifndef GAUSSJORDAN_H_
#define GAUSSJORDAN_H_
#include <iostream>


class GaussJordan {
public:
	GaussJordan(int n,long double** matriz, long double** inversa);
	virtual ~GaussJordan();
	void hallar_inversa(long double num);

private:
	int N;
	long double** matriz;
	long double** identidad;
	void escalonar_matriz(void);
	void permutar_filas(int fila1, int fila2);
	void multip_fila(int fila,long double factor);
	void sumar_fila_multip(int fila1,int fila2, long double factor);
	void ceros_abajo(int fila_pivote, int columna_pivote);
	void ceros_arriba(int fila_pivote, int columna_pivote);
	void generar_matriz_identidad(long double num);
	int modL(long double value);
};

#endif /* GAUSSJORDAN_H_ */
