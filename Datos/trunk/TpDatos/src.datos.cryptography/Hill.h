/*
 * Hill.h
 *
 *  Created on: 14/11/2010
 *      Author: Santiago
 */

#ifndef HILL_H_
#define HILL_H_

#include "Encryption.h"
#include "../src.datos.utils/Define.h"

class Hill: public Encryption {
public:
	/**
	 * Construye encriptador con un N y clave determinados
	 *
	 * @param keySize  Tamaño clave (numero caracteres a encriptar/desencriptar por vez)
	 * @param clave Clave utilizada para armar la matriz clave correspondiente a este metodo
	 */
	Hill(const int keySize, string clave);
	virtual ~Hill();

	/**
	 * Metodo de encriptacion
	 *
	 * @param textToEncrypt Texto a ser encriptado
	 * @return string Texto encriptado
	 */
	virtual string encrypt(string textToEncrypt);

	/**
	 * Metodo de encriptacion
	 *
	 * @param textToDecrypt Texto a ser desencriptado
	 * @return string Texto desencriptado
	 */
	virtual string decrypt(string textToDecrypt);

	/**
	 * Muestra la matriz clave actual
	 */
	void printKeyMatrix();

	/**
	 * Muestra la matriz clave inversa actual
	 */
	void printKeyInvertedMatrix();



private:
	/**
	 * Matriz clave de este metodo (para encriptar), su determinante mod 128 tiene que ser igual a 1
	 */
	int** keyMatrix;

	/**
	 * Matriz clave inversa de este metodo (para desencriptar)
	 */
	int** keyInvertedMatrix;

	/**
	 * Multiplica un vector por una matriz
	 *
	 * @param vector Vector dado para realizar el producto
	 * @param matrix Matriz dada para realizar el producto
	 * @return int* Vector resultante del producto
	 */
	int* productVectorPerMatrix(int* vector, int** matrix);

	/**
	 * Aplica mod 128 a todos los elementos del vector dado
	 *
	 * @param vector Vector dado para realizar la operacion
	 */
	void mod128(int* vector);

	/**
	 * Metodo que dado un mensaje y una matriz devuelve su conversion (tanto para encriptar como para desencriptar)
	 *
	 * @param text Mensaje a traducir
	 * @param matrix Matriz a usar para la traduccion
	 * @return devuelve el mensaje convertido (encriptado o desencriptado)
	 */
	string translate(string text, int** matrix);

	//BORRAR
	void testMatrix2x2();
	void testInvertedMatrix2x2();

};

#endif /* HILL_H_ */
