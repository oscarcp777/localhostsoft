#include "EstrategiaAlmacenamientoBSharp.hpp"
#include<iostream>
EstrategiaAlmacenamientoBSharp::EstrategiaAlmacenamientoBSharp(Esquema::puntero esquema, Clave::puntero clavePrimaria) throw() {
	this->esquema = esquema->clonar();
	this->clavePrimaria = clavePrimaria->clonar();
}

EstrategiaAlmacenamientoBSharp::~EstrategiaAlmacenamientoBSharp() throw() {
}

bool EstrategiaAlmacenamientoBSharp::escribir_bloque(unsigned int numero_bloque, BloqueBSharp::puntero bloque, Archivo::puntero archivo) throw() {
	bool exitoso = false;
	if (bloque != NULL && archivo != NULL) {
		char* bytes = escribir_bloque_en_bytes(bloque);
		exitoso = archivo->escribir(bytes, numero_bloque);
		delete[] bytes;
	}
	return exitoso;
}

BloqueBSharp::puntero EstrategiaAlmacenamientoBSharp::leer_bloque(unsigned int numero_bloque, Archivo::puntero archivo) throw() {
	if (archivo != NULL) {
		char* bytes = new char[archivo->obtener_longitud_en_bytes()];
		if (archivo->leer(bytes, numero_bloque)) {
			BloqueBSharp::puntero bloque = leer_bloque_desde_bytes(bytes, archivo->obtener_longitud_en_bytes());
			delete[] bytes;
			return bloque;
		} else {
			delete[] bytes;
			return NULL;
		}
	}
	return NULL;
}

unsigned int EstrategiaAlmacenamientoBSharp::agregar_bloque(BloqueBSharp::puntero bloque, Archivo::puntero archivo) throw() {
	if (bloque != NULL && archivo != NULL) {
		char* bytes = escribir_bloque_en_bytes(bloque);
		if (archivo->agregar(bytes)) {
			unsigned int cantidad_registros = archivo->obtener_cantidad_registros();
			delete[] bytes;
			return cantidad_registros -1;
		} else {
			delete[] bytes;
			return -1;
		}
		delete[] bytes;
	}
	return -1;
}

Esquema::puntero EstrategiaAlmacenamientoBSharp::obtener_esquema() const throw() {
	return this->esquema;
}

Clave::puntero EstrategiaAlmacenamientoBSharp::obtener_clave_primaria() const throw() {
	return this->clavePrimaria;
}

char* EstrategiaAlmacenamientoBSharp::escribir_bloque_en_bytes(BloqueBSharp::puntero bloque) throw() {
	if (bloque != NULL) {

		if (bloque->es_hoja()) {
			// Caso de bloque externo
			BloqueExternoBSharp::puntero bloqueExterno = bloque;
			return escribir_bloque_externo_en_bytes(bloqueExterno);
		} else {
			// Caso de bloque interno
			BloqueInternoBSharp::puntero bloqueInterno = bloque;
			return escribir_bloque_interno_en_bytes(bloqueInterno);
		}
	}
	return NULL;
}

