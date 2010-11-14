/*
 * Hill.cpp
 *
 *  Created on: 14/11/2010
 *      Author: Santiago
 */

#include "Hill.h"
using namespace std;

Hill::Hill(const int keySize, string clave) {
	this->keySize = keySize;
	this->keyMatrix = new int *[keySize];
	for (int k=0; k<keySize; k++)
		this->keyMatrix[k] = new int[keySize];

	this->keyInvertedMatrix = new int *[keySize];
	for (int k=0; k<keySize; k++)
		this->keyInvertedMatrix[k] = new int[keySize];

	//NOTA El det(keyMatrix) mod 128 = 1 para que funcione el metodo
	// Armado matriz clave
	// makeKey();//Falta implementar, aca van las funciones hash y el calculo
	this->testMatrix2x2();

	// Armado matriz clave inversa
	// makeKeyInverted();//aca se calcula la inversa con respecto a la anterior
	this->testInvertedMatrix2x2();

}

void Hill::testMatrix2x2(){
	//NOTA ver que 4x65 - 3 = 257, y 257 mod 128 = 1, verifica condicion
	this->keyMatrix[0][0] = 2;
	this->keyMatrix[0][1] = 1;
	this->keyMatrix[1][0] = 1;
	this->keyMatrix[1][1] = 65;
}

void Hill::testInvertedMatrix2x2(){
	this->keyInvertedMatrix[0][0] = 65;
	this->keyInvertedMatrix[0][1] = -1;
	this->keyInvertedMatrix[1][0] = -1;
	this->keyInvertedMatrix[1][1] = 2;
}

Hill::~Hill() {
	for (int k=0; k<this->keySize; k++)
			delete []this->keyMatrix[k];
	delete []this->keyMatrix;
	for (int k=0; k<this->keySize; k++)
			delete []this->keyInvertedMatrix[k];
	delete []this->keyInvertedMatrix;

}

string Hill::encrypt(string textToEncrypt){
	return this->translate(textToEncrypt, this->keyMatrix);
}

string Hill::decrypt(string textToDecrypt){
	return this->translate(textToDecrypt, this->keyInvertedMatrix);
}


void Hill::printKeyMatrix(){
	string matrix;
	cout << "Matriz clave: " << endl;
	for (int i = 0; i < this->keySize; i++) {
		for (int j = 0; j < this->keySize; j++) {
			cout << this->keyMatrix[i][j]  <<" ";
		}
		cout << endl;
	}
}

void Hill::printKeyInvertedMatrix(){
	string matrix;
	cout << "Matriz clave inversa: " << endl;
	for (int i = 0; i < this->keySize; i++) {
		for (int j = 0; j < this->keySize; j++) {
			cout << this->keyInvertedMatrix[i][j]  <<" ";
		}
		cout << endl;
	}
}

string Hill::translate(string text, int** matrix){

	string result;
	unsigned int n = 0;
	int j = 0;
	int* textPart = new int[this->keySize];
	char letter;

	//FIX-ME este codigo comentado es para solucionar si el mensaje no es multiplo de el tamaño clave
	//	int mod = text.length() % set;
	//	if (mod!=0){
	//		mod = set - mod;
	//		for (int i=0; i<mod; i++){
	//			text = text.concat("x");
	//		}
	//	}
	while (n < text.length()) {
		char c = text[n++];
		if (DEBUG) cout << "letra "<<n<<": "<<int(c)<<endl;
		textPart[j++] = int(c);
		if (j >= this->keySize) {

			int* multiplyResult = productVectorPerMatrix(textPart, matrix);
			mod128(multiplyResult);

			for (int i = 0; i < this->keySize; i++) {
				letter = char(multiplyResult[i]);
				result.append(&letter,sizeof(char));
			}
			j = 0;
			delete []multiplyResult;
		}
	}
	delete []textPart;

	return result;

}



int *Hill::productVectorPerMatrix(int *vector, int** matrix){

	int* result = new int[this->keySize];
	int i, j;

	for (i = 0; i < this->keySize; i++) {
		result[i] = 0;
		for (j = 0; j < this->keySize; j++)
			result[i] += matrix[i][j] * vector[j];
		if (DEBUG) cout << " en product: "<<result[i]<<endl;
	}
	return result;

}

void Hill::mod128(int *vector){

	for (int i = 0; i < this->keySize; i++) {
		int aux = vector[i] % 128;
		if (aux < 0) aux = aux + 128;
		vector[i] = aux;
		if (DEBUG) cout <<"en MOD:"<< vector[i]<<endl;
	}

}






