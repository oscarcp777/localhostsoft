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
	this->keyMatrix = new double *[keySize];
	for (int k=0; k<keySize; k++)
		this->keyMatrix[k] = new double[keySize];

	this->keyInvertedMatrix = new double *[keySize];
	for (int k=0; k<keySize; k++)
		this->keyInvertedMatrix[k] = new double[keySize];

	//NOTA El det(keyMatrix) mod 128 = 1 para que funcione el metodo

	// Armado matriz clave
	//this->buildKeyMatrix(clave);
	this->testMatrix2x2();

	// Armado matriz clave inversa
	this->buildKeyInverted();


	//this->buildKeyMatrix(clave); //TODO CAMBIAR......( el metodo hallar_inversa me modifica  la KeyMatrix, por eso la genero de nuevo, seria mejor hacer un memcpy o algo asi)
	this->testMatrix2x2();
}
void Hill::buildKeyInverted(){
	GaussJordan* gaussJordan = new GaussJordan(this->keySize, this->keyMatrix, this->keyInvertedMatrix);
	gaussJordan->hallar_inversa();
	delete gaussJordan;
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

string Hill::translate(string text, double** matrix){

	string result;
	unsigned int n = 0;
	int j = 0;
	double* textPart = new double[this->keySize];
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

			double* multiplyResult = productVectorPerMatrix(textPart, matrix);
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



double* Hill::productVectorPerMatrix(double *vector, double** matrix){

	double* result = new double[this->keySize];
	int i, j;

	for (i = 0; i < this->keySize; i++) {
		result[i] = 0;
		for (j = 0; j < this->keySize; j++)
			result[i] += matrix[i][j] * vector[j];
		if (DEBUG) cout << " en product: "<<result[i]<<endl;
	}
	return result;

}

void Hill::mod128(double *vector){

	for (int i = 0; i < this->keySize; i++) {
		int aux = (int)vector[i] % 128;
		if (aux < 0) aux = aux + 128;
		vector[i] = aux;
		if (DEBUG) cout <<"en MOD:"<< vector[i]<<endl;
	}

}

int Hill::modL(int value){
	int aux = value % CONST_L;
	if (aux < 0)
		aux = aux + CONST_L;
	return aux;
}

int Hill::H1(string word){
	int aux = this->modL(word.size()*3); //TODO pensar una buena funcion, esta es fruta
	if(aux % 2 == 0)//tiene q ser impar, para asegurar q el producto de la diagonal sea impar
		aux++;

	return 153;//aux;
}

int Hill::H2(string word){
	int aux = this->modL(word.size()*2); //TODO pensar una buena funcion, esta es fruta
		if(aux % 2 == 0)//tiene q ser impar, para asegurar q el producto de la diagonal sea impar
			aux++;

		return 41;//aux;
}

int Hill::inverseModL(int num){
	int i;
	for(i=0; i<CONST_L-1; i++){
		if(modL(num*i) == 1)
			break;
	}
	return i;
}

void Hill::buildKeyMatrix(string word){
	int h1 = H1(word);
	int h2 = H2(word);
	int aux = 1;
	for(int i=0 ; i < this->keySize; i++){
		for(int j=0; j < this->keySize; j++){
			if(j >= i) //triangular superior
				this->keyMatrix[i][j] = modL((h1*h2)*(i+j+1));
			else
				this->keyMatrix[i][j] = 0;
		}
	}


	//corregir el elemento superior izquierdo, primero hago productoria de la diagonal (sin el sup izq)
	for(int i=1 ; i < this->keySize; i++){
		aux = aux* this->keyMatrix[i][i];
	}
	//a la productoria le hago inversa mod L
	aux = inverseModL(aux);
	//modifico el elemento superior izquierdo
	this->keyMatrix[0][0] = aux;

}



