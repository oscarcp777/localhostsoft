#ifndef COMPRESORARITMETICO_HPP_INCLUDED
#define COMPRESORARITMETICO_HPP_INCLUDED

#include <string>
#include "BitStream.hpp"
#include "TablaCompresor.hpp"
#include "math.h"
#include "CompresorAritmeticoHelper.hpp"
#include "TablaCompresor.hpp"
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"

#define MAX_UNSIGNED_BYTE_VALUE 256

using namespace std;

/**
* Clase Compresor Aritmetico que define un compresor aritmetico de Orden Uno
*/
class CompresorAritmetico: public ContadorReferencias
{
    public:
        /**
        * Define el tipo de dato puntero.
        */
        typedef PunteroIntrusivo<CompresorAritmetico> puntero;
        /**
        * Constructor
        */
        CompresorAritmetico();
        /**
        * Destructor
        */
        ~CompresorAritmetico() throw();
        /**
        * Comprime la cadena enviada por bytesacomprimir
        */
        string Comprimir(const string &bytesAComprimir);
        /**
        * Descomprime la cadena bytesComprimidos
        */
        string Descomprimir(const string bytesComprimidos);

    private:
        /**
        * Piso actual
        */
        unsigned int piso;
        /**
        * Techo actual
        */
        unsigned int techo;
        /**
        * BitStream para el manejo de bits
        */
        BitStream bitStream;
        /**
        * Comprime el simbolo recibido por parametro
        */
        void ComprimirSimbolo(const unsigned char &simbolo, TablaCompresor &tablaFrecuencia);
        /**
        * Descomprime el simbolo
        */
        unsigned int DescomprimirSimbolo(TablaCompresor &tablaDescompresion, unsigned int &bufferLeido,
                                            unsigned int &tamanoInfoComprimida, unsigned int &ultimoBitEmitido, string &resultadoDescomprimido);
        /**
        * Comprime el ultimo simbolo recibido por parametro
        */
        void ComprimirUltimoSimbolo(const unsigned char &simbolo, TablaCompresor &tablaFrecuencia);
        /**
        * Escribe el piso
        */
        void EscribirPiso();
        /**
        * Obtiene el rango
        */
        void CalcularRango(const unsigned char simbolo, TablaCompresor &tablaFrecuencia, unsigned int &nuevoPiso, unsigned int &nuevoTecho) const;
        /**
        * Cargar los bits leidos
        */
        void CargarBufferLeido(unsigned int &bufferLeido, const string fuente, const unsigned int cantidadBits, unsigned int &UltimoBitEmitido);
        /**
        * Obtiene el simbolo del stream
        */
        unsigned char GetSimbolo(const unsigned int bufferLeido,TablaCompresor &tabla,unsigned int &npiso,unsigned int &ntecho);
};

#endif // COMPRESORARITMETICO_HPP_INCLUDED
