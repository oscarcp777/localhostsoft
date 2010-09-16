#include "almacenamiento.hpp"

Almacenamiento::Almacenamiento(unsigned int longitud, TipoAlmacenamiento tipo) throw() : longitud_en_bytes(longitud), tipoAlmacenamiento(tipo) {
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

int Almacenamiento::GetEspacioBloque( int posicion )
{
    return this->LeerEspacioBloque( posicion );
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

int Almacenamiento::GetEspacioLibre()
{
    return -1;
}

TipoAlmacenamiento Almacenamiento::GetTipoAlmacenamiento()
{
    return this->tipoAlmacenamiento;
}
