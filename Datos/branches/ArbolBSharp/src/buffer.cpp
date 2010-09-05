#include "buffer.hpp"

Buffer::Buffer(unsigned int longitud) throw(): Almacenamiento(longitud) {
}

Buffer::Buffer(unsigned int longitud, Esquema::puntero esquema, std::list<Clave::puntero> listaClaves) throw(): Almacenamiento(longitud)
{
    this->esquema = esquema;
    this->listaClaves = listaClaves;
}

Buffer::Buffer(unsigned int longitud, EsquemaBloque::puntero esquemaBloque, Esquema::puntero esquema, std::list<Clave::puntero> listaClaves) throw(): Almacenamiento(longitud)
{
    this->esquema = esquema;
    this->esquemaBloque = esquemaBloque;
    this->listaClaves = listaClaves;
}

Buffer::~Buffer() throw() {
	Buffer::iterador actual = this->buffer_interno.begin();
	Buffer::iterador fin = this->buffer_interno.end();

	while (actual != fin) {
		delete[] actual->second;
		++actual;
	}
}

bool Buffer::escribir(const char* bytes, unsigned int posicion) throw() {
	if (bytes == NULL) {
		return false;
	}
	unsigned int longitud = this->obtener_longitud_en_bytes();
	char* copia = new char[longitud];
	memcpy(copia, bytes, longitud);

	this->buffer_interno[posicion] = copia;
	return true;
}

bool Buffer::leer(char* bytes, unsigned int posicion) throw() {
	if (bytes == NULL) {
		return false;
	}
	Buffer::iterador posicion_encontrado = this->buffer_interno.find(posicion);
	if (posicion_encontrado == this->buffer_interno.end()) {
		return false;
	}
	unsigned int longitud = this->obtener_longitud_en_bytes();
	memcpy(bytes, posicion_encontrado->second, longitud);
	return true;
}
