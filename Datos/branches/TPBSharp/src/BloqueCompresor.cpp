#include "BloqueCompresor.hpp"
#include "esquema.hpp"
#include<iostream>
BloqueCompresor::BloqueCompresor(Esquema::puntero esquema, Clave::puntero clavePrimaria, unsigned int longitud_maxima) throw(): Bloque(longitud_maxima) {
    this->esquema = esquema;
    this->clavePrimaria = clavePrimaria;
    this->compresorAritmetico = new CompresorAritmetico();
}

BloqueCompresor::~BloqueCompresor() throw() {
}

unsigned int BloqueCompresor::obtener_longitud_administrativa() throw() {
    return 0;
}

unsigned int BloqueCompresor::obtener_longitud_datos() throw() {
	//std::stringstream buffer;
	//this->escribir_registros(buffer);
	//std::string contenidoComprimido = this->compresorAritmetico->Comprimir(buffer.str());
	//return contenidoComprimido.size();
	return this->registrosComprimidos.size();
}

unsigned int BloqueCompresor::obtener_longitud_ocupada() throw() {
    return this->obtener_longitud_datos();
}

bool BloqueCompresor::puede_agregar_componente(Componente::puntero componente) throw() {
	std::stringstream buffer;

	buffer << this->cantidad_componentes() + 1 << " ";

	this->escribir_registros(buffer);

	Registro::puntero registroAgregar = componente;
	BloqueCompresorHelper::escribir_registro(this->esquema, registroAgregar, buffer);

	std::string contenidoComprimido = this->compresorAritmetico->Comprimir(buffer.str());

	if (contenidoComprimido.size() <= this->GetLongitudBytes()) {
		this->registrosComprimidos = contenidoComprimido;
		return true;
	} else {
		return false;
	}
}

void BloqueCompresor::remover_componente(BloqueCompresor::iterador_componentes posicion) throw() {
	Bloque::remover_componente(posicion);

	std::stringstream buffer;

	buffer << this->cantidad_componentes() << " ";

	this->escribir_registros(buffer);

	this->registrosComprimidos = this->compresorAritmetico->Comprimir(buffer.str());
}

char* BloqueCompresor::obtener_datos_comprimidos() throw() {
	char* bufferDatosComprimidos = new char[this->GetLongitudBytes()];
	memset(bufferDatosComprimidos, 0, this->GetLongitudBytes());

	//std::stringstream buffer;
	//this->escribir_registros(buffer);
	//std::string contenidoComprimido = this->compresorAritmetico->Comprimir(buffer.str());
	memcpy(bufferDatosComprimidos, this->registrosComprimidos.c_str(), this->registrosComprimidos.size());

	return bufferDatosComprimidos;
}

void BloqueCompresor::establecer_datos_comprimidos(char* datosComprimidos, unsigned int longitud_comprimida) throw() {
	std::stringstream streamComprimido;
	streamComprimido.write(datosComprimidos, longitud_comprimida);
	this->registrosComprimidos = streamComprimido.str();

	std::string datosDescomprimidos = this->compresorAritmetico->Descomprimir(streamComprimido.str());

	std::stringstream streamDescomprimido(datosDescomprimidos);
	unsigned int cantidadRegistros;
	streamDescomprimido >> cantidadRegistros;
	for (unsigned int counter = 0; counter < cantidadRegistros; ++counter) {
		Registro::puntero registro = BloqueCompresorHelper::leer_registro(this->esquema, this->clavePrimaria, streamDescomprimido);
		this->agregar_componente_sin_validar(registro);
	}
}

void BloqueCompresor::escribir_registros(std::stringstream& buffer) throw() {
	BloqueCompresor::iterador_componentes_constante actualComponente = this->primer_componente();
        BloqueCompresor::iterador_componentes_constante finComponente = this->ultimo_componente();

        while (actualComponente != finComponente) {
                Registro::puntero registro = *actualComponente;
                BloqueCompresorHelper::escribir_registro(this->esquema, registro, buffer);
                ++actualComponente;
        }
}

