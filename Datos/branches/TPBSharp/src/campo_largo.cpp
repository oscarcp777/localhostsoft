#include "campo_largo.hpp"

CampoLargo::CampoLargo(long valor) throw(): Campo(), valor(valor) {
}

CampoLargo::~CampoLargo() throw() {
}

TipoCampo CampoLargo::obtener_tipo_campo() const throw() {
	return TIPO_CAMPO_LARGO;
}

unsigned int CampoLargo::obtener_longitud_en_bytes() const throw() {
	return sizeof(long);
}

const void* CampoLargo::obtener_valor() const throw() {
	return &(this->valor);
}

void CampoLargo::establecer_valor(const void* valor) throw() {
	this->valor = (*(long*) valor);
}

Campo::puntero CampoLargo::clonar() const throw() {
	return new CampoLargo(valor);
}

bool CampoLargo::operator == (const Campo& rhs) throw() {
	if (TIPO_CAMPO_LARGO != rhs.obtener_tipo_campo()) {
		return false;
	}
	long largoLhs = (*(long*) this->obtener_valor());
	long largoRhs = (*(long*) rhs.obtener_valor());

	return largoLhs == largoRhs;
}

bool CampoLargo::operator < (const Campo& rhs) throw() {
	if (TIPO_CAMPO_LARGO != rhs.obtener_tipo_campo()) {
		return false;
	}
	long largoLhs = (*(long*) this->obtener_valor());
	long largoRhs = (*(long*) rhs.obtener_valor());

	return largoLhs < largoRhs;
}

bool CampoLargo::operator > (const Campo& rhs) throw() {
	if (TIPO_CAMPO_LARGO != rhs.obtener_tipo_campo()) {
		return false;
	}
	long largoLhs = (*(long*) this->obtener_valor());
	long largoRhs = (*(long*) rhs.obtener_valor());

	return largoLhs > largoRhs;
}

