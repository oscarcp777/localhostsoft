#include "EstrategiaAlmacenamientoTexto.hpp"
#include<iostream>

EstrategiaAlmacenamientoTexto::EstrategiaAlmacenamientoTexto()
{}

EstrategiaAlmacenamientoTexto::~EstrategiaAlmacenamientoTexto() throw()
{}

bool EstrategiaAlmacenamientoTexto::Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    Registro::puntero registro = componente;
    string dato;

    for(Registro::iterador_campos it = registro->primer_campo(); it != registro->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;
        stringstream ss;
        string valor = *(std::string*)campo->obtener_valor();
        ss << sizeof(char)*valor.length();
        dato.append(ss.str());
        dato.append("|");
        dato.append(valor);
    }
    return almacenamiento->escribir(dato.c_str(), posicion);
}

Componente::puntero EstrategiaAlmacenamientoTexto::Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave)
{
    Esquema::puntero esquema = almacenamiento->GetEsquema();
    RegistroLongitudVariable* registro = new RegistroLongitudVariable(clave);
    char* bytes = new char[almacenamiento->obtener_longitud_en_bytes()];

    if(almacenamiento->leer(bytes, posicion))
    {
        for(Esquema::iterador_campos it = esquema->primer_campo(); it != esquema->ultimo_campo(); it++)
        {
            string valor;
            int valorLongitud = 0;
            int i = 0;
            char auxLongitud[sizeof(int)];

            while(bytes[i] !='|') i++;
            memcpy(auxLongitud, bytes, i);
            valorLongitud = atoi(auxLongitud);

            char* auxDato = new char[valorLongitud];

            bytes += i+1;
            memcpy(auxDato,bytes,valorLongitud);
            bytes += valorLongitud;

            CampoCadena* campo = new CampoCadena(auxDato);
            delete[] auxDato;
            registro->agregar_campo(it->first, campo);
        }
        return registro;
    }
    return 0;
}

int EstrategiaAlmacenamientoTexto::AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    return 0;
}
