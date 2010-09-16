#ifndef ESTRATEGIAALMACENAMIENTOTEXTO_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOTEXTO_HPP_INCLUDED

#include "EstrategiaAlmacenamiento.hpp"
#include "bloque.hpp"
#include "registro.hpp"
#include<string>
#include "campo_cadena.hpp"

/**
 * Clase EstrategiaAlmacenamientoTexto que administra el almacenamiento registros solo texto
 */
class EstrategiaAlmacenamientoTexto: public EstrategiaAlmacenamiento
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaAlmacenamientoTexto> puntero;
        /**
         * Constructor
         */
        EstrategiaAlmacenamientoTexto();
        /**
         * Destructor
         */
        ~EstrategiaAlmacenamientoTexto() throw();
        /**
         * Escribe en el almacenamiento el registro en la posicion indicada
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

#endif // ESTRATEGIAALMACENAMIENTOTEXTO_HPP_INCLUDED
