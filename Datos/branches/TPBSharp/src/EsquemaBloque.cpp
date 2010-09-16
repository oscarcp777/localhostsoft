#include "EsquemaBloque.hpp"
#include<iostream>

EsquemaBloque::EsquemaBloque(int cantidadDeBloques)
{
    this->cantidadDeBloques = cantidadDeBloques;
    for(int i = 0; i < cantidadDeBloques; i++)
    {
        this->listaBloquesEspacio.insert(std::make_pair(i, 0));
    }
}

EsquemaBloque::~EsquemaBloque() throw()
{
}

int EsquemaBloque::GetEspacioOcupado(int numeroDeBloque)
{
    return this->listaBloquesEspacio[numeroDeBloque];
}

int EsquemaBloque::GetCantidadDeBloques()
{
    return this->cantidadDeBloques;
}

void EsquemaBloque::SetEspacioOcupado(int numeroDeBloque, int espacio)
{
    if(numeroDeBloque < this->cantidadDeBloques && numeroDeBloque > -1)
        this->listaBloquesEspacio[numeroDeBloque] = espacio;
    else
        std::cout<< "El numero de bloque: " << numeroDeBloque << " es inexistente" << '\n';
}

EsquemaBloque::iterador EsquemaBloque::primerCampo()
{
    return listaBloquesEspacio.begin();
}

EsquemaBloque::iterador EsquemaBloque::ultimoCampo()
{
    return listaBloquesEspacio.end();
}
