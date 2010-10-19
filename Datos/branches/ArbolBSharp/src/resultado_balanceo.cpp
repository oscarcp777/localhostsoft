#include "resultado_balanceo.hpp"

ResultadoBalanceo::ResultadoBalanceo() throw() {
}

ResultadoBalanceo::~ResultadoBalanceo() throw() {
}

void ResultadoBalanceo::establecer_registro_clave_media(const Registro::puntero& registro_clave_media) throw() {
	this->registro_clave_media = registro_clave_media;
}

const Registro::puntero& ResultadoBalanceo::obtener_registro_clave_media() const throw() {
	return this->registro_clave_media;
}

void ResultadoBalanceo::establecer_bloque_hermano_derecho(int bloque_hermano_derecho) throw() {
	this->bloque_hermano_derecho = bloque_hermano_derecho;
}

int ResultadoBalanceo::obtener_bloque_hermano_derecho() const throw() {
	return this->bloque_hermano_derecho;
}

