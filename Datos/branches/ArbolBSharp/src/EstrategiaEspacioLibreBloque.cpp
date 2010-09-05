#include "EstrategiaEspacioLibreBloque.hpp"

EstrategiaEspacioLibreBloque::EstrategiaEspacioLibreBloque(unsigned int longitud_maxima, float porcentaje_ocupado, const std::string& nombre_archivo) throw():
	EstrategiaAlmacenamientoEspacioLibre(nombre_archivo) {
	this->longitud_maxima = longitud_maxima;
	this->porcentaje_ocupado = porcentaje_ocupado;
}

EstrategiaEspacioLibreBloque::~EstrategiaEspacioLibreBloque() throw() {
}

bool EstrategiaEspacioLibreBloque::es_espacio_libre(unsigned int espacio_ocupado) throw() {
	//unsigned int longitud_maxima_ocupada = ((float) this->longitud_maxima * this->porcentaje_ocupado);
	return espacio_ocupado == 0;
}

