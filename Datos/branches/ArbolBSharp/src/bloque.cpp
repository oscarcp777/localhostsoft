#include "bloque.hpp"

Bloque::Bloque(unsigned int longitud_maxima) throw(): ComponenteCompuesto(), longitud_maxima(longitud_maxima)
{
}

Bloque::~Bloque() throw()
{
}

unsigned int Bloque::GetLongitudBytes() const throw() {
	return this->longitud_maxima;
}

unsigned int Bloque::obtener_longitud_ocupada() const throw() {
	Bloque::iterador_componentes_constante actualComponente = this->primer_componente();
	Bloque::iterador_componentes_constante finComponente = this->ultimo_componente();
	unsigned int longitud_ocupada = 0;
	while (actualComponente != finComponente) {
		Componente::puntero componenteActual = *actualComponente;
		longitud_ocupada += componenteActual->GetLongitudBytes();
		++actualComponente;
	}
	longitud_ocupada += sizeof(unsigned int);
	return longitud_ocupada;
}

bool Bloque::puede_agregar_componente(Componente::puntero componente) const throw() {
	unsigned int longitud_ocupada = this->obtener_longitud_ocupada();
	if (componente != NULL) {
		if (longitud_ocupada + componente->GetLongitudBytes() <= this->GetLongitudBytes()) {
			return true;
		} else {
			return false;
		}
	}
	return true;
}

unsigned int Bloque::obtener_espacio_metadata() const{
	return (sizeof(unsigned int));
}

