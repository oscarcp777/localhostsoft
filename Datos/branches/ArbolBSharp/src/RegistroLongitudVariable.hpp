#ifndef REGISTROLONGITUDVARIABLE_HPP_INCLUDED
#define REGISTROLONGITUDVARIABLE_HPP_INCLUDED

#include "puntero_intrusivo.hpp"
#include "registro.hpp"
#include "campo.hpp"

class RegistroLongitudVariable: public Registro
{
    public:
	/**
	 * Define el tipo de dato puntero.
	 */
	typedef PunteroIntrusivo<RegistroLongitudVariable> puntero;
	/**
	 * Constructor de la clase RegitroLongitudVariable.
	 */
        RegistroLongitudVariable(Clave::puntero clave_primaria) throw();
	/**
	 * Destructor virtual de la clase RegistroLongitudVariable.
	 */
        virtual ~RegistroLongitudVariable() throw();
	/**
	 * Clona la clase RegistroLongitudVariable.
	 */
	virtual Registro::puntero clonar() const throw();
};

#endif // REGISTROLONGITUDVARIABLE_HPP_INCLUDED
