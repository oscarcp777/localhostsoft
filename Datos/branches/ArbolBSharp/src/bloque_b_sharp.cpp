#include "bloque_b_sharp.hpp"
#include<iostream>
BloqueBSharp::BloqueBSharp(unsigned int longitud_maxima, unsigned int numero_bloque, unsigned int nivel) throw(): Bloque(longitud_maxima), numero_bloque(numero_bloque), nivel(nivel) {
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

bool BloqueBSharp::es_hoja() const throw() {
	return this->obtener_nivel() == 0;
}

void BloqueBSharp::agregar_componente(Componente::puntero componente) throw() {
	if (componente != NULL) {
		if (this->puede_agregar_componente(componente)) {
		            Bloque::agregar_componente(componente);
		}
	} else {
		std::cout << "No se pudo agregar en bloque BSharp... " << std::endl;
	}
}

void BloqueBSharp::agregar_componente(Componente::puntero componente, ComponenteCompuesto::iterador_componentes posicion) throw() {
	if (componente != NULL) {
		if (this->puede_agregar_componente(componente)) {
			Bloque::agregar_componente(componente, posicion);
		}
	}
}

unsigned int BloqueBSharp::obtener_longitud_ocupada() const throw() {
	unsigned int longitud_ocupada = Bloque::obtener_longitud_ocupada();
	longitud_ocupada += sizeof(unsigned int);
	longitud_ocupada += sizeof(unsigned int);
	return longitud_ocupada;
}

