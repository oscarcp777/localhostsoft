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

class EstrategiaAlmacenamiento: public ContadorReferencias
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaAlmacenamiento> puntero;
        virtual bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        virtual Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        virtual int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        virtual ~EstrategiaAlmacenamiento() throw();
    protected:
        EstrategiaAlmacenamiento() throw();
};

#endif // ESTRATEGIAALMACENAMIENTO_HPP_INCLUDED
