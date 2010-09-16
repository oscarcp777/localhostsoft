#include "CompresorAritmetico.hpp"

CompresorAritmetico::CompresorAritmetico()
{
        this->piso = 0;
        this->techo = ~0;
}

CompresorAritmetico::~CompresorAritmetico() throw()
{
}

unsigned char CompresorAritmetico::GetSimbolo (const unsigned int bufferLeido, TablaCompresor &tabla, unsigned int &npiso, unsigned int &ntecho)
{
         unsigned char primero = 0, ultimo = MAX_UNSIGNED_BYTE_VALUE - 1;

         while (primero <= ultimo)
         {
                 unsigned char simbolo = (primero + ultimo) / 2;
                 CalcularRango(simbolo, tabla, npiso, ntecho);

                 if ( (npiso < bufferLeido) && (ntecho < bufferLeido) )
                 {
                         primero = simbolo + 1;
                 }
                 else if ( (npiso > bufferLeido) && (ntecho > bufferLeido) )
                         ultimo = simbolo - 1;
                 else
                 {
                         return simbolo;
                 }
         }

         return 0;
}

string CompresorAritmetico::Comprimir(const string &bytesAComprimir)
{
        this->piso = 0;
        this->techo = ~0;
        this->bitStream.Reiniciar();
        TablaCompresor tablaCompresion;

        for (unsigned int i = 0; i < bytesAComprimir.size()-1; i++)
                ComprimirSimbolo((unsigned char)bytesAComprimir[i], tablaCompresion);

        ComprimirUltimoSimbolo((unsigned char)bytesAComprimir[bytesAComprimir.size()-1], tablaCompresion);

        return bitStream.GetBytesEscritos();
}


void CompresorAritmetico::ComprimirSimbolo(const unsigned char &simbolo, TablaCompresor &tablaFrecuencia)
{
        CalcularRango(simbolo, tablaFrecuencia, this->piso, this->techo);
        bitStream.Procesar(techo, piso);
        tablaFrecuencia.IncrementarFrecuencia(simbolo);
}

void CompresorAritmetico::ComprimirUltimoSimbolo(const unsigned char &simbolo, TablaCompresor &tablaFrecuencia)
{
        CalcularRango(simbolo, tablaFrecuencia, this->piso, this->techo);
        bitStream.Procesar(piso, piso);
}

void CompresorAritmetico::CargarBufferLeido(unsigned int &bufferLeido, const string fuente, const unsigned int cantidadBits, unsigned int &UltimoBitEmitido)
{
        unsigned int primerByte = floor( (UltimoBitEmitido )/8);
        unsigned int buffer = fuente[primerByte];
        unsigned int mascara = ((unsigned char)~0)>> (UltimoBitEmitido % 8);
        buffer &= mascara;
        buffer <<= 8;
        buffer |= (unsigned char)fuente [primerByte + 1];
        buffer <<= 8;
        buffer |= (unsigned char)fuente [primerByte + 2];
        buffer <<= 8;
        buffer |= (unsigned char)fuente [primerByte + 3];

        buffer >>= (sizeof(int)*8 - cantidadBits - ( UltimoBitEmitido % 8) );

        bufferLeido |= buffer;
        UltimoBitEmitido += cantidadBits;
}

void CompresorAritmetico::CalcularRango(const unsigned char simbolo,
                                            TablaCompresor &tablaFrecuencia,
                                            unsigned int &nuevoPiso,
                                            unsigned int &nuevoTecho) const
{
        double probabilidadSimboloAnterior, probabilidadSimbolo;
        tablaFrecuencia.CalcularProbabilidad(simbolo, probabilidadSimboloAnterior, probabilidadSimbolo);

        unsigned int rango = techo - piso;
        unsigned int pisoAux = piso;

        nuevoPiso = ceil(pisoAux + (rango * probabilidadSimboloAnterior) + (1 * probabilidadSimboloAnterior));
        nuevoTecho = floor(pisoAux + (rango * probabilidadSimbolo) + (1 * probabilidadSimbolo)) - 1;
}

string CompresorAritmetico::Descomprimir(const string bytesComprimidos)
{
        piso = 0;
        techo = ~0;
        bitStream.Reiniciar();
        TablaCompresor tablaDescompresion;

        unsigned int longitudComprimidos = bytesComprimidos.size() * 8 - CompresorAritmeticoHelper::GetLongitudPadding(bytesComprimidos);

        string resultadoDescomprimido = "";

        if (bytesComprimidos.size() == 0)
            return resultadoDescomprimido;

        unsigned int bitsEmitidos = 32;
        unsigned int ultimoBitEmitido = 0;
        unsigned int bufferLeido = 0;

        while (ultimoBitEmitido < longitudComprimidos || bitsEmitidos == 0)
        {
                if(bitsEmitidos != 0)
                    CargarBufferLeido(bufferLeido, bytesComprimidos, bitsEmitidos, ultimoBitEmitido);
                bitsEmitidos = DescomprimirSimbolo(tablaDescompresion, bufferLeido, longitudComprimidos, ultimoBitEmitido, resultadoDescomprimido);
        }

        return resultadoDescomprimido;
}

unsigned int CompresorAritmetico::DescomprimirSimbolo(TablaCompresor &tablaDescompresion,
                                                            unsigned int &bufferLeido,
                                                            unsigned int &tamanoInfoComprimida,
                                                            unsigned int &ultimoBitEmitido,
                                                            string &resultadoDescomprimido)
{
        unsigned int bitsSimbolo, pisoObtenido, techoObtenido;
        unsigned char simbolo = GetSimbolo(bufferLeido, tablaDescompresion, pisoObtenido, techoObtenido);

        if (ultimoBitEmitido >= tamanoInfoComprimida && simbolo == '\0')
            return 1;
        else
            resultadoDescomprimido += simbolo;

        this->bitStream.Procesar(techoObtenido, pisoObtenido);
        this->techo = techoObtenido;
        this->piso = pisoObtenido;
        bitsSimbolo = bitStream.compactarBufferLeido(bufferLeido);
        tablaDescompresion.IncrementarFrecuencia(simbolo);

        return bitsSimbolo;
}
