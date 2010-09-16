#ifndef REGISTROLONGITUDFIJA_HPP_INCLUDED
#define REGISTROLONGITUDFIJA_HPP_INCLUDED

#include "puntero_intrusivo.hpp"
#include "registro.hpp"

/**
 * Clase RegistroLongitudFija que modela un objeto registro de longitud fija
 */
class RegistroLongitudFija: public Registro {
    public:
	/**
	 * Define el tipo de dato puntero.
	 */
	typedef PunteroIntrusivo<RegistroLongitudFija> puntero;
	/**
	 * Constructor de la clase RegistroLongitudFija.
	 */
        RegistroLongitudFija(Clave::puntero clave_primaria, unsigned int longitud_maxima) throw();
	/**
	 * Destructor virtual de la clase RegistroLongitudFija.
	 */
        virtual ~RegistroLongitudFija() throw();
	/**
	 * Agrega un campo al registro de longitud fija.
	 */
        virtual void agregar_campo(const std::string& nombre_campo, Campo::puntero campo) throw();
	/**
	 * Obtiene la longitud en bytes del registro.
	 */
	unsigned int GetLongitudBytes() const throw();
	/**
	 * Clona la clase RegistroLongitudFija.
	 */
	virtual Registro::puntero clonar() const throw();
    private:
        unsigned int longitudAcumulada;
        unsigned int longitudMaxima;
};

#endif // REGISTROLONGITUDFIJA_HPP_INCLUDED
