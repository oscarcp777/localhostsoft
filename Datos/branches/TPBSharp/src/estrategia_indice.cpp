#include "estrategia_indice.hpp"

EstrategiaIndice::EstrategiaIndice(Clave::puntero clavePrimaria, Esquema::puntero esq) throw() {
	this->clavePrimaria = clavePrimaria->clonar();
	this->esquema = esq->clonar();
}

EstrategiaIndice::~EstrategiaIndice() throw() {
}

Clave::puntero EstrategiaIndice::obtener_clave_primaria() const throw() {
	return this->clavePrimaria;
}

Esquema::puntero  EstrategiaIndice::obtener_esquema() throw() {
	return this->esquema;
}

