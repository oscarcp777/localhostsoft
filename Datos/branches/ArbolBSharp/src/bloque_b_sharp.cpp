#include "bloque_b_sharp.hpp"
#include<iostream>
BloqueBSharp::BloqueBSharp(unsigned int longitud_maxima, unsigned int numero_bloque, unsigned int nivel) throw(): Bloque(longitud_maxima), numero_bloque(numero_bloque), nivel(nivel), bloque_siguiente(ID_BLOQUE_INVALIDO), pesoPromedio(0){
}

BloqueBSharp::~BloqueBSharp() throw() {
}

unsigned int BloqueBSharp::obtener_numero_bloque() const throw() {
	return this->numero_bloque;
}

void BloqueBSharp::establecer_numero_bloque(unsigned int numero_bloque) throw() {
	this->numero_bloque = numero_bloque;
}

unsigned int BloqueBSharp::obtener_nivel() const throw() {
	return this->nivel;
}

void BloqueBSharp::establecer_nivel(unsigned int nivel) throw() {
	this->nivel = nivel;
}

int BloqueBSharp::obtener_bloque_siguiente() const throw() {
	return this->bloque_siguiente;
}

void BloqueBSharp::establecer_bloque_siguiente(int bloque_siguiente) throw() {
	this->bloque_siguiente = bloque_siguiente;
}

bool BloqueBSharp::es_hoja() const throw() {
	return this->obtener_nivel() == 0;
}

void BloqueBSharp::agregar_componente(Componente::puntero componente) throw() {
	if (componente != NULL) {
		if (this->puede_agregar_componente(componente)) {
		            Bloque::agregar_componente(componente);
		}
	} else {
		std::cout << "No se pudo agregar en bloque BSharp... " << std::endl;
	}
}

void BloqueBSharp::agregar_componente(Componente::puntero componente, ComponenteCompuesto::iterador_componentes posicion) throw() {
	if (componente != NULL) {
		if (this->puede_agregar_componente(componente)) {
			Bloque::agregar_componente(componente, posicion);
		}
	}
}

unsigned int BloqueBSharp::obtener_longitud_ocupada() const throw() {
	unsigned int longitud_ocupada = Bloque::obtener_longitud_ocupada();
	longitud_ocupada += sizeof(unsigned int);
	longitud_ocupada += sizeof(unsigned int);
	return longitud_ocupada;
}

unsigned int BloqueBSharp::obtener_espacio_metadata() const{
	unsigned int espacio_metadata = Bloque::obtener_espacio_metadata();
	espacio_metadata += sizeof(unsigned int);
	espacio_metadata += sizeof(unsigned int);
	return espacio_metadata;
}


// DONI borrar metodo
bool BloqueBSharp::esta_semi_vacio() throw() {
	unsigned int longitud_ocupada = this->obtener_longitud_ocupada();
	return longitud_ocupada <= (this->GetLongitudBytes() / 2);
}

unsigned int BloqueBSharp::getPesoPromedio() const
{
	if (pesoPromedio!=0)
		return pesoPromedio;
	else{
		ComponenteCompuesto::iterador_componentes_constante actual = this->primer_componente();
		ComponenteCompuesto::iterador_componentes_constante ultimo_registro = this->ultimo_componente();
		unsigned int pesoTotal = 0;
		unsigned int contador = 0;
		while (actual != ultimo_registro){
			Registro::puntero registroAux = static_cast<Registro::puntero>(*actual);
			pesoTotal += registroAux->GetLongitudBytes();
			actual++;
			contador++;
		}
		if (contador == 0)
			return 0;
		unsigned int pesoPromedio = pesoTotal/contador;
		return pesoPromedio;
	}
}

void BloqueBSharp::setPesoPromedio(unsigned int pesoPromedio)
{
	this->pesoPromedio = pesoPromedio;
}

bool BloqueBSharp::haySubflujo() const throw() {

	unsigned int cota_subflujo = (2*this->GetLongitudBytes()/3)-(0.5*this->getPesoPromedio());
	std::cout<<"SUBFLUJO_BAJA: "<<cota_subflujo<<std::endl;
	return (this->obtener_longitud_ocupada() < cota_subflujo);
}

