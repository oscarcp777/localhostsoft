#include "registro.hpp"

Registro::Registro(Clave::puntero clave_primaria) throw() {
	this->clavePrimaria = clave_primaria->clonar();
}

Registro::~Registro() throw() {
}

void Registro::establecer_clave_primaria(Clave::puntero clave_primaria) throw() {
	this->clavePrimaria = clave_primaria;
}

Clave::puntero Registro::obtener_clave_primaria() const throw() {
	return this->clavePrimaria;
}

void Registro::agregar_clave_secundaria(Clave::puntero clave_secundaria) throw() {
	this->listaClaves.push_back(clave_secundaria);
}

void Registro::remover_clave_secundaria(Clave::puntero clave_secundaria) throw() {
	this->listaClaves.remove(clave_secundaria);
}

unsigned int Registro::cantidad_claves_secundarias() const throw() {
	return this->listaClaves.size();
}

Registro::iterador_claves Registro::primer_clave_secundaria() throw() {
	return this->listaClaves.begin();

}

Registro::iterador_claves_constante Registro::primer_clave_secundaria() const throw() {
	return this->listaClaves.begin();
}

Registro::iterador_claves Registro::ultima_clave_secundaria() throw() {
	return this->listaClaves.end();
}

Registro::iterador_claves_constante Registro::ultima_clave_secundaria() const throw() {
	return this->listaClaves.end();
}

void Registro::agregar_campo(const std::string& nombre_campo, Campo::puntero campo) throw() {
	this->listaCampos.insert(std::make_pair(nombre_campo, campo));
}

void Registro::remover_campo(const std::string& nombre_campo) throw() {
	this->listaCampos.erase(nombre_campo);
}

bool Registro::contiene_campo(const std::string& nombre_campo) const throw() {
	Registro::iterador_campos_constante posicion = this->listaCampos.find(nombre_campo);

	return posicion != this->ultimo_campo();
}

unsigned int Registro::cantidad_campos() const throw() {
	return this->listaCampos.size();
}

Campo::puntero Registro::obtener_campo(const std::string& nombre_campo) const throw() {
//	return this->listaCampos[nombre_campo];
	Registro::iterador_campos_constante posicion = this->listaCampos.find(nombre_campo);
	return posicion->second;
}

unsigned int Registro::GetLongitudBytes() const throw() {
	unsigned int longitud = 0;
	for(Registro::iterador_campos_constante it= this->primer_campo(); it != this->ultimo_campo(); it++) {
		Campo::puntero campo = it->second;
		longitud += campo->obtener_longitud_en_bytes();
	}
	return longitud;
}

unsigned int Registro::GetLongitudBytesAlmacenada() const throw() {
	unsigned int longitud = 0;
	for(Registro::iterador_campos_constante it= this->primer_campo(); it != this->ultimo_campo(); it++) {
		Campo::puntero campo = it->second;
		if(campo->obtener_tipo_campo() == TIPO_CAMPO_CADENA)
            longitud += campo->obtener_longitud_en_bytes() + sizeof(int);
        else
            longitud += campo->obtener_longitud_en_bytes();
	}
	return longitud;
}

Registro::iterador_campos Registro::primer_campo() throw() {
	return this->listaCampos.begin();
}

Registro::iterador_campos_constante Registro::primer_campo() const throw() {
	return this->listaCampos.begin();
}

Registro::iterador_campos Registro::ultimo_campo() throw() {
	return this->listaCampos.end();
}

Registro::iterador_campos_constante Registro::ultimo_campo() const throw() {
	return this->listaCampos.end();
}

Registro::puntero Registro::clonar() const throw() {
	return 0;
}

int Registro::GetCantidadDeCampos()
{
    return this->listaCampos.size();
}

void Registro::ClearCampos()
{
    this->listaCampos.clear();
}
