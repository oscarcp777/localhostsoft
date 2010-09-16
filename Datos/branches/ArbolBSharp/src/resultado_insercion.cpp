#include "resultado_insercion.hpp"

ResultadoInsercion::ResultadoInsercion() throw() {
}

ResultadoInsercion::~ResultadoInsercion() throw() {
}

const Registro::puntero& ResultadoInsercion::obtener_registro_clave_media() const throw() {
	return this->registro_clave_media;
}

void ResultadoInsercion::establecer_registro_clave_media(const Registro::puntero& registro_clave_media) throw() {
	this->registro_clave_media = registro_clave_media;
}
void ResultadoInsercion::establecer_registro_clave_izq(const Registro::puntero& registro_clave_izq) throw() {
	this->registro_clave_izq = registro_clave_izq;
}
void ResultadoInsercion::establecer_registro_clave_der(const Registro::puntero& registro_clave_der) throw() {
	this->registro_clave_der = registro_clave_der;
}

unsigned int ResultadoInsercion::obtener_bloque_izquierdo() const throw() {
	return this->bloque_izquierdo;
}

void ResultadoInsercion::establecer_bloque_izquierdo(unsigned int bloque_izquierdo) throw() {
	this->bloque_izquierdo = bloque_izquierdo;
}

unsigned int ResultadoInsercion::obtener_bloque_derecho() const throw() {
	return this->bloque_derecho;
}

void ResultadoInsercion::establecer_bloque_derecho(unsigned int bloque_derecho) throw() {
	this->bloque_derecho = bloque_derecho;
}
unsigned int ResultadoInsercion::obtener_bloque_medio() const throw() {
	return this->bloque_medio;
}
void ResultadoInsercion::establecer_bloque_medio(unsigned int bloque_medio) throw() {
	this->bloque_medio = bloque_medio;
}

