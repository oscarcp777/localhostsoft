/*
 * Hill.cpp
 *
 *  Created on: 14/11/2010
 *      Author: Santiago
 */

#include "Hill.h"
using namespace std;
#include <math.h>

Hill *Hill::instance = NULL;

Hill::Hill() {

}

Hill::~Hill() {
	for (int k=0; k<this->keySize; k++)
			delete []this->keyMatrix[k];
	delete []this->keyMatrix;
	for (int k=0; k<this->keySize; k++)
			delete []this->keyInvertedMatrix[k];
	delete []this->keyInvertedMatrix;

}


void Hill::initialize(const int keySize, string clave){
	this->keySize = keySize;
	this->keyMatrix = new double *[keySize];
	for (int k=0; k<keySize; k++)
		this->keyMatrix[k] = new double[keySize];

	this->keyInvertedMatrix = new double *[keySize];
	for (int k=0; k<keySize; k++)
		this->keyInvertedMatrix[k] = new double[keySize];

	//NOTA El det(keyMatrix) mod 128 = 1 para que funcione el metodo
	double aux;
	// Armado matriz clave
	aux = this->buildKeyMatrix(clave);
	// Armado matriz clave inversa
	this->buildKeyInverted(aux);
}

Hill *Hill::getInstance()
{
	 if (!Hill::instance)
		Hill::instance = new Hill();
	 return Hill::instance;
}


void Hill::buildKeyInverted(long double num){
	GaussJordan* gaussJordan = new GaussJordan(this->keySize, this->keyMatrix, this->keyInvertedMatrix);
	gaussJordan->hallar_inversa(num);
	delete gaussJordan;
}

Buffer* Hill::encrypt(char* messageToEncrypt,int size){
	return this->translate(messageToEncrypt,size, this->keyMatrix);
}

Buffer* Hill::decrypt(char* messageToDecrypt,int size){
	return this->translate(messageToDecrypt, size,this->keyInvertedMatrix);
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
Buffer* Hill::translate(char* messageOriginal,int sizeText, double** matrix){

	Buffer* result= new Buffer(sizeText);
	int n = 0;
	int j = 0;
	double* textPart = new double[this->keySize];
	char letter;

	while (n < sizeText) {
		char c = messageOriginal[n++];
		if (DEBUG) cout << "letra "<<n<<": "<<int(c)<<endl;
		textPart[j++] = int(c);
		if (j >= this->keySize) {

			double* multiplyResult = productVectorPerMatrix(textPart, matrix);
			modL(multiplyResult);

			for (int i = 0; i < this->keySize; i++) {
				letter = char(multiplyResult[i]);
				result->packField(&letter,sizeof(char));
			}
			j = 0;
			delete []multiplyResult;
		}
	}
	delete []textPart;
	result->init();
	return result;

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
			modL(multiplyResult);

			for (int i = 0; i < this->keySize; i++) {
				double aux = round(multiplyResult[i]);
				int round = aux;
				if (DEBUG) cout <<"Sin round: "<<multiplyResult[i]<<"  Con round: "<< round;
				letter = char(round);
				if (DEBUG) cout <<"letra: " << letter<<"-"<<endl;
				result.append(&letter,sizeof(char));
			}
			j = 0;
			delete []multiplyResult;
		}
	}
	if (DEBUG) cout << endl;
	delete []textPart;

	return result;

}



double* Hill::productVectorPerMatrix(double *vector, double** matrix){

	double* result = new double[this->keySize];
	int i, j;

	for (i = 0; i < this->keySize; i++) {
		result[i] = 0;
		for (j = 0; j < this->keySize; j++)
			result[i] += round(matrix[i][j] * vector[j]);
		if (DEBUG) cout << " en product: "<<result[i]<<endl;
	}
	return result;

}

void Hill::modL(double *vector){

	for (int i = 0; i < this->keySize; i++) {
		long int toInt = (long int)vector[i];
		int aux =  toInt % CONST_L;
		if (aux < 0) aux = aux + CONST_L;
		vector[i] = aux;
		if (DEBUG) cout <<"en MOD:"<< vector[i]<<endl;
	}

}

int Hill::modL(long int value){
	int aux = value % CONST_L;
	if (aux < 0)
		aux = aux + CONST_L;
	return aux;
}

int Hill::H1(string word){
	int aux = this->modL((word.size()/100)*3); //TODO pensar una buena funcion, esta es fruta
	if(aux % 2 == 0)//tiene q ser impar, para asegurar q el producto de la diagonal sea impar
		aux++;

	return aux;
}

int Hill::H2(string word){
	int aux = this->modL((word.size()/60)*2); //TODO pensar una buena funcion, esta es fruta
		if(aux % 2 == 0)//tiene q ser impar, para asegurar q el producto de la diagonal sea impar
			aux++;

		return aux;
}

int Hill::inverseModL(int num){
	int i;
	for(i=0; i<CONST_L-1; i++){
		if(modL(num*i) == 1)
			break;
	}
	return i;
}

long double Hill::buildKeyMatrix(string word){
	int h1 = H1(word);
	int h2 = H2(word);
	long double aux = 1;
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
	long double aux2 = aux;
	aux = inverseModL(aux);
	//modifico el elemento superior izquierdo
	this->keyMatrix[0][0] = aux;

	return aux2*aux;
}



