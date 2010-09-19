#include "bloque_externo_b_sharp.hpp"
#include <iostream>

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


bool BloqueExternoBSharp::hay_subflujo() const throw() {

	unsigned int espacio_ocupado = this->obtener_longitud_ocupada() - this->obtener_espacio_metadata();
	std::cout << "Bloque: " << this->obtener_numero_bloque() <<" Espacio Ocupado: " << espacio_ocupado << " Peso prom: " << this->getPesoPromedio() << std::endl;
	unsigned int cota_subflujo = (2*this->GetLongitudBytes()/3)-(0.5*this->getPesoPromedio());
	std::cout << "Limite Subflujo: " <<  cota_subflujo << std::endl;
	if (this->obtener_longitud_ocupada() < cota_subflujo) {
		return true;
	} else {
		return false;
	}
}

unsigned int BloqueExternoBSharp::obtener_espacio_metadata() const{
	unsigned int espacio_metadata = BloqueBSharp::obtener_espacio_metadata();
	espacio_metadata += sizeof(int);
	return espacio_metadata;
}

