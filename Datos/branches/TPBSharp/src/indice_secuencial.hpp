#ifndef INDICE_SECUENCIAL_HPP_INCLUDED
#define INDICE_SECUENCIAL_HPP_INCLUDED

#include "comparador_clave.hpp"
#include "almacenamiento.hpp"
#include "registro.hpp"
#include "archivo.hpp"
#include "buffer.hpp"
#include "RegistroLongitudVariable.hpp"
#include "RegistroLongitudFija.hpp"
#include "CampoStream.hpp"
#include "campo.hpp"
#include "campo_entero.hpp"
#include "campo_booleano.hpp"
#include "campo_doble.hpp"
#include "campo_flotante.hpp"
#include "campo_largo.hpp"
#include "campo_cadena.hpp"
#include "EstrategiaAlmacenamientoTexto.hpp"
#include "EstrategiaAlmacenamientoRegistros.hpp"
#include "EstrategiaAlmacenamientoBloques.hpp"
#include "EstrategiaAlmacenamientoCompuestoComprimido.hpp"

/**
 * Clase IndiceSecuencial que permite busquedas secuencialmente a partir de la clave
 */
class IndiceSecuencial: public ContadorReferencias
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<IndiceSecuencial> puntero;
        /**
         * Constructor
         */
        IndiceSecuencial(ComparadorClave::puntero comparador);
        /**
         * Destructor
         */
        virtual ~IndiceSecuencial() throw();
        /**
         * Busqueda para almacenamiento archivo
         */
        Registro::puntero Buscar(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave);
        /**
         * Busqueda para almacenamiento buffer
         */
        Registro::puntero Buscar(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave);
    private:
        /**
         * Comparador
         */
        ComparadorClave::puntero comparador;
        /**
         * Busqueda por registros para almacenamiento archivo
         */
        Registro::puntero BuscarPorRegistro(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave);
        /**
         * Busqueda por registros para almacenamiento buffer
         */
        Registro::puntero BuscarPorRegistro(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave);
        /**
         * Busqueda por bloques para almacenamiento archivo
         */
        Registro::puntero BuscarPorBloque(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave);
        /**
         * Busqueda por bloques para almacenamiento buffer
         */
        Registro::puntero BuscarPorBloque(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave);
        /**
         * Busqueda en texto para almacenamiento archivo
         */
        Registro::puntero BuscarPorTexto(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave);
        /**
         * Busqueda en texto para almacenamiento buffer
         */
        Registro::puntero BuscarPorTexto(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave);
        /**
         * Busqueda por compresor
         */
        Registro::puntero BuscarPorCompresor(Archivo::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave);
};

#endif // INDICE_SECUENCIAL_HPP_INCLUDED
