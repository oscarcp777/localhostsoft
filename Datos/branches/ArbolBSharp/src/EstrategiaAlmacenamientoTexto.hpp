#ifndef ESTRATEGIAALMACENAMIENTOTEXTO_HPP_INCLUDED
#define ESTRATEGIAALMACENAMIENTOTEXTO_HPP_INCLUDED

#include "EstrategiaAlmacenamiento.hpp"
#include "bloque.hpp"
#include "registro.hpp"
#include<string>
#include "campo_cadena.hpp"

class EstrategiaAlmacenamientoTexto: public EstrategiaAlmacenamiento
{
    public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<EstrategiaAlmacenamientoTexto> puntero;
        EstrategiaAlmacenamientoTexto();
        ~EstrategiaAlmacenamientoTexto() throw();
        bool Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento);
        Componente::puntero Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave);
        int AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento);
    private:
        bool EscribirRegistro(int posicion, Registro::puntero registro, Almacenamiento::puntero almacenamiento);
        bool EscribirBloque(int posicion, Bloque::puntero bloque, Almacenamiento::puntero almacenamiento);
};

#endif // ESTRATEGIAALMACENAMIENTOTEXTO_HPP_INCLUDED
