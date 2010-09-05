#include "EstrategiaAlmacenamientoEspacioLibre.hpp"

EstrategiaAlmacenamientoEspacioLibre::EstrategiaAlmacenamientoEspacioLibre(const std::string& nombre_archivo) throw() {
	this->archivo = new Archivo(sizeof(unsigned int), nombre_archivo);
	this->archivo->abrirModoBinario();
}

EstrategiaAlmacenamientoEspacioLibre::~EstrategiaAlmacenamientoEspacioLibre() throw() {
}

void EstrategiaAlmacenamientoEspacioLibre::escribir_espacio_ocupado(unsigned int posicion, unsigned int espacio_ocupado) throw() {
	this->archivo->escribir((char*) &espacio_ocupado, posicion);
}

unsigned int EstrategiaAlmacenamientoEspacioLibre::leer_espacio_ocupado(unsigned int posicion) throw() {
	unsigned int espacio_ocupado;
	this->archivo->leer((char*) &espacio_ocupado, posicion);
	return espacio_ocupado;
}

unsigned int EstrategiaAlmacenamientoEspacioLibre::buscar_espacio_libre() throw() {
	unsigned int cantidad_elementos = this->archivo->obtener_cantidad_registros();
	unsigned int contador = 0;
	unsigned int espacio_ocupado = 0;
	bool encontrado = false;

	while (contador < cantidad_elementos && !encontrado) {
		this->archivo->leer((char*) &espacio_ocupado, contador);
		if (this->es_espacio_libre(espacio_ocupado)) {
			encontrado = true;
		} else {
			++contador;
		}
	}

	if (!encontrado) {
		espacio_ocupado = 0;
		this->archivo->agregar((char *) &espacio_ocupado);
	}
	return contador;
}

