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

unsigned int Bloque::obtener_longitud_administrativa() throw() {
	unsigned int longitud_administrativa = 0;
	longitud_administrativa = sizeof(unsigned int); // Cantidad de regitros en el bloque.
	return longitud_administrativa;
}

unsigned int Bloque::obtener_longitud_datos() throw() {
	Bloque::iterador_componentes_constante actualComponente = this->primer_componente();
	Bloque::iterador_componentes_constante finComponente = this->ultimo_componente();
	unsigned int longitud_datos = 0;
	while (actualComponente != finComponente) {
		Componente::puntero componenteActual = *actualComponente;
		longitud_datos += componenteActual->GetLongitudBytes();
		++actualComponente;
	}
	return longitud_datos;
}

unsigned int Bloque::obtener_longitud_ocupada() throw() {
	unsigned int longitud_ocupada = 0;
	longitud_ocupada += this->obtener_longitud_administrativa();
	longitud_ocupada += this->obtener_longitud_datos();
	return longitud_ocupada;
}

bool Bloque::puede_agregar_componente(Componente::puntero componente) throw() {
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


