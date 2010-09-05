#include "RegistroLongitudVariable.hpp"

RegistroLongitudVariable::RegistroLongitudVariable(Clave::puntero clave_primaria) throw(): Registro(clave_primaria) {

}

RegistroLongitudVariable::~RegistroLongitudVariable() throw() {

}

Registro::puntero RegistroLongitudVariable::clonar() const throw() {
        Clave::puntero clonClavePrimaria = this->obtener_clave_primaria()->clonar();

        Registro::puntero clonRegistro = new RegistroLongitudVariable(clonClavePrimaria);

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

