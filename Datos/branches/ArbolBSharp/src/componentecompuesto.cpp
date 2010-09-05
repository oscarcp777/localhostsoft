#include "componentecompuesto.hpp"
ComponenteCompuesto::ComponenteCompuesto() throw(): Componente() {
}

ComponenteCompuesto::~ComponenteCompuesto() throw() {
}

void ComponenteCompuesto::agregar_componente(Componente::puntero componente) throw() {
	this->listaComponentes.push_back(componente);
}

void ComponenteCompuesto::agregar_componente(Componente::puntero componente, ComponenteCompuesto::iterador_componentes posicion) throw() {
	this->listaComponentes.insert(posicion, componente);
}

void ComponenteCompuesto::remover_componente(Componente::puntero componente) throw() {
	std::remove(this->primer_componente(), this->ultimo_componente(), componente);
}

void ComponenteCompuesto::transferir_componentes(ComponenteCompuesto::contenedor_componentes& contenedor_componentes) throw() {
	contenedor_componentes.clear();
	this->listaComponentes.swap(contenedor_componentes);
}

bool ComponenteCompuesto::contiene_componente(Componente::puntero componente) throw() {
	ComponenteCompuesto::iterador_componentes posicion;

	posicion = std::find(this->primer_componente(), this->ultimo_componente(), componente);

	return posicion != this->ultimo_componente();
}

Componente::puntero ComponenteCompuesto::obtener_componente(unsigned int indice) throw() {
	return this->listaComponentes[indice];
}

unsigned int ComponenteCompuesto::cantidad_componentes() const throw() {
	return this->listaComponentes.size();
}

ComponenteCompuesto::iterador_componentes ComponenteCompuesto::primer_componente() throw() {
	return this->listaComponentes.begin();
}

ComponenteCompuesto::iterador_componentes_constante ComponenteCompuesto::primer_componente() const throw() {
	return this->listaComponentes.begin();
}

ComponenteCompuesto::iterador_componentes ComponenteCompuesto::ultimo_componente() throw() {
	return this->listaComponentes.end();
}

ComponenteCompuesto::iterador_componentes_constante ComponenteCompuesto::ultimo_componente() const throw() {
	return this->listaComponentes.end();
}