char* EstrategiaAlmacenamientoBSharp::escribir_bloque_externo_en_bytes(BloqueExternoBSharp::puntero bloque) throw() {
	// Creo array de bytes
	char* bytes = new char[bloque->GetLongitudBytes()];
	memset(bytes, 0, bloque->GetLongitudBytes());
	// Defino iterador de array de bytes
	char* bytesIterador = bytes;
	// Obtengo nivel bloque
	unsigned int nivel_bloque = bloque->obtener_nivel();
	// Obtengo numero de bloque
	unsigned int numero_bloque = bloque->obtener_numero_bloque();
	// Obtengo id bloque siguiente
	int bloque_siguiente = bloque->obtener_bloque_siguiente();
	// Obtengo cantidad de componentes
	unsigned int cantidad_componentes = bloque->cantidad_componentes();

	// Escribo nivel de bloque en array de bytes
	memcpy(bytesIterador, &nivel_bloque, sizeof(nivel_bloque));
	bytesIterador += sizeof(nivel_bloque);
	// Escribo numero bloque en array de bytes
	memcpy(bytesIterador, &numero_bloque, sizeof(numero_bloque));
	bytesIterador += sizeof(numero_bloque);

	// Escribo id bloque siguiente en array de bytes
	memcpy(bytesIterador, &bloque_siguiente, sizeof(bloque_siguiente));
	bytesIterador += sizeof(bloque_siguiente);

	// Escribo cantidad de componentes en array de bytes
	memcpy(bytesIterador, &cantidad_componentes, sizeof(cantidad_componentes));
	bytesIterador += sizeof(cantidad_componentes);

	Bloque::iterador_componentes actualComponente = bloque->primer_componente();
	Bloque::iterador_componentes finComponente = bloque->ultimo_componente();

	while (actualComponente != finComponente) {
		Esquema::iterador_campos actualCampo = this->obtener_esquema()->primer_campo();
		Esquema::iterador_campos finCampo = this->obtener_esquema()->ultimo_campo();
		Registro::puntero registroActual = (Registro::puntero) *actualComponente;

		while (actualCampo != finCampo) {
			Campo::puntero campoActual = registroActual->obtener_campo(actualCampo->first);
			// Si el campo es de tipo cadena
			if (campoActual->obtener_tipo_campo() == TIPO_CAMPO_CADENA) {
				std::string* cadena = (std::string*) campoActual->obtener_valor();
				unsigned int longitud_cadena = cadena->size();
				// Ecribo longitud de cadena en array de bytes
				memcpy(bytesIterador, &longitud_cadena, sizeof(longitud_cadena));
				bytesIterador += sizeof(longitud_cadena);
				// Escribo cadena en array de bytes
				memcpy(bytesIterador, cadena->c_str(), longitud_cadena);
				bytesIterador += longitud_cadena;
			} else {
				unsigned int longitud_campo = campoActual->obtener_longitud_en_bytes();
				// Escribo valor de campo en array de bytes
				memcpy(bytesIterador, campoActual->obtener_valor(), longitud_campo);
				bytesIterador += longitud_campo;
			}
			++actualCampo;
		}
		++actualComponente;
	}

	return bytes;
}


char* EstrategiaAlmacenamientoBSharp::escribir_bloque_interno_en_bytes(BloqueInternoBSharp::puntero bloque) throw() {
        // Creo array de bytes
        char* bytes = new char[bloque->GetLongitudBytes()];
        memset(bytes, 0, bloque->GetLongitudBytes());
        // Defino iterador de array de bytes
        char* bytesIterador = bytes;
	// Obtengo numero de bloque
	unsigned int numero_bloque = bloque->obtener_numero_bloque();
        // Obtengo nivel bloque
        unsigned int nivel_bloque = bloque->obtener_nivel();
	// Obtengo cantidad de ramas
	unsigned int cantidad_ramas = bloque->cantidad_ramas();
        // Obtengo cantidad de componentes
        unsigned int cantidad_componentes = bloque->cantidad_componentes();

	// Escribo nivel de bloque en array de bytes
	memcpy(bytesIterador, &nivel_bloque, sizeof(nivel_bloque));
	bytesIterador += sizeof(nivel_bloque);
        // Escribo numero bloque en array de bytes
        memcpy(bytesIterador, &numero_bloque, sizeof(numero_bloque));
        bytesIterador += sizeof(numero_bloque);
	// Escribo cantidad de ramas en array de bytes
	memcpy(bytesIterador, &cantidad_ramas, sizeof(cantidad_ramas));
	bytesIterador += sizeof(cantidad_ramas);

	BloqueInternoBSharp::iterador_rama actualRama = bloque->primer_rama();
	BloqueInternoBSharp::iterador_rama finRama = bloque->ultima_rama();

	while (actualRama != finRama) {
		int ramaActual = *actualRama;
		// Escribo rama en array de bytes
		memcpy(bytesIterador, &ramaActual, sizeof(ramaActual));
		bytesIterador += sizeof(ramaActual);
		++actualRama;
	}

	// Escribo cantidad de componentes en array de bytes
        memcpy(bytesIterador, &cantidad_componentes, sizeof(cantidad_componentes));
        bytesIterador += sizeof(cantidad_componentes);

        Bloque::iterador_componentes actualComponente = bloque->primer_componente();
        Bloque::iterador_componentes finComponente = bloque->ultimo_componente();

        while (actualComponente != finComponente) {
                Clave::iterador_campos actualCampo = this->obtener_clave_primaria()->primer_campo();
                Clave::iterador_campos finCampo = this->obtener_clave_primaria()->ultimo_campo();
                Registro::puntero registroActual = (Registro::puntero) *actualComponente;

                while (actualCampo != finCampo) {
                        Campo::puntero campoActual = registroActual->obtener_campo(*actualCampo);
                        // Si el campo es de tipo cadena
                        if (campoActual->obtener_tipo_campo() == TIPO_CAMPO_CADENA) {
                                std::string* cadena = (std::string*) campoActual->obtener_valor();
                                unsigned int longitud_cadena = cadena->size();
                                // Ecribo longitud de cadena en array de bytes
                                memcpy(bytesIterador, &longitud_cadena, sizeof(longitud_cadena));
                                bytesIterador += sizeof(longitud_cadena);
                                // Escribo cadena en array de bytes
                                memcpy(bytesIterador, cadena->c_str(), longitud_cadena);
                                bytesIterador += longitud_cadena;
                        } else {
                                unsigned int longitud_campo = campoActual->obtener_longitud_en_bytes();
                                // Escribo valor de campo en array de bytes
                                memcpy(bytesIterador, campoActual->obtener_valor(), longitud_campo);
                                bytesIterador += longitud_campo;
                        }
                        ++actualCampo;
                }
                ++actualComponente;
        }

        return bytes;
}

