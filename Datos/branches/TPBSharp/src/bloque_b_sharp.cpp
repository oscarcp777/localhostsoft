#include "bloque_b_sharp.hpp"
#include<iostream>
BloqueBSharp::BloqueBSharp(unsigned int longitud_maxima, unsigned int numero_bloque, unsigned int nivel) throw(): Bloque(longitud_maxima), numero_bloque(numero_bloque), nivel(nivel), bloque_siguiente(ID_BLOQUE_INVALIDO), bloque_previo(ID_BLOQUE_INVALIDO) {
}

BloqueBSharp::~BloqueBSharp() throw() {
}

unsigned int BloqueBSharp::obtener_numero_bloque() const throw() {
	return this->numero_bloque;
}

void BloqueBSharp::establecer_numero_bloque(unsigned int numero_bloque) throw() {
	this->numero_bloque = numero_bloque;
}

unsigned int BloqueBSharp::obtener_nivel() const throw() {
	return this->nivel;
}

void BloqueBSharp::establecer_nivel(unsigned int nivel) throw() {
	this->nivel = nivel;
}

int BloqueBSharp::obtener_bloque_siguiente() const throw() {
	return this->bloque_siguiente;
}

void BloqueBSharp::establecer_bloque_siguiente(int bloque_siguiente) throw() {
	this->bloque_siguiente = bloque_siguiente;
}

bool BloqueBSharp::es_hoja() const throw() {
	return this->obtener_nivel() == 0;
}

unsigned int BloqueBSharp::obtener_longitud_administrativa() throw() {
	unsigned int longitud_ocupada = Bloque::obtener_longitud_administrativa();
	longitud_ocupada += sizeof(unsigned int); // Para el numero de bloque
	longitud_ocupada += sizeof(unsigned int); // Para el nivel de bloque
	longitud_ocupada += sizeof(int); // Para el bloque previo
	longitud_ocupada += sizeof(int); // Para el bloque siguiente
	return longitud_ocupada;
}

bool BloqueBSharp::esta_semi_vacio() throw() {
	unsigned int longitud_ocupada = this->obtener_longitud_ocupada();
	return longitud_ocupada < (this->GetLongitudBytes() / 2);
}

