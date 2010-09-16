#ifndef BITSTREAM_HPP_INCLUDED
#define BITSTREAM_HPP_INCLUDED

#include <string>
#include "math.h"
#include "CompresorAritmeticoHelper.hpp"
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"

/**
 * Clase BitStream que el manejo de bits
 */
class BitStream: public ContadorReferencias
{
    public:
        /**
        * Define el tipo de dato puntero.
        */
        typedef PunteroIntrusivo<BitStream> puntero;
        /**
        * Constructor
        */
        BitStream();
        /**
        * Destructor
        */
        virtual ~BitStream() throw();
        /**
        * Devuelve los bits escritos
        */
        std::string GetBytesEscritos();
        /**
        * Procesa el techo y piso
        */
        void Procesar(unsigned int &techo, unsigned int &piso);
        /**
        * Compacta los bytes leidos
        */
        unsigned int compactarBufferLeido(unsigned int &bufferLeido);
        /**
        * Reinicia el stream de bits
        */
        void Reiniciar();
    private:
        /**
        * Indicador de Overflow
        */
        bool HayOverflow(const unsigned int &techo, const unsigned int &piso) const;
        /**
        * Indicador de Underflow
        */
        bool HayUnderflow(const unsigned int &techo, const unsigned int &piso) const;
        /**
        * Maneja el Overflow
        */
        void ManejarOverflow(unsigned int &techo, unsigned int &piso);
        /**
        * Maneja el Underflow
        */
        void ManejarUnderflow(unsigned int &techo, unsigned int &piso);
        /**
        * Niega los bits
        */
        void NegarBits(unsigned int &numero, const unsigned int &posicionInicial, const unsigned int &posicionFinal) const;
        /**
        * Escribe numero en el stream
        */
        void Escribir(const unsigned int &numero, const unsigned int &cantidadOverflow);
        /**
        * Ecribe el padding en el stream
        */
        void EscribirPadding();
        /**
        * Conteo de overflow
        */
        unsigned int overflowCount;
        /**
        * Conteo de underflow
        */
        unsigned int underflowCount;
        /**
        * Conteo de emisiones vacias
        */
        unsigned int ufEmisionesVacias;
        /**
        * Steam para la emision
        */
        std::string emision;
};

#endif // BITSTREAM_HPP_INCLUDED