BloqueBSharp::puntero EstrategiaAlmacenamientoBSharp::leer_bloque_desde_bytes(char* bytes, unsigned int longitud_bytes_bloque) throw() {
	if (bytes != NULL) {
		unsigned int nivel_bloque;
		memcpy(&nivel_bloque, bytes, sizeof(nivel_bloque));
		if (nivel_bloque == 0) {
			return leer_bloque_externo_desde_bytes(bytes, longitud_bytes_bloque);
		} else {
			return leer_bloque_interno_desde_bytes(bytes, longitud_bytes_bloque);
		}
	}
	return NULL;
}

BloqueExternoBSharp::puntero EstrategiaAlmacenamientoBSharp::leer_bloque_externo_desde_bytes(char* bytes, unsigned int longitud_bytes_bloque) throw() {
	unsigned int numero_bloque;
	unsigned int nivel_bloque;
	int bloque_siguiente;
	unsigned int cantidad_componentes;

	memcpy(&nivel_bloque, bytes, sizeof(nivel_bloque));
	bytes += sizeof(nivel_bloque);
	memcpy(&numero_bloque, bytes, sizeof(numero_bloque));
	bytes += sizeof(numero_bloque);

	BloqueExternoBSharp::puntero bloque = new BloqueExternoBSharp(longitud_bytes_bloque, numero_bloque);

	memcpy(&bloque_siguiente, bytes, sizeof(bloque_siguiente));
	bytes += sizeof(bloque_siguiente);

	bloque->establecer_bloque_siguiente(bloque_siguiente);

	memcpy(&cantidad_componentes, bytes, sizeof(cantidad_componentes));
	bytes += sizeof(cantidad_componentes);

	for (unsigned int contador = 0; contador < cantidad_componentes; ++contador) {
		Esquema::iterador_campos actualCampo = this->obtener_esquema()->primer_campo();
		Esquema::iterador_campos finCampo = this->obtener_esquema()->ultimo_campo();
		Registro::puntero registro = new RegistroLongitudVariable(this->obtener_clave_primaria());
		while (actualCampo != finCampo) {
			switch (actualCampo->second) {
				case TIPO_CAMPO_BOOLEANO: {
					bool campoBooleano;
					memcpy(&campoBooleano, bytes, sizeof(campoBooleano));
					bytes += sizeof(campoBooleano);
					registro->agregar_campo(actualCampo->first, new CampoBooleano(campoBooleano));
					break;
				}
				case TIPO_CAMPO_CADENA: {
					unsigned int longitudCampoCadena;
					memcpy(&longitudCampoCadena, bytes, sizeof(longitudCampoCadena));
					bytes += sizeof(longitudCampoCadena);
					char* campoCadena = new char[longitudCampoCadena + 1];
					memset(campoCadena, 0, longitudCampoCadena + 1);
					memcpy(campoCadena, bytes, longitudCampoCadena);
					bytes += longitudCampoCadena;
					registro->agregar_campo(actualCampo->first, new CampoCadena(campoCadena));
					delete[] campoCadena;
					break;
				}
				case TIPO_CAMPO_DOBLE: {
					double campoDoble;
					memcpy(&campoDoble, bytes, sizeof(campoDoble));
					bytes += sizeof(campoDoble);
					registro->agregar_campo(actualCampo->first, new CampoDoble(campoDoble));
					break;
				}
				case TIPO_CAMPO_ENTERO: {
					int campoEntero;
					memcpy(&campoEntero, bytes, sizeof(campoEntero));
					bytes += sizeof(campoEntero);
					registro->agregar_campo(actualCampo->first, new CampoEntero(campoEntero));
					break;
				}
				case TIPO_CAMPO_FLOTANTE: {
					float campoFlotante;
					memcpy(&campoFlotante, bytes, sizeof(campoFlotante));
					bytes += sizeof(campoFlotante);
					registro->agregar_campo(actualCampo->first, new CampoFlotante(campoFlotante));
					break;
				}
				case TIPO_CAMPO_LARGO: {
					float campoLargo;
					memcpy(&campoLargo, bytes, sizeof(campoLargo));
					bytes += sizeof(campoLargo);
					registro->agregar_campo(actualCampo->first, new CampoLargo(campoLargo));
					break;
				}
			}
			++actualCampo;
		}
		bloque->agregar_componente(registro);
	}

	return bloque;
}

