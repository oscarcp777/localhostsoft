#include "campo_doble.hpp"

CampoDoble::CampoDoble(double valor) throw(): Campo(), valor(valor) {
}

CampoDoble::~CampoDoble() throw() {
}

TipoCampo CampoDoble::obtener_tipo_campo() const throw() {
	return TIPO_CAMPO_DOBLE;
}

unsigned int CampoDoble::obtener_longitud_en_bytes() const throw() {
	return sizeof(double);
}

const void* CampoDoble::obtener_valor() const throw() {
	return &(this->valor);
}

void CampoDoble::establecer_valor(const void* valor) throw() {
	this->valor = (*(double*) valor);
}

Campo::puntero CampoDoble::clonar() const throw() {
	return new CampoDoble(valor);
}

bool CampoDoble::operator == (const Campo& rhs) throw() {
	if (TIPO_CAMPO_DOBLE != rhs.obtener_tipo_campo()) {
		return false;
	}
	double dobleLhs = (*(double*) this->obtener_valor());
	double dobleRhs = (*(double*) rhs.obtener_valor());

	return dobleLhs == dobleRhs;
}

bool CampoDoble::operator < (const Campo& rhs) throw() {
	if (TIPO_CAMPO_DOBLE != rhs.obtener_tipo_campo()) {
		return false;
	}
	double dobleLhs = (*(double*) this->obtener_valor());
	double dobleRhs = (*(double*) rhs.obtener_valor());

	return dobleLhs < dobleRhs;
}

bool CampoDoble::operator > (const Campo& rhs) throw() {
	if (TIPO_CAMPO_DOBLE != rhs.obtener_tipo_campo()) {
		return false;
	}
	double dobleLhs = (*(double*) this->obtener_valor());
	double dobleRhs = (*(double*) rhs.obtener_valor());

	return dobleLhs > dobleRhs;
}

