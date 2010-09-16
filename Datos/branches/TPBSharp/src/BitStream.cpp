#include "BitStream.hpp"

BitStream::BitStream()
{
        Reiniciar();
}

BitStream::~BitStream() throw()
{
}

void BitStream::Procesar(unsigned int &techo, unsigned int &piso)
{
        if (HayOverflow(techo, piso))
            ManejarOverflow(techo, piso);

        if ( this->overflowCount != 0)
            ufEmisionesVacias = 0;
        else
            ufEmisionesVacias = this->underflowCount;

        if (HayUnderflow(techo, piso))
            ManejarUnderflow(techo, piso);
}

bool BitStream::HayOverflow(const unsigned int &techo, const unsigned int &piso) const
{
        int primerBitTecho = CompresorAritmeticoHelper::obtenerBit(techo, 0);
        int primerBitPiso  = CompresorAritmeticoHelper::obtenerBit(piso, 0);

        return (primerBitTecho == primerBitPiso);
}

bool BitStream::HayUnderflow(const unsigned int &techo, const unsigned int &piso) const
{
        int primerBitTecho = CompresorAritmeticoHelper::obtenerBit(techo, 0);
        int primerBitPiso  = CompresorAritmeticoHelper::obtenerBit(piso, 0);
        int segundoBitTecho = CompresorAritmeticoHelper::obtenerBit(techo, 1);
        int segundoBitPiso  = CompresorAritmeticoHelper::obtenerBit(piso, 1);

        return ((primerBitTecho == 1) && (primerBitPiso == 0) &&
                    (segundoBitTecho == 0) && (segundoBitPiso == 1));
}

void BitStream::ManejarOverflow(unsigned int &techo, unsigned int &piso)
{
        this->overflowCount = 0;
        const unsigned int tamanoInt = sizeof(int) * 8;

        for(unsigned int i = 0; i < tamanoInt; i ++)
        {
                if (CompresorAritmeticoHelper::obtenerBit(techo, i) != CompresorAritmeticoHelper::obtenerBit(piso, i))
                    break;

                this->overflowCount++;
        }

        Escribir(techo, this->overflowCount);

        techo = techo << this->overflowCount;
        piso = piso << this->overflowCount;

        unsigned int posicionInicial = tamanoInt - this->overflowCount;

        NegarBits(techo, posicionInicial, tamanoInt);
}

void BitStream::Escribir(const unsigned int &numero, const unsigned int &cantidadOverflow)
{
        unsigned int bitMasSignificativo = CompresorAritmeticoHelper::obtenerBit(numero, 0);
        unsigned int bitNegado = bitMasSignificativo ^ 1;

        emision += bitMasSignificativo;

        while (this->underflowCount > 0)
        {
                emision += bitNegado;
                this->underflowCount--;
        }

        for (unsigned int i = 1; i < cantidadOverflow; i++)
            emision += CompresorAritmeticoHelper::obtenerBit(numero, i);
}

void BitStream::ManejarUnderflow(unsigned int &techo, unsigned int &piso)
{
        const unsigned int tamanoInt = sizeof(int) * 8;

        unsigned int cantidadUnderflow = 0;
        for(unsigned int i = 1; i < tamanoInt; i ++)
        {
                if ((CompresorAritmeticoHelper::obtenerBit(techo, i) != 0) || (CompresorAritmeticoHelper::obtenerBit(piso, i) != 1))
                    break;

                cantidadUnderflow++;
        }

        this->underflowCount += cantidadUnderflow;

        piso = piso << (cantidadUnderflow + 1);
        piso = piso >> 1;

        techo = techo << (cantidadUnderflow + 1);
        techo = techo >> 1;

        NegarBits(techo, 0, 1);
        NegarBits(techo, tamanoInt - cantidadUnderflow, tamanoInt);
}

void BitStream::EscribirPadding()
{
        int tamanoPadding = 8 - emision.size() % 8;
        emision += 1;
        tamanoPadding--;

        int cero = 0;

        while (tamanoPadding > 0)
        {
                emision += cero;
                tamanoPadding--;
        }
}

std::string BitStream::GetBytesEscritos()
{
        EscribirPadding();
        const int tamanoChar = sizeof(char) * 8;
        int cantidadCaracteres = emision.size() / tamanoChar;
        std::string emisionResultado = "";

        int posicion = 0;

        for (int i = 0; i < cantidadCaracteres; i++)
        {
                int bufferBits = 0;

                for (int j = posicion; j < (posicion + tamanoChar); j++)
                {
                        bufferBits = bufferBits << 1;
                        bufferBits += emision[j];
                }

                emisionResultado += bufferBits;
                posicion += tamanoChar;
        }

        return emisionResultado;
}

unsigned int BitStream::compactarBufferLeido(unsigned int &bufferLeido)
{
        bufferLeido = bufferLeido << this->overflowCount;

        int bitMasSignificativo = CompresorAritmeticoHelper::obtenerBit(bufferLeido, 0);

        bufferLeido = bufferLeido << (this->underflowCount - ufEmisionesVacias + 1);
        bufferLeido = bufferLeido >> 1;

        if (bitMasSignificativo == 1)
            NegarBits(bufferLeido, 0, 1);

        unsigned int resultado = this->overflowCount + this->underflowCount - ufEmisionesVacias;

        this->overflowCount = 0;
        return resultado;
}

void BitStream::NegarBits(unsigned int &numero, const unsigned int &posicionInicial, const unsigned int &posicionFinal) const
{
        for (unsigned int i = posicionInicial; i < posicionFinal; i ++)
            numero = numero ^ CompresorAritmeticoHelper::crearMascara(i);
}

void BitStream::Reiniciar()
{
        this->underflowCount = 0;
        this->overflowCount = 0;
        this->ufEmisionesVacias = 0;
        this->emision = "";
}