BloqueInternoBSharp::puntero EstrategiaAlmacenamientoBSharp::leer_bloque_interno_desde_bytes(char* bytes, unsigned int longitud_bytes_bloque) throw() {
	unsigned int numero_bloque;
        unsigned int nivel_bloque;
        unsigned int cantidad_ramas;
        unsigned int cantidad_componentes;

        memcpy(&nivel_bloque, bytes, sizeof(nivel_bloque));
        bytes += sizeof(nivel_bloque);

	memcpy(&numero_bloque, bytes, sizeof(numero_bloque));
	bytes += sizeof(numero_bloque);

        BloqueInternoBSharp::puntero bloque = new BloqueInternoBSharp(longitud_bytes_bloque, numero_bloque, nivel_bloque);

        memcpy(&cantidad_ramas, bytes, sizeof(cantidad_ramas));
        bytes += sizeof(cantidad_ramas);

	for (unsigned int contador = 0; contador < cantidad_ramas; ++contador) {
		unsigned int rama;
		memcpy(&rama, bytes, sizeof(rama));
		bytes += sizeof(rama);
		bloque->agregar_rama(rama);
	}

        memcpy(&cantidad_componentes, bytes, sizeof(cantidad_componentes));
        bytes += sizeof(cantidad_componentes);

        for (unsigned int contador = 0; contador < cantidad_componentes; ++contador) {
                Clave::iterador_campos actualCampo = this->obtener_clave_primaria()->primer_campo();
                Clave::iterador_campos finCampo = this->obtener_clave_primaria()->ultimo_campo();
                Registro::puntero registro = new RegistroLongitudVariable(this->obtener_clave_primaria());
                while (actualCampo != finCampo) {
                        switch (this->obtener_esquema()->obtener_campo(*actualCampo)) {
                                case TIPO_CAMPO_BOOLEANO: {
                                        bool campoBooleano;
                                        memcpy(&campoBooleano, bytes, sizeof(campoBooleano));
                                        bytes += sizeof(campoBooleano);
                                        registro->agregar_campo(*actualCampo, new CampoBooleano(campoBooleano));
                                        break;
                                }
                                case TIPO_CAMPO_CADENA: {
                                        unsigned int longitudCampoCadena;
                                        memcpy(&longitudCampoCadena, bytes, sizeof(longitudCampoCadena));
                                        bytes += sizeof(longitudCampoCadena);
                                        char* campoCadena = new char[longitudCampoCadena + 1];
                                        memset(campoCadena, 0, longitudCampoCadena + 1);
                                        memcpy(campoCadena, bytes, longitudCampoCadena);
                                        bytes += longitudCampoCadena;
                                        registro->agregar_campo(*actualCampo, new CampoCadena(campoCadena));
                                        delete[] campoCadena;
                                        break;
                                }
                                case TIPO_CAMPO_DOBLE: {
                                        double campoDoble;
                                        memcpy(&campoDoble, bytes, sizeof(campoDoble));
                                        bytes += sizeof(campoDoble);
                                        registro->agregar_campo(*actualCampo, new CampoDoble(campoDoble));
                                        break;
                                }
                                case TIPO_CAMPO_ENTERO: {
                                        int campoEntero;
                                        memcpy(&campoEntero, bytes, sizeof(campoEntero));
                                        bytes += sizeof(campoEntero);
                                        registro->agregar_campo(*actualCampo, new CampoEntero(campoEntero));
                                        break;
                                }
                                case TIPO_CAMPO_FLOTANTE: {
                                        float campoFlotante;
                                        memcpy(&campoFlotante, bytes, sizeof(campoFlotante));
                                        bytes += sizeof(campoFlotante);
                                        registro->agregar_campo(*actualCampo, new CampoFlotante(campoFlotante));
                                        break;
                                }
                                case TIPO_CAMPO_LARGO: {
                                        float campoLargo;
                                        memcpy(&campoLargo, bytes, sizeof(campoLargo));
                                        bytes += sizeof(campoLargo);
                                        registro->agregar_campo(*actualCampo, new CampoLargo(campoLargo));
                                        break;
                                }
                        }
                        ++actualCampo;
                }
                bloque->agregar_componente(registro);
        }

        return bloque;
}
