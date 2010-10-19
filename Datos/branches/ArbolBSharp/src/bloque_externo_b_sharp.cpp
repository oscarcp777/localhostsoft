#include "bloque_externo_b_sharp.hpp"
#include <iostream>

BloqueExternoBSharp::BloqueExternoBSharp(unsigned int longitud_maxima, unsigned int numero_bloque) throw(): BloqueBSharp(longitud_maxima, numero_bloque, 0){
}

BloqueExternoBSharp::~BloqueExternoBSharp() throw() {
}

unsigned int BloqueExternoBSharp::obtener_longitud_ocupada() const throw() {
	unsigned int longitud_ocupada = BloqueBSharp::obtener_longitud_ocupada();
	longitud_ocupada += sizeof(int);
	return longitud_ocupada;
}


bool BloqueExternoBSharp::hay_subflujo(unsigned int espacioMin) const throw() {

	unsigned int cota_subflujo = espacioMin-(0.5*this->getPesoPromedio())+obtener_espacio_metadata();
	std::cout<<"SUBFLUJO: "<<cota_subflujo<<std::endl;
	return (this->obtener_longitud_ocupada() < cota_subflujo);
}

bool BloqueExternoBSharp::hay_subflujo() const throw() {

	unsigned int cota_subflujo = (2*this->GetLongitudBytes()/3)-(0.5*this->getPesoPromedio());
	std::cout<<"SUBFLUJO_BAJA: "<<cota_subflujo<<std::endl;
	return (this->obtener_longitud_ocupada() < cota_subflujo);
}

unsigned int BloqueExternoBSharp::obtener_espacio_metadata() const{
	unsigned int espacio_metadata = BloqueBSharp::obtener_espacio_metadata();
	espacio_metadata += sizeof(int);
	return espacio_metadata;
}

