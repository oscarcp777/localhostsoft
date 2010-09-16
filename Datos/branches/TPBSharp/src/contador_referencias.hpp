#ifndef CONTADOR_REFERENCIAS_HPP
#define CONTADOR_REFERENCIAS_HPP

/**
 * Definicion de la clse ContadorReferencias que lleva la cuenta de
 * la cantidad de referencias que posee el objeto.
 */
class ContadorReferencias {
	public:
		/**
		 * Constructor de la clase ContadorReferencias.
		 */
		ContadorReferencias() throw();
		/**
		 * Destructor virtual de la clase ContadorReferencias.
		 */
		virtual ~ContadorReferencias() throw();
		/**
		 * Incrementa el contador de referencias.
		 */
		void incrementar_contador_referencias() throw();
		/**
		 * Decrementa el contador de referencias.
		 */
		void decrementar_contador_referencias() throw();
		/**
		 * Obtiene la cantidad de referencias del objeto.
		 */
		unsigned int obtener_contador_referencias() const throw();
	private:
		/**
		 * Almacena el contador de referencias.
		 */
		unsigned int contador_referencias;
};

#endif /** CONTADOR_REFERENCIAS_HPP */

