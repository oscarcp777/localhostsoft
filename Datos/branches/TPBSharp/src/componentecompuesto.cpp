#include "componentecompuesto.hpp"
ComponenteCompuesto::ComponenteCompuesto() throw(): Componente() {
}

ComponenteCompuesto::~ComponenteCompuesto() throw() {
}

bool ComponenteCompuesto::puede_agregar_componente(Componente::puntero componente) throw() {
	return true;
}

void ComponenteCompuesto::agregar_componente(Componente::puntero componente) throw() {
	if (this->puede_agregar_componente(componente)) {
		this->listaComponentes.push_back(componente);
	}
}

void ComponenteCompuesto::agregar_componente_sin_validar(Componente::puntero componente) throw() {
	this->listaComponentes.push_back(componente);
}

void ComponenteCompuesto::agregar_componente_antes_de(Componente::puntero componente, ComponenteCompuesto::iterador_componentes posicion) throw() {
	if (this->puede_agregar_componente(componente)) {
		this->listaComponentes.insert(posicion, componente);
	}
}

void ComponenteCompuesto::remover_componente(ComponenteCompuesto::iterador_componentes posicion) throw() {
	this->listaComponentes.erase(posicion);
}

void ComponenteCompuesto::remover_ultimo_componente() throw() {
	this->listaComponentes.pop_back();
}

void ComponenteCompuesto::establecer_componente(unsigned int posicion, Componente::puntero componente) throw() {
	this->listaComponentes[posicion] = componente;
}

void ComponenteCompuesto::transferir_componentes(ComponenteCompuesto::contenedor_componentes& contenedor_componentes) throw() {
	contenedor_componentes.clear();
	this->listaComponentes.swap(contenedor_componentes);
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

