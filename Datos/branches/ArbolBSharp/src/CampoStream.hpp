#ifndef CampoStream_HPP
#define CampoStream_HPP

#include <sstream>
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include "tipo_campo.hpp"

using namespace std;

class CampoStream: public ContadorReferencias {
	private:
		stringstream buffer;

	public:
        /**
         * Define el tipo de dato puntero.
         */
        typedef PunteroIntrusivo<CampoStream> puntero;
		/*Inicializacion de atributos*/
		CampoStream();

		/*Inicializacion de atributos*/
		void reset(void);

		/*Retorna el stream de bytes almacenados.*/
		const char* str(void);
		string str_string(void);

		/*Carga el stream con el bloque indicado o parametro.*/
		void str(string& bloque, unsigned size);
		void str(char* bloque, unsigned size);

		/*Inserta un entero en la siguiente posicion del stream.*/
		void insert(const void* valor, TipoCampo tipo);

		void insert(string cadena);

		void insert(string cadena, int longitud);

		void insert(int numero);

		/*Obtiene un entero en la siguiente posicion del stream.*/
		bool get(int& numero);

		/*Obtiene un string en la siguiente posicio del stream.*/
		bool get(string& cadena, int longitud);

		/*Obtiene un booleano en la siguiente posicio del stream.*/
		bool get(bool& bandera);

		bool get(char** cadena, int longitud);

		bool get(float& numero);

		bool get(double& numero);

		bool get(long& numero);

		/*Retorna el tamaño en bytes del stream almacenado.*/
		unsigned size(void);

		/*Desplaza al puntero del stream a la posicion indicada.*/
		bool seek(unsigned pos);

		/*Vacia el stream.*/
		void erase(void);

		virtual ~CampoStream() throw();
};

#endif
