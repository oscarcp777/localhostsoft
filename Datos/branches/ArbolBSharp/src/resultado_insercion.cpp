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

