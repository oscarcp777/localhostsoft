#include "campo_entero.hpp"

CampoEntero::CampoEntero(int valor) throw(): Campo(), valor(valor) {
}

CampoEntero::~CampoEntero() throw() {
}

TipoCampo CampoEntero::obtener_tipo_campo() const throw() {
	return TIPO_CAMPO_ENTERO;
}

unsigned int CampoEntero::obtener_longitud_en_bytes() const throw() {
	return sizeof(int);
}

const void* CampoEntero::obtener_valor() const throw() {
	return &(this->valor);
}

void CampoEntero::establecer_valor(const void* valor) throw() {
	this->valor = (*(int*) valor);
}

Campo::puntero CampoEntero::clonar() const throw() {
	return new CampoEntero(valor);
}

bool CampoEntero::operator == (const Campo& rhs) throw() {
	if (TIPO_CAMPO_ENTERO != rhs.obtener_tipo_campo()) {
		return false;
	}
	int enteroLhs = (*(int*) this->obtener_valor());
	int enteroRhs = (*(int*) rhs.obtener_valor());

	return enteroLhs == enteroRhs;
}

bool CampoEntero::operator < (const Campo& rhs) throw() {
	if (TIPO_CAMPO_ENTERO != rhs.obtener_tipo_campo()) {
		return false;
	}
	int enteroLhs = (*(int*) this->obtener_valor());
    int enteroRhs = (*(int*) rhs.obtener_valor());

	return enteroLhs < enteroRhs;
}

bool CampoEntero::operator > (const Campo& rhs) throw() {
	if (TIPO_CAMPO_ENTERO != rhs.obtener_tipo_campo()) {
		return false;
	}
	int enteroLhs = (*(int*) this->obtener_valor());
	int enteroRhs = (*(int*) rhs.obtener_valor());

	return enteroLhs > enteroRhs;
}

