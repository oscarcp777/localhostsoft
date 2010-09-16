#include "bloque_interno_b_sharp.hpp"

BloqueInternoBSharp::BloqueInternoBSharp(unsigned int longitud_maxima, unsigned int numero_bloque, unsigned int nivel) throw(): BloqueBSharp(longitud_maxima, numero_bloque, nivel) {
}

BloqueInternoBSharp::~BloqueInternoBSharp() throw() {
}

void BloqueInternoBSharp::agregar_rama(int rama) throw() {
	this->listaRamas.push_back(rama);
}

void BloqueInternoBSharp::agregar_rama_antes_de(int rama, BloqueInternoBSharp::iterador_ramas posicion) throw() {
	this->listaRamas.insert(posicion, rama);
}

void BloqueInternoBSharp::remover_rama(BloqueInternoBSharp::iterador_ramas posicion) throw() {
	this->listaRamas.erase(posicion);
}

void BloqueInternoBSharp::remover_ultima_rama() throw() {
	this->listaRamas.pop_back();
}

void BloqueInternoBSharp::transferir_ramas(BloqueInternoBSharp::contenedor_ramas& contenedor_ramas) throw() {
	contenedor_ramas.clear();
	this->listaRamas.swap(contenedor_ramas);
}

int BloqueInternoBSharp::obtener_rama(unsigned int posicion) const throw() {
	return this->listaRamas[posicion];
}

unsigned int BloqueInternoBSharp::cantidad_ramas() const throw() {
	return this->listaRamas.size();
}

BloqueInternoBSharp::iterador_ramas BloqueInternoBSharp::primer_rama() throw() {
	return this->listaRamas.begin();
}

BloqueInternoBSharp::iterador_ramas_constante BloqueInternoBSharp::primer_rama() const throw() {
	return this->listaRamas.begin();
}

BloqueInternoBSharp::iterador_ramas BloqueInternoBSharp::ultima_rama() throw() {
	return this->listaRamas.end();
}

BloqueInternoBSharp::iterador_ramas_constante BloqueInternoBSharp::ultima_rama() const throw() {
	return this->listaRamas.end();
}

bool BloqueInternoBSharp::puede_agregar_componente(Componente::puntero componente) throw() {
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

unsigned int BloqueInternoBSharp::obtener_longitud_datos() throw() {
	unsigned int longitud_datos = BloqueBSharp::obtener_longitud_datos();
	longitud_datos += sizeof(int) * this->listaRamas.size(); // Para las ramas en total
	return longitud_datos;
}
 
unsigned int BloqueInternoBSharp::obtener_longitud_administrativa() throw() {
	unsigned int longitud_administrativa = BloqueBSharp::obtener_longitud_administrativa();
	longitud_administrativa += sizeof(unsigned int); // Para la cantidad de ramas
	return longitud_administrativa;
}

