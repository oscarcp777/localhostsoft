#ifndef ESTRATEGIAALMACENAMIENTOREGISTROS_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOREGISTROS_HPP_INCLUDED

#include "EstrategiaAlmacenamiento.hpp"
#include "registro.hpp"
#include "almacenamiento.hpp"
#include<string.h>

/**
 * Clase EstrategiaAlmacenamientoRegistros que maneja el almacenamiento por registros
 */
class EstrategiaAlmacenamientoRegistros: public EstrategiaAlmacenamiento
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaAlmacenamientoRegistros> puntero;
        /**
         * Constructor
         */
        EstrategiaAlmacenamientoRegistros();
        /**
         * Destructor
         */
        ~EstrategiaAlmacenamientoRegistros() throw();
        /**
         * Escribe en el alamcenamiento el registro en la posicion indicada
         */
        bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
         * Lee del almacenamiento el registro guardado en la posicion indicada
         */
        Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        /**
         * Agrega un registro en la primer posicion libre del almacenamiento
         */
        int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        /**
         * Elimina el espacio ocupado en la posicion indicada en el almacenamiento
         */
        bool Eliminar(int posicion, Almacenamiento::puntero almacenamiento);
};

#endif // ESTRATEGIAALMACENAMIENTOREGISTROS_HPP_INCLUDED
