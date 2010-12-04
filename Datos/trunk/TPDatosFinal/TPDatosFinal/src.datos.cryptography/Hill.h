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
#include "../src.datos.storage/Buffer.h"
#include "GaussJordan.h"


class Hill: public Encryption {

public:

	/**
	 * Singleton, metodo devuelve instancia unica de la clase
	 */
	static Hill *getInstance();

	/**
	 * Metodo que debe ser llamado luego de pedir por primera vez dicha instancia, setea tamaño y clave necesarias
	 * para la encriptacion
	 *
	 * @param keySize  Tamaño clave (numero caracteres a encriptar/desencriptar por vez)
	 * @param clave Clave utilizada para armar la matriz clave correspondiente a este metodo
	 */
	void initialize(const int keySize, string clave);

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
	 * Metodo de encriptacion
	 *
	 * @param textToEncrypt Buffer a ser encriptado
	 * @return Buffer Buffer encriptado
	 */
	Buffer* encrypt(char* messageToEncrypt,int size);

	/**
	 * Metodo de encriptacion
	 *
	 * @param textToDecrypt Texto a ser desencriptado
	 * @return string Texto desencriptado
	 */
	Buffer* decrypt(char* messageToDecrypt,int size);

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
	 * Instancia singleton de la clase
	 */
	static Hill *instance;

	/**
	 * Constructor privado (singleton) de la clase
	 */
	Hill();

	/**
	 * Matriz clave de este metodo (para encriptar), su determinante mod 128 tiene que ser igual a 1
	 */
	double** keyMatrix;

	/**
	 * Matriz clave inversa de este metodo (para desencriptar)
	 */
	double** keyInvertedMatrix;

	/**
	 * Multiplica un vector por una matriz
	 *
	 * @param vector Vector dado para realizar el producto
	 * @param matrix Matriz dada para realizar el producto
	 * @return double* Vector resultante del producto
	 */
	double* productVectorPerMatrix(double* vector, double** matrix);

	/**
	 * Aplica mod 128 a todos los elementos del vector dado
	 *
	 * @param vector Vector dado para realizar la operacion
	 */
	void modL(double* vector);
	int modL(long int value);
	int inverseModL(int num);
	int H1(string word);
	int H2(string word);
	long double buildKeyMatrix(string word);
	void buildKeyInverted(long double num);

	/**
	 * Metodo que dado un mensaje y una matriz devuelve su conversion (tanto para encriptar como para desencriptar)
	 *
	 * @param text Mensaje a traducir
	 * @param matrix Matriz a usar para la traduccion
	 * @return string Devuelve el mensaje convertido (encriptado o desencriptado)
	 */
	string translate(string text, double** matrix);
	Buffer* translate(char* messageOriginal,int sizeText, double** matrix);

	//BORRAR
	void testMatrix2x2();
	void testInvertedMatrix2x2();

};



#endif /* HILL_H_ */
