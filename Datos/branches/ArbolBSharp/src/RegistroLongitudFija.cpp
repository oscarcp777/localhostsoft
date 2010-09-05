#include "RegistroLongitudFija.hpp"

RegistroLongitudFija::RegistroLongitudFija(Clave::puntero clave_primaria, unsigned int longitud_maxima) throw() : Registro(clave_primaria), longitudMaxima(longitud_maxima) {
    this->longitudAcumulada = 0;
}

RegistroLongitudFija::~RegistroLongitudFija() throw() {

}

void RegistroLongitudFija::agregar_campo(const std::string& nombre_campo, Campo::puntero campo) throw() {
	unsigned int nuevaLongitud = this->longitudAcumulada + campo->obtener_longitud_en_bytes();
	if ( nuevaLongitud < this->GetLongitudBytes() ) {
		this->longitudAcumulada = nuevaLongitud;
	        Registro::agregar_campo(nombre_campo, campo);
	}
}

unsigned int RegistroLongitudFija::GetLongitudBytes() const throw() {
    return this->longitudMaxima;
}

Registro::puntero RegistroLongitudFija::clonar() const throw() {
	unsigned int clonLongitudMaxima = this->GetLongitudBytes();
	Clave::puntero clonClavePrimaria = this->obtener_clave_primaria()->clonar();

	Registro::puntero clonRegistro = new RegistroLongitudFija(clonClavePrimaria, clonLongitudMaxima);

	Registro::iterador_claves_constante actualClaveSecundaria = this->primer_clave_secundaria();
	Registro::iterador_claves_constante finClaveSecundaria = this->ultima_clave_secundaria();

	while (actualClaveSecundaria != finClaveSecundaria) {
		Clave::puntero elementoActual = *actualClaveSecundaria;
		clonRegistro->agregar_clave_secundaria(elementoActual->clonar());
		++actualClaveSecundaria;
	}

	Registro::iterador_campos_constante actualCampo = this->primer_campo();
	Registro::iterador_campos_constante finCampo = this->ultimo_campo();

	while (actualCampo != finCampo) {
		clonRegistro->agregar_campo(actualCampo->first, actualCampo->second->clonar());
		++actualCampo;
	}

	return clonRegistro;
}

