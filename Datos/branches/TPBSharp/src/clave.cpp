#include "clave.hpp"

Clave::Clave() throw() {
}

Clave::~Clave() throw() {
}

void Clave::agregar_campo(const std::string& nombre_campo) throw() {
	this->listaCampos.push_back(nombre_campo);
}

void Clave::remover_campo(const std::string& nombre_campo) throw() {
	this->listaCampos.remove(nombre_campo);
}

unsigned int Clave::cantidad_campos() const throw() {
	return this->listaCampos.size();
}

Clave::iterador_campos Clave::primer_campo() throw() {
	return this->listaCampos.begin();
}

Clave::iterador_campos_constante Clave::primer_campo() const throw() {
	return this->listaCampos.begin();
}

Clave::iterador_campos Clave::ultimo_campo() throw() {
	return this->listaCampos.end();
}

Clave::iterador_campos_constante Clave::ultimo_campo() const throw() {
	return this->listaCampos.end();
}

Clave::puntero Clave::clonar() const throw() {
	Clave::puntero clonClave = new Clave();

	Clave::iterador_campos_constante actualCampo = this->primer_campo();
	Clave::iterador_campos_constante finCampo = this->ultimo_campo();

	while (actualCampo != finCampo) {
		clonClave->agregar_campo(*actualCampo);
		++actualCampo;
	}

	return clonClave;
}

