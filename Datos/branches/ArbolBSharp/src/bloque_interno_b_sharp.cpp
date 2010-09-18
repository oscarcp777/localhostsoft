#include "bloque_interno_b_sharp.hpp"
#include <iostream>

BloqueInternoBSharp::BloqueInternoBSharp(unsigned int longitud_maxima, unsigned int numero_bloque, unsigned int nivel) throw(): BloqueBSharp(longitud_maxima, numero_bloque, nivel) {
}

BloqueInternoBSharp::~BloqueInternoBSharp() throw() {
}

void BloqueInternoBSharp::agregar_rama(int rama) throw() {
	this->listaRamas.push_back(rama);
}

void BloqueInternoBSharp::agregar_rama(int rama, BloqueInternoBSharp::iterador_rama posicion) throw() {
	this->listaRamas.insert(posicion, rama);
}

void BloqueInternoBSharp::remover_rama(int rama) throw() {
	std::remove(this->primer_rama(), this->ultima_rama(), rama);
}

void BloqueInternoBSharp::transferir_ramas(BloqueInternoBSharp::contenedor_ramas& contenedor_ramas) throw() {
	contenedor_ramas.clear();
	this->listaRamas.swap(contenedor_ramas);
}

void BloqueInternoBSharp::vaciar_ramas() throw() {
	this->listaRamas.clear();
}

bool BloqueInternoBSharp::contiene_rama(int rama) throw() {
	BloqueInternoBSharp::iterador_rama posicion;

	posicion = std::find(this->primer_rama(), this->ultima_rama(), rama);

	return posicion != this->ultima_rama();
}

int BloqueInternoBSharp::obtener_rama(unsigned int indice) const throw() {
	return this->listaRamas[indice];
}

unsigned int BloqueInternoBSharp::cantidad_ramas() const throw() {
	return this->listaRamas.size();
}

BloqueInternoBSharp::iterador_rama BloqueInternoBSharp::primer_rama() throw() {
	return this->listaRamas.begin();
}

BloqueInternoBSharp::iterador_rama_constante BloqueInternoBSharp::primer_rama() const throw() {
	return this->listaRamas.begin();
}

BloqueInternoBSharp::iterador_rama BloqueInternoBSharp::ultima_rama() throw() {
	return this->listaRamas.end();
}

BloqueInternoBSharp::iterador_rama_constante BloqueInternoBSharp::ultima_rama() const throw() {
	return this->listaRamas.end();
}

bool BloqueInternoBSharp::puede_agregar_componente(Componente::puntero componente) const throw() {
        unsigned int longitud_ocupada = this->obtener_longitud_ocupada();
        if (componente != NULL) {
                if (longitud_ocupada + sizeof(int) + componente->GetLongitudBytes() <= this->GetLongitudBytes()) {
                        return true;
                } else {
                        return false;
                }
        }
        return true;
}

unsigned int BloqueInternoBSharp::obtener_longitud_ocupada() const throw() {
	unsigned int longitud_ocupada = BloqueBSharp::obtener_longitud_ocupada();
	longitud_ocupada += sizeof(unsigned int);
	longitud_ocupada += this->cantidad_ramas() * sizeof(int);
	return longitud_ocupada;
}


bool BloqueInternoBSharp::hay_subflujo() const throw() {
	unsigned int espacio_ocupado = this->obtener_longitud_ocupada() - this->obtener_espacio_metadata();
	std::cout << "Bloque: " << this->obtener_numero_bloque() <<" Espacio Ocupado: " << espacio_ocupado << std::endl;

	unsigned int cota_subflujo;
	if (this->cantidad_componentes() == 0)
		cota_subflujo = (this->GetLongitudBytes()/2);
	else
		cota_subflujo = (this->GetLongitudBytes()/2)+(0.5*(espacio_ocupado/this->cantidad_componentes()));
	std::cout << "Limite Subflujo: " <<  cota_subflujo << std::endl;
	if (this->obtener_longitud_ocupada() < cota_subflujo) {
		return true;
	} else {
		return false;
	}
}

unsigned int BloqueInternoBSharp::obtener_espacio_metadata() const{
	unsigned int espacio_metadata = BloqueBSharp::obtener_espacio_metadata();
	espacio_metadata += sizeof(unsigned int);
	espacio_metadata += this->cantidad_ramas() * sizeof(int);
	return espacio_metadata;
}

