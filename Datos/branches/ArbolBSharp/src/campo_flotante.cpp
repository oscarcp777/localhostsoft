#include "campo_flotante.hpp"

CampoFlotante::CampoFlotante(float valor) throw(): Campo(), valor(valor) {
}

CampoFlotante::~CampoFlotante() throw() {
}

TipoCampo CampoFlotante::obtener_tipo_campo() const throw() {
	return TIPO_CAMPO_FLOTANTE;
}

unsigned int CampoFlotante::obtener_longitud_en_bytes() const throw() {
	return sizeof(float);
}

const void* CampoFlotante::obtener_valor() const throw() {
	return &(this->valor);
}

void CampoFlotante::establecer_valor(const void* valor) throw() {
	this->valor = (*(float*) valor);
}

Campo::puntero CampoFlotante::clonar() const throw() {
	return new CampoFlotante(valor);
}

bool CampoFlotante::operator == (const Campo& rhs) throw() {
	if (TIPO_CAMPO_FLOTANTE != rhs.obtener_tipo_campo()) {
		return false;
	}
	float flotanteLhs = (*(float*) this->obtener_valor());
	float flotanteRhs = (*(float*) rhs.obtener_valor());

	return flotanteLhs == flotanteRhs;
}

bool CampoFlotante::operator < (const Campo& rhs) throw() {
	if (TIPO_CAMPO_FLOTANTE != rhs.obtener_tipo_campo()) {
		return false;
	}
	float flotanteLhs = (*(float*) this->obtener_valor());
	float flotanteRhs = (*(float*) rhs.obtener_valor());

	return flotanteLhs < flotanteRhs;
}

bool CampoFlotante::operator > (const Campo& rhs) throw() {
	if (TIPO_CAMPO_FLOTANTE != rhs.obtener_tipo_campo()) {
		return false;
	}
	float flotanteLhs = (*(float*) this->obtener_valor());
	float flotanteRhs = (*(float*) rhs.obtener_valor());

	return flotanteLhs > flotanteRhs;
}

