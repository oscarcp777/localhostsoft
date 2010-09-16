#include "esquema.hpp"

Esquema::Esquema() throw() {
}

Esquema::~Esquema() throw() {
}

void Esquema::agregar_campo(const std::string& nombre_campo, TipoCampo tipo_campo) throw() {
	this->listaCampos.insert(std::make_pair(nombre_campo, tipo_campo));
}

void Esquema::remover_campo(const std::string& nombre_campo) throw() {
	this->listaCampos.erase(nombre_campo);
}

bool Esquema::contiene_campo(const std::string& nombre_campo) throw() {
	Esquema::iterador_campos posicion = this->listaCampos.find(nombre_campo);

	return posicion != this->ultimo_campo();
}

TipoCampo Esquema::obtener_campo(const std::string& nombre_campo) throw() {
	return this->listaCampos[nombre_campo];
}

unsigned int Esquema::cantidad_campos() const throw() {
	return this->listaCampos.size();
}

Esquema::iterador_campos Esquema::primer_campo() throw() {
	return this->listaCampos.begin();
}

Esquema::iterador_campos_constante Esquema::primer_campo() const throw() {
	return this->listaCampos.begin();
}

Esquema::iterador_campos Esquema::ultimo_campo() throw() {
	return this->listaCampos.end();
}

Esquema::iterador_campos_constante Esquema::ultimo_campo() const throw() {
	return this->listaCampos.end();
}

Esquema::puntero Esquema::clonar() const throw() {
	Esquema::puntero clonEsquema = new Esquema();

	Esquema::iterador_campos_constante actualCampo = this->primer_campo();
	Esquema::iterador_campos_constante finCampo = this->ultimo_campo();

	while (actualCampo != finCampo) {
		clonEsquema->agregar_campo(actualCampo->first, actualCampo->second);
		++actualCampo;
	}

	return clonEsquema;
}

