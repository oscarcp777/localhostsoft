#include "campo_booleano.hpp"

CampoBooleano::CampoBooleano(bool valor) throw(): Campo(), valor(valor) {
}

CampoBooleano::~CampoBooleano() throw() {
}

TipoCampo CampoBooleano::obtener_tipo_campo() const throw() {
	return TIPO_CAMPO_BOOLEANO;
}

unsigned int CampoBooleano::obtener_longitud_en_bytes() const throw() {
	return sizeof(bool);
}

const void* CampoBooleano::obtener_valor() const throw() {
	return &(this->valor);
}

void CampoBooleano::establecer_valor(const void* valor) throw() {
	this->valor = (*(bool*) valor);
}

Campo::puntero CampoBooleano::clonar() const throw() {
	return new CampoBooleano(valor);
}

bool CampoBooleano::operator == (const Campo& rhs) throw() {
	if (TIPO_CAMPO_BOOLEANO != rhs.obtener_tipo_campo()) {
		return false;
	}
	bool booleanoLhs = (*(bool*) this->obtener_valor());
	bool booleanoRhs = (*(bool*) rhs.obtener_valor());

	return booleanoLhs == booleanoRhs;
}

bool CampoBooleano::operator < (const Campo& rhs) throw() {
	if (TIPO_CAMPO_BOOLEANO != rhs.obtener_tipo_campo()) {
		return false;
	}
	bool booleanoLhs = (*(bool*) this->obtener_valor());
	bool booleanoRhs = (*(bool*) rhs.obtener_valor());

	return booleanoLhs < booleanoRhs;
}

bool CampoBooleano::operator > (const Campo& rhs) throw() {
	if (TIPO_CAMPO_BOOLEANO != rhs.obtener_tipo_campo()) {
		return false;
	}
	bool booleanoLhs = (*(bool*) this->obtener_valor());
	bool booleanoRhs = (*(bool*) rhs.obtener_valor());

	return booleanoLhs > booleanoRhs;
}

