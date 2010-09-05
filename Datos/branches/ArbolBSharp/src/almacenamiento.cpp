#include "almacenamiento.hpp"

Almacenamiento::Almacenamiento(unsigned int longitud) throw() : longitud_en_bytes(longitud) {
}

Almacenamiento::~Almacenamiento() throw() {
}

void Almacenamiento::establecer_longitud_en_bytes(unsigned int longitud) throw() {
	this->longitud_en_bytes = longitud;
}

unsigned int Almacenamiento::obtener_longitud_en_bytes() const throw() {
	return this->longitud_en_bytes;
}

Esquema::puntero Almacenamiento::GetEsquema()
{
    this->LeerHeader();
    return this->esquema;
}

EsquemaBloque::puntero Almacenamiento::GetEsquemaBloque()
{
    this->LeerHeaderBloque();
    return this->esquemaBloque;
}

void Almacenamiento::LeerHeader()
{
}

void Almacenamiento::LeerHeaderBloque()
{
}

std::list<Clave::puntero> Almacenamiento::GetClaves()
{
    std::list<Clave::puntero>* lista = new std::list<Clave::puntero>();
    return *lista;
}

void Almacenamiento::ActualizarEsquemaBloque(EsquemaBloque::puntero esquemaBloque)
{
    this->esquemaBloque = esquemaBloque;
}
