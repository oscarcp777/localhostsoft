#ifndef COMPRESORARITMETICOHELPER_HPP_INCLUDED
#define COMPRESORARITMETICOHELPER_HPP_INCLUDED

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/**
* Clase CompresorAritmeticoHelper que contiene metodos comunes usados por el Compresor Aritmetico
*/
class CompresorAritmeticoHelper
{
    public:
        /**
        * Obtiene el bit segun el numero y posicion
        */
        static unsigned int obtenerBit(const unsigned int &numero, const int &posicion);
        /**
        * Obtiene el bit al invertido
        */
        static unsigned int obtenerBitReves(const unsigned char &numero, const int &posicion);
        /**
        * Crea la mascara segun la pisicion
        */
        static unsigned int crearMascara(const int &posicionUno);
        /**
        * Devuelve la longitud del padding
        */
        static unsigned int GetLongitudPadding(const string bytesComprimidos);
};

#endif // COMPRESORARITMETICOHELPER_HPP_INCLUDED
