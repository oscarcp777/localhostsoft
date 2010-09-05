#include "estrategia_indice.hpp"

EstrategiaIndice::EstrategiaIndice(Clave::puntero clavePrimaria) throw() {
	this->clavePrimaria = clavePrimaria->clonar();
}

EstrategiaIndice::~EstrategiaIndice() throw() {
}

Clave::puntero EstrategiaIndice::obtener_clave_primaria() const throw() {
	return this->clavePrimaria;
}

