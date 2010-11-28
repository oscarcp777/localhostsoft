/*
 * Encryption.h
 *
 *  Created on: 14/11/2010
 *      Author: Santiago
 */

#ifndef ENCRYPTION_H_
#define ENCRYPTION_H_

#include <string>
#include <iostream>
using namespace std;


class Encryption {
public:
	Encryption();
	virtual ~Encryption();

	/**
	 * Metodo de encriptacion
	 *
	 * @param textToEncrypt Texto a ser encriptado
	 * @return string Texto encriptado
	 */
	virtual string encrypt(string textToEncrypt)=0;

	/**
	 * Metodo de encriptacion
	 *
	 * @param textToDecrypt Texto a ser desencriptado
	 * @return string Texto desencriptado
	 */
	virtual string decrypt(string textToDecrypt)=0;

protected:
	/**
	 * Tamaño bloque estructura a encriptar
	 */
	int blockSize;

	/**
	 * Tamaño clave (numero caracteres a encriptar/desencriptar por vez)
	 */
	int keySize;
};

#endif /* ENCRYPTION_H_ */
