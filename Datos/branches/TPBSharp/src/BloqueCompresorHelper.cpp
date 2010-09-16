#include "BloqueCompresorHelper.hpp"

void BloqueCompresorHelper::escribir_registro(Esquema::puntero& esquema, Registro::puntero& registro, std::stringstream& buffer) throw() {
    Esquema::iterador_campos actualCampo = esquema->primer_campo();
    Esquema::iterador_campos finCampo = esquema->ultimo_campo();

    while (actualCampo != finCampo) {
        Campo::puntero campo = registro->obtener_campo(actualCampo->first);
        switch (actualCampo->second) {
            case TIPO_CAMPO_BOOLEANO: {
                buffer << *(bool*) campo->obtener_valor() << " ";
                break;
                };
            case TIPO_CAMPO_CADENA: {
                std::string cadena = *(std::string*) campo->obtener_valor();
                buffer << cadena.size() << " " << cadena << " ";
                break;
                };
            case TIPO_CAMPO_DOBLE: {
                buffer << *(double*) campo->obtener_valor() << " ";
                break;
                };
            case TIPO_CAMPO_ENTERO: {
                buffer << *(int*) campo->obtener_valor() << " ";
                break;
                };
            case TIPO_CAMPO_FLOTANTE: {
                buffer << *(float*) campo->obtener_valor() << " ";
                break;
                };
            case TIPO_CAMPO_LARGO: {
                buffer << *(long*) campo->obtener_valor() << " ";
                break;
                };
        };
        ++actualCampo;
    }
}

Registro::puntero BloqueCompresorHelper::leer_registro(Esquema::puntero& esquema, Clave::puntero& clavePrimaria, std::stringstream& buffer) throw() {
        Esquema::iterador_campos actualCampo = esquema->primer_campo();
        Esquema::iterador_campos finCampo = esquema->ultimo_campo();

        Registro::puntero registroLeido = new RegistroLongitudVariable(clavePrimaria);

        while (actualCampo != finCampo) {
                Campo::puntero campo;
                switch (actualCampo->second) {
                        case TIPO_CAMPO_BOOLEANO: {
                                bool valor;
                                buffer >> valor;
                                campo = new CampoBooleano(valor);
                                break;
                        };
                        case TIPO_CAMPO_CADENA: {
                                unsigned int largoCadena;
                                std::string valor;
                                buffer >> largoCadena;
                                buffer.seekg(1, std::ios_base::cur);
                                char* bufferCadena = new char[largoCadena + 1];
                                buffer.read(bufferCadena, largoCadena);
                                bufferCadena[largoCadena] = '\0';
                                valor = bufferCadena;
                                delete[] bufferCadena;
                                campo = new CampoCadena(valor);
                                break;
                        };
                        case TIPO_CAMPO_DOBLE: {
                                double valor;
                                buffer >> valor;
                                campo = new CampoDoble(valor);
                                break;
                        };
                        case TIPO_CAMPO_ENTERO: {
                                int valor;
                                buffer >> valor;
                                campo = new CampoEntero(valor);
                                break;
                        };
                        case TIPO_CAMPO_FLOTANTE: {
                                float valor;
                                buffer >> valor;
                                campo = new CampoEntero(valor);
                                break;
                        };
                        case TIPO_CAMPO_LARGO: {
                                long valor;
                                buffer >> valor;
                                campo = new CampoLargo(valor);
                                break;
                        };
                }
                registroLeido->agregar_campo(actualCampo->first, campo);
                ++actualCampo;
        }
        return registroLeido;
}

std::string BloqueCompresorHelper::comprimir_registro(Esquema::puntero& esquema, Registro::puntero& registro) throw() {
	CompresorAritmetico::puntero compresor = new CompresorAritmetico();
	std::stringstream buffer;

	BloqueCompresorHelper::escribir_registro(esquema, registro, buffer);

	return compresor->Comprimir(buffer.str());
}

