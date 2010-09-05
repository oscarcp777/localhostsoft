#include "campo_cadena.hpp"

CampoCadena::CampoCadena(std::string valor) throw(): Campo(), valor(valor) {
}

CampoCadena::~CampoCadena() throw() {
}

TipoCampo CampoCadena::obtener_tipo_campo() const throw() {
	return TIPO_CAMPO_CADENA;
}

unsigned int CampoCadena::obtener_longitud_en_bytes() const throw() {
	return (sizeof(unsigned int) + this->valor.length());
}

const void* CampoCadena::obtener_valor() const throw() {
	return &(this->valor);
}

void CampoCadena::establecer_valor(const void* valor) throw() {
	this->valor = (*(std::string*) valor);
}

Campo::puntero CampoCadena::clonar() const throw() {
	return new CampoCadena(valor);
}

bool CampoCadena::operator == (const Campo& rhs) throw() {
	if (TIPO_CAMPO_CADENA != rhs.obtener_tipo_campo()) {
		return false;
	}
	std::string cadenaLhs = (*(std::string*) this->obtener_valor());
	std::string cadenaRhs = (*(std::string*) rhs.obtener_valor());

	return cadenaLhs == cadenaRhs;
}

bool CampoCadena::operator < (const Campo& rhs) throw() {
	if (TIPO_CAMPO_CADENA != rhs.obtener_tipo_campo()) {
		return false;
	}
	std::string cadenaLhs = (*(std::string*) this->obtener_valor());
	std::string cadenaRhs = (*(std::string*) rhs.obtener_valor());

	return cadenaLhs < cadenaRhs;
}

bool CampoCadena::operator > (const Campo& rhs) throw() {
	if (TIPO_CAMPO_CADENA != rhs.obtener_tipo_campo()) {
		return false;
	}
	std::string cadenaLhs = (*(std::string*) this->obtener_valor());
	std::string cadenaRhs = (*(std::string*) rhs.obtener_valor());

	return cadenaLhs > cadenaRhs;
}

