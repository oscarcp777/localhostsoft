#ifndef ESTRATEGIAALMACENAMIENTO_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTO_HPP_INCLUDED

#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "componente.hpp"
#include "string.h"
#include "almacenamiento.hpp"
#include "CampoStream.hpp"
#include "RegistroLongitudVariable.hpp"
#include "RegistroLongitudFija.hpp"
#include "campo.hpp"
#include "campo_entero.hpp"
#include "campo_booleano.hpp"
#include "campo_doble.hpp"
#include "campo_flotante.hpp"
#include "campo_largo.hpp"
#include "campo_cadena.hpp"

/**
 * Clase EstrategiaAlmacenamiento que define la interfaz a ser usada por los distintos tipos almacenamientos
 */
class EstrategiaAlmacenamiento: public ContadorReferencias
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaAlmacenamiento> puntero;
        /**
         * Escribe en el almacenamiento el registro en la posicion indicada
         */
        virtual bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
         * Lee del almacenamiento el registro guardado en la posicion indicada
         */
        virtual Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        /**
         * Agrega un registro en la primer posicion libre del almacenamiento
         */
        virtual int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
         * Elimina el espacio ocupado en la posicion indicada en el almacenamiento
         */
        virtual bool Eliminar(int posicion, Almacenamiento::puntero almacenamiento);
        /**
         * Destructor
         */
        virtual ~EstrategiaAlmacenamiento() throw();
        /**
         * Setea el registro con datos de la clave que se usara cuando sea necesario para buscar un registro
         */
        virtual void SetRegistroConDatosClave(Registro::puntero registro);
        /**
         * Devuelve el tipo de almacenamiento usado
         */
        bool por_buffer();
        /**
         * Permite indicar con un flag el almacenamiento usado
         */
        void set_por_buffer(bool por_buffer);
    private:
        bool porb;
    protected:
        /**
         * Constructor protegido
         */
        EstrategiaAlmacenamiento() throw();
};

#endif // ESTRATEGIAALMACENAMIENTO_HPP_INCLUDED
