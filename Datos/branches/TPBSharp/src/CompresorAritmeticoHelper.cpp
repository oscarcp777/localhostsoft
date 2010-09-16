#include "CompresorAritmeticoHelper.hpp"

unsigned int CompresorAritmeticoHelper::obtenerBit(const unsigned int &numero, const int &posicion)
{
        unsigned int resultadoMascara = numero & CompresorAritmeticoHelper::crearMascara(posicion);

        int cantidadShitfs = sizeof(unsigned int) * 8 - posicion - 1;

        unsigned int bitResultado = resultadoMascara >> cantidadShitfs;

        return bitResultado;
}

unsigned int CompresorAritmeticoHelper::crearMascara(const int &posicionUno)
{
        int mascara = 1;
        int cantidadShifts = sizeof(int) * 8 - posicionUno - 1;

        mascara = mascara << cantidadShifts;

        return mascara;
}

unsigned int CompresorAritmeticoHelper::obtenerBitReves(const unsigned char &numero, const int &posicion)
{
        return ( ( numero>>posicion ) &1 );
}

unsigned int CompresorAritmeticoHelper::GetLongitudPadding(const string bytesComprimidos)
{
        int longitudPadding = 0;
        unsigned char ultimoByte = bytesComprimidos[bytesComprimidos.size() -1];

        for (int i=0; i<8 ; ++i)
        {
                ++longitudPadding;
                bool currentBit = CompresorAritmeticoHelper::obtenerBitReves(ultimoByte, i);
                if (currentBit == 1)
                        break;
        }

        return longitudPadding;
}

