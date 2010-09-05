#include "bloque_externo_b_sharp.hpp"

BloqueExternoBSharp::BloqueExternoBSharp(unsigned int longitud_maxima, unsigned int numero_bloque) throw(): BloqueBSharp(longitud_maxima, numero_bloque, 0),
	bloque_siguiente(BloqueExternoBSharp::ID_BLOQUE_INVALIDO) {
}

BloqueExternoBSharp::~BloqueExternoBSharp() throw() {
}

int BloqueExternoBSharp::obtener_bloque_siguiente() const throw() {
	return this->bloque_siguiente;
}

void BloqueExternoBSharp::establecer_bloque_siguiente(int numero_bloque) throw() {
	this->bloque_siguiente = numero_bloque;
}

unsigned int BloqueExternoBSharp::obtener_longitud_ocupada() const throw() {
	unsigned int longitud_ocupada = BloqueBSharp::obtener_longitud_ocupada();
	longitud_ocupada += sizeof(int);
	return longitud_ocupada;
}

