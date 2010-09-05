#ifndef ESTRATEGIAALMACENAMIENTOREGISTROS_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOREGISTROS_HPP_INCLUDED

#include "EstrategiaAlmacenamiento.hpp"
#include "registro.hpp"
#include "almacenamiento.hpp"
#include<string.h>

class EstrategiaAlmacenamientoRegistros: public EstrategiaAlmacenamiento
{
    private:
        Almacenamiento::puntero almacenamiento;
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaAlmacenamientoRegistros> puntero;
        EstrategiaAlmacenamientoRegistros();
        ~EstrategiaAlmacenamientoRegistros() throw();
        bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
};

#endif // ESTRATEGIAALMACENAMIENTOREGISTROS_HPP_INCLUDED
