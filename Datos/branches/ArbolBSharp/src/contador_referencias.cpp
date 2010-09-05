#include "contador_referencias.hpp"

ContadorReferencias::ContadorReferencias() throw(): contador_referencias(0) {
}

ContadorReferencias::~ContadorReferencias() throw() {
}

void ContadorReferencias::incrementar_contador_referencias() throw() {
	this->contador_referencias += 1;
}

void ContadorReferencias::decrementar_contador_referencias() throw() {
	this->contador_referencias -= 1;
}

unsigned int ContadorReferencias::obtener_contador_referencias() const throw() {
	return this->contador_referencias;
}

