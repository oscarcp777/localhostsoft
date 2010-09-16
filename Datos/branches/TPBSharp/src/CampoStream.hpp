#ifndef CampoStream_HPP
#define CampoStream_HPP

#include <sstream>
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "tipo_campo.hpp"

using namespace std;

/**
 * Clase CampoStream que permite el manejo del stream de datos almacenados
 */
class CampoStream: public ContadorReferencias {
	private:
		stringstream buffer;

	public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<CampoStream> puntero;
        /**
         * Constructor de CampoStream
         */
		CampoStream();
		/**
         * Resetea el stream
         */
		void reset(void);
		/**
         * Retorna el stream de bytes almacenados.
         */
		const char* str(void);
		/**
         * Retorna el stream de bytes almacenados.
         */
		string str_string(void);
		/**
         * Carga el stream con el bloque indicado o parametro.
         */
		void str(string& bloque, unsigned size);
		/**
         * Carga el stream con el bloque indicado o parametro.
         */
		void str(char* bloque, unsigned size);
		/**
         * Inserta valor de un campo del tipo indicado en la siguiente posicion del stream.
         */
		void insert(const void* valor, TipoCampo tipo);
		/**
         * Inserta un string en la siguiente posicion del stream.
         */
		void insert(string cadena);
		/**
         * Inserta un string y su longitud como campo de control en la siguiente posicion del stream.
         */
		void insert(string cadena, int longitud);
		/**
         * Inserta un numero en la siguiente posicion del stream.
         */
		void insert(int numero);
		/**
         * Obtiene un entero en la siguiente posicion del stream.
         */
		bool get(int& numero);
		/**
         * Obtiene un string en la siguiente posicio del stream.
         */
		bool get(string& cadena, int longitud);
		/**
         * Obtiene un booleano en la siguiente posicio del stream.
         */
		bool get(bool& bandera);
		/**
         * Obtiene una cadena en la siguiente posicio del stream de la longitud indicada.
         */
		bool get(char** cadena, int longitud);
		/**
         * Obtiene un flotante en la siguiente posicio del stream.
         */
		bool get(float& numero);
		/**
         * Obtiene un doble en la siguiente posicio del stream.
         */
		bool get(double& numero);
		/**
         * Obtiene un largo en la siguiente posicio del stream.
         */
		bool get(long& numero);
		/**
         * Retorna el tamaño en bytes del stream almacenado.
         */
		unsigned size(void);
		/**
         * Desplaza al puntero del stream a la posicion indicada.
         */
		bool seek(unsigned pos);
		/**
         * Vacia el stream.
         */
		void erase(void);
		/**
         * Destructor
         */
		virtual ~CampoStream() throw();
};

#endif
